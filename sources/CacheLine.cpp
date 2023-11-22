#include <CacheLine.hpp>

bool CacheLine::request(int64_t pageid)
{
    if (pagetoposition.find(pageid) != pagetoposition.end())
    {
        return true;
    }
    load(pageid);
    return false;
}

bool CacheLine::load(int64_t pageid)
{
    int64_t pos = getfreeposition();
    assert(pos > 0); // O is an invalid position
    assert(pos <= CACHELINE_SIZE);

    freepositions.erase(pos);

    pagetoposition[pageid] = pos;
    positiontopage[pos] = pageid;

    return true;
}

bool CacheLine::evict(int64_t position)
{
    assert(freepositions.find(position) == freepositions.end());

    freepositions.insert(position);
    int64_t page = positiontopage[position];
    assert(page != 0);

    pagetoposition.erase(pagetoposition.find(page));
    positiontopage.erase(positiontopage.find(position));

    return true;
}

int64_t CacheLine::getfreeposition()
{
    if (freepositions.empty())
    {
        int pos = 1;
        evict(1);
        freepositions.insert(1);
        return 1;
    }
    else
    {
        return *(freepositions.begin());
    }
}

CacheLine::CacheLine()
{
    freepositions.clear();
    for (int i = 1; i <= CACHELINE_SIZE; i++)
    {
        freepositions.insert(i);
    }
}

void CacheLine::print()
{
    printf("Cache\n");
    for (int64_t i = 1; i <= CACHELINE_SIZE; i++)
    {

        int64_t pageid = -1;
        if (positiontopage.find(i) != positiontopage.end())
        {
            pageid = positiontopage[i];
        }

        printf("%ld ", pageid);
    }
    printf("\nFree Positions\n");
    for (auto x : freepositions)
    {
        printf("%ld ", x);
    }
    printf("\n");
}
