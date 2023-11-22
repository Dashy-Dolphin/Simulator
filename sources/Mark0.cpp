#include <Mark0.hpp>

int64_t Mark0cache::randgen()
{
    return rand();
}
bool Mark0cache::request(int64_t pageid, int64_t pred)


{

    bool ans = true;
    if (pagetoposition.find(pageid) == pagetoposition.end())
    {
        if (freepositions.empty() && commonunmarked.empty())
        {
            previouscache.clear();
            commonunmarked.clear();
            postomark.clear();
            for (int i = 1; i <= CACHELINE_SIZE; i++)
            {

                previouscache.insert(positiontopage[i]);
                commonunmarked.insert(positiontopage[i]);
            }
        }

        bool cond1 = previouscache.find(pageid) != previouscache.end();
        bool cond3 = postomark.find(pageid) == postomark.end();
        bool cond2 = !commonunmarked.empty();
        bool cond4 = freepositions.empty();
        if (cond1 && cond2 && cond3 || cond4)
        {
            int64_t randpos = randgen() % commonunmarked.size() ;

            std::vector<int64_t> temp(commonunmarked.begin(),commonunmarked.end());
            int64_t randpage = temp[randpos];
            int64_t randcachepos = pagetoposition[randpage];
            evict(randcachepos);
            commonunmarked.erase(randpage);
            
        }
        

        load(pageid);
        ans = false;
    }

    postomark[pageid] = 1;

    if (pred == 1)
    {
        evict(pagetoposition[pageid]);
    }
    
    return ans;
}

bool Mark0cache::load(int64_t pageid)
{
    int64_t pos = getfreeposition();
    assert(pos > 0); // O is an invalid position
    assert(pos <= CACHELINE_SIZE);

    freepositions.erase(pos);

    pagetoposition[pageid] = pos;
    positiontopage[pos] = pageid;

    return true;
}

bool Mark0cache::evict(int64_t position)
{
    assert(freepositions.find(position) == freepositions.end());

    freepositions.insert(position);
    int64_t page = positiontopage[position];
    assert(page != 0);

    pagetoposition.erase(pagetoposition.find(page));
    positiontopage.erase(positiontopage.find(position));

    return true;
}

int64_t Mark0cache::getfreeposition()
{
    if (freepositions.empty())
    {
        assert(false);
        // int pos = 1;
        // evict(1);
        // freepositions.insert(1);
        // return 1;
    }
    else
    {
        return *(freepositions.begin());
    }
}

Mark0cache::Mark0cache()
{
    srand(time(0));
    freepositions.clear();
    postomark.clear();
    for (int i = 1; i <= CACHELINE_SIZE; i++)
    {
        freepositions.insert(i);
    }
}

void Mark0cache::print()
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
