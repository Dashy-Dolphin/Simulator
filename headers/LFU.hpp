#include <bits/stdc++.h>
#ifndef LFU_HPP
#define LFU_HPP
 
// This Cache just evicts the first position when all the positions are occupied.
// There is ordering among the free positions to be served.

class LFUcache
{
public:
    LFUcache();
    bool request(int64_t pageid);
    void print();

private:
    bool evict(int64_t position);
    bool load(int64_t pageid);
    int64_t getfreeposition();
    void priority(int64_t pos,int64_t pri);

    // positions are numbered from 1 to CACHELINE_SIZE
    std::map<int64_t, int64_t> pagetoposition;
    std::map<int64_t, int64_t> positiontopage;
    std::set<std::pair<int64_t,int64_t>,std::less<std::pair<int64_t,int64_t>>> positions; // sorted according to last usage
                                   // first one is the last used.
    std::map<int64_t,int64_t> postofreq;
    const int CACHELINE_SIZE = 3;
};
#endif