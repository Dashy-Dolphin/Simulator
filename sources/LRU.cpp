#include <LRU.hpp>

// priority logic only in request code.
bool LRUcache::request(int64_t pageid)
{
#ifdef Debug
    printf("Request %ld\n", pageid);
#endif

    if (pagetoposition.find(pageid) != pagetoposition.end())
    {
        int pos = pagetoposition[pageid];
        priority(pos);

        return true;
    }
    load(pageid);
    int pos = pagetoposition[pageid];
    priority(pos);

    return false;
}

void LRUcache::priority(int64_t pos)
{
#ifdef Debug
    printf("priority %ld\n", pos);
#endif
    for (int i = 0; i < CACHELINE_SIZE; i++)
    {
        if (positions[i] == pos)
        {
            positions.erase(positions.begin() + i);
            positions.push_back(pos);
            break;
        }
    }
}

bool LRUcache::load(int64_t pageid)
{
#ifdef Debug
    printf("Load %ld\n", pageid);
#endif
    int64_t pos = getfreeposition();
    assert(pos > 0); // O is an invalid position
    assert(pos <= CACHELINE_SIZE);

    pagetoposition[pageid] = pos;
    positiontopage[pos] = pageid;

    return true;
}

bool LRUcache::evict(int64_t position)
{
#ifdef Debug
    printf("Evict %ld\n", position);
#endif
    int64_t page = positiontopage[position];

    if (page == 0)
    {
        positiontopage.erase(positiontopage.find(position));
    }else{
   

    pagetoposition.erase(pagetoposition.find(page));
    positiontopage.erase(positiontopage.find(position));
    }


#ifdef Debug
    printf("Evict %ld end\n", position);
#endif
    return true;
}
// priority logic again added here
int64_t LRUcache::getfreeposition()
{
#ifdef Debug
    printf("Get Free position\n");
#endif
    int pos = positions[0];
    evict(pos);
    return pos;
}

LRUcache::LRUcache()
{
#ifdef Debug
    printf("Cache Initialization\n");
#endif
    positions.clear();
    for (int i = 1; i <= CACHELINE_SIZE; i++)
    {
        positions.push_back(i);
    }
}

void LRUcache::print()
{
#ifdef Debug
        printf("Print Cache\n" );
#endif
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
    printf("\nLast Used Positions\n");
    for (auto x : positions)
    {
        printf("%ld ", x);
    }
    printf("\n");
}
