#include <LFU.hpp>

// priority logic only in request code.
bool LFUcache::request(int64_t pageid)
{
#ifdef Debug
    printf("Request %ld\n", pageid);
#endif

    if (pagetoposition.find(pageid) != pagetoposition.end())
    {
        int pos = pagetoposition[pageid];
        priority(pos, postofreq[pos] + 1);

        return true;
    }
    load(pageid);
    int pos = pagetoposition[pageid];
    priority(pos, 1);

    return false;
}

void LFUcache::priority(int64_t pos, int64_t pri)
{
#ifdef Debug
    printf("priority %ld\n", pos);
    printf("pos - %ld old - %ld new - %ld\n", pos, postofreq[pos], pri);
#endif

    positions.erase(positions.find({postofreq[pos], pos}));
    positions.insert({pri, pos});
    postofreq[pos]=pri;
}

bool LFUcache::load(int64_t pageid)
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

bool LFUcache::evict(int64_t position)
{
#ifdef Debug
    printf("Evict %ld\n", position);
#endif
    int64_t page = positiontopage[position];

    if (page == 0)
    {
        positiontopage.erase(positiontopage.find(position));
    }
    else
    {

        pagetoposition.erase(pagetoposition.find(page));
        positiontopage.erase(positiontopage.find(position));
    }

#ifdef Debug
    printf("Evict %ld end\n", position);
#endif
    return true;
}
// priority logic again added here
int64_t LFUcache::getfreeposition()
{
#ifdef Debug
    printf("Get Free position\n");
#endif
    int pos = (*positions.begin()).second;
    evict(pos);
    return pos;
}

LFUcache::LFUcache()
{
#ifdef Debug
    printf("Cache Initialization\n");
#endif

    for (int i = 1; i <= CACHELINE_SIZE; i++)
    {
        positions.insert({0, i});
        postofreq[i] = 0;
    }
}

void LFUcache::print()
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
    printf("\nFrequency of Positions\n");

    for (auto it = positions.begin(); it != positions.end(); it++)

    {
        printf("%ld ", (*it).first);
    }
    printf("\n");

    for (auto it = positions.begin(); it != positions.end(); it++)

    {
        printf("%ld ", (*it).second);
    }
    printf("\n\n");
}
