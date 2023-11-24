#include <bits/stdc++.h>
#ifndef MARK0_HPP
#define MARK0_HPP

// This Cache just evicts the first position when all the positions are occupied.
// There is ordering among the free positions to be served.

class Mark0cache
{
public:
    Mark0cache(int c);
    bool request(int64_t pageid,int64_t pred);
    void print();

private:
    int64_t randgen();
    bool evict(int64_t position);
    bool load(int64_t pageid);
    int64_t getfreeposition();

    std::set<int64_t> freepositions; // positions are numbered from 1 to CACHELINE_SIZE
    std::map<int64_t, int64_t> pagetoposition;
    std::map<int64_t, int64_t> positiontopage;
    std::set<int64_t> previouscache;
    std::map<int64_t,int64_t> pagetomark;
    int CACHELINE_SIZE = 3;
};
#endif