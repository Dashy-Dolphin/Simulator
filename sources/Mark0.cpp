#include <Mark0.hpp>
#define Debug
int64_t Mark0cache::randgen()
{
    return rand();
}
bool Mark0cache::request(int64_t pageid, int64_t pred)

{
#ifdef Debug
    printf("Request %ld\n", pageid);
#endif
    bool ans = true;
    if (pagetoposition.find(pageid) == pagetoposition.end())
    {
        ans = false;
        std::vector<int64_t> unmarked;
        for (int i = 1; i <= CACHELINE_SIZE; i++)
        {
            if (positiontopage.find(i) != positiontopage.end())
            {
                assert(freepositions.find(i) == freepositions.end());
                int64_t page = positiontopage[i];
                if (previouscache.find(page) != previouscache.end())
                {
                    if (pagetomark.find(page) == pagetomark.end())
                    {
                        unmarked.push_back(i);
                    }
                }
            }
        }

        bool cond1 = freepositions.empty();

        if (freepositions.empty() && unmarked.empty())
        {
            pagetomark.clear();
            previouscache.clear();
            for (int i = 1; i <= CACHELINE_SIZE; i++)
            {
                assert(positiontopage.find(i) != positiontopage.end());
                int64_t page = positiontopage[i];
                previouscache.insert(page);
            }
            unmarked.clear();
            for (int i = 1; i <= CACHELINE_SIZE; i++)
            {

                unmarked.push_back(i);
            }
        }

        if (freepositions.empty())
        {

            assert(unmarked.size() > 0);
            int randpos = randgen() % unmarked.size();
#ifdef Debug
            printf("Evicting pos %d because cache is full\n", randpos);
#endif
            evict(unmarked[randpos]);
        }

        else if (!unmarked.empty() && (previouscache.find(pageid) != previouscache.end()) && (pagetomark.find(pageid) == pagetomark.end()))
        {
            assert(unmarked.size() > 0);
            int randpos = randgen() % unmarked.size();
#ifdef Debug
            printf("Evicting pos %d because page is unmarked\n", randpos);
#endif
            evict(unmarked[randpos]);
        }

        load(pageid);
    }
    pagetomark[pageid] = 1;

    if (pred == 1)
    {
        assert(pagetoposition.find(pageid) != pagetoposition.end());
        evict(pagetoposition[pageid]);
    }

    return ans;
}

bool Mark0cache::load(int64_t pageid)
{
#ifdef Debug
    printf("Load %ld\n", pageid);
#endif
    int64_t pos = getfreeposition();
    assert(pos > 0); // O is an invalid position
    assert(pos <= CACHELINE_SIZE);

    freepositions.erase(pos);
#ifdef Debug
    printf("free position %ld\n", pos);
    fflush(stdout);
#endif

    pagetoposition[pageid] = pos;
    positiontopage[pos] = pageid;

    return true;
}

bool Mark0cache::evict(int64_t position)
{
#ifdef Debug
    printf("Evict %ld\n", position);
    fflush(stdout);
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

int64_t Mark0cache::getfreeposition()
{
#ifdef Debug
    printf("Get Free position\n");
#endif
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

Mark0cache::Mark0cache(int c)
{
#ifdef Debug
    printf("Cache Initialization\n");
#endif
    // srand(time(0));
    CACHELINE_SIZE = c;
    freepositions.clear();

    for (int i = 1; i <= CACHELINE_SIZE; i++)
    {
        freepositions.insert(i);
    }
}

void Mark0cache::print()
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
