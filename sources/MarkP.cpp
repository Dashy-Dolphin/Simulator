#include <MarkP.hpp>

int64_t MarkPcache::getrand()
{
    return rand();
}
bool MarkPcache::request(int64_t pageid, int64_t prediction)
{
#ifdef Debug
    printf("Request %ld\n", pageid);
#endif

    bool hit = true;
    pagestopred[pageid] = prediction;
    if (pagetoposition.find(pageid) == pagetoposition.end())
    {
        hit = false;
        if (freepositions.empty())
        {
#ifdef Debug
            printf("Free position available\n");
#endif
            if (unmarked1.empty() && unmarked0.empty())
            {
                unmarked1.clear();
                unmarked0.clear();

                for (int i = 1; i <= CACHELINE_SIZE; i++)
                {
                    if (positiontopage.find(i) != positiontopage.end())
                    {
                        int64_t pageid = positiontopage[i];
                        if (pagestopred[pageid] == 1)
                        {
                            unmarked1.push_back(pageid);
                        }
                        else
                        {
                            unmarked0.push_back(pageid);
                        }
                    }
                }
            }

            if (unmarked1.size() > 0)
            {
                int64_t ran = getrand() % unmarked1.size();
                int64_t pageid = unmarked1[ran];
                int64_t pos = pagetoposition[pageid];
#ifdef Debug
                printf("Evicting pos %ld page %ld\n", pos, pageid);
#endif
                unmarked1.erase(unmarked1.begin() + ran);
                evict(pos);
            }
            else if (unmarked0.size() > 0)
            {
                int64_t ran = getrand() % unmarked0.size();
                int64_t pageid = unmarked0[ran];
                int64_t pos = pagetoposition[pageid];
#ifdef Debug
                printf("Evicting pos %ld page %ld\n", pos, pageid);
#endif
                unmarked0.erase(unmarked0.begin() + ran);
                evict(pos);
            }
        }
        load(pageid);
    }

    for (int i = 0; i < unmarked1.size(); i++)
    {
        if (unmarked1[i] == pageid)
        {
            unmarked1.erase(unmarked1.begin() + i);
            break;
        }
    }

    for (int i = 0; i < unmarked0.size(); i++)
    {
        if (unmarked0[i] == pageid)
        {
            unmarked0.erase(unmarked0.begin() + i);
            break;
        }
    }

    return hit;
}

bool MarkPcache::load(int64_t pageid)
{
#ifdef Debug
    printf("Load %ld\n", pageid);
#endif
    int64_t pos = getfreeposition();
    assert(pos > 0); // O is an invalid position
    assert(pos <= CACHELINE_SIZE);

    freepositions.erase(pos);

    pagetoposition[pageid] = pos;
    positiontopage[pos] = pageid;

    return true;
}

bool MarkPcache::evict(int64_t position)
{
#ifdef Debug
    printf("Evict %ld\n", position);
#endif
    assert(freepositions.find(position) == freepositions.end());

    freepositions.insert(position);
    int64_t page = positiontopage[position];
    assert(page != 0);

    pagetoposition.erase(pagetoposition.find(page));
    positiontopage.erase(positiontopage.find(position));
#ifdef Debug
    printf("Evict %ld end\n", position);
#endif
    return true;
}

int64_t MarkPcache::getfreeposition()
{
#ifdef Debug
    printf("Get Free position\n");
#endif
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

MarkPcache::MarkPcache()
{
#ifdef Debug
    printf("Cache Initialization\n");
#endif
    freepositions.clear();
    for (int i = 1; i <= CACHELINE_SIZE; i++)
    {
        freepositions.insert(i);
    }
}

void MarkPcache::print()
{
#ifdef Debug
    printf("Print Cache\n");
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
    printf("\nFree Positions\n");
    for (auto x : freepositions)
    {
        printf("%ld ", x);
    }
    printf("\n");
}
