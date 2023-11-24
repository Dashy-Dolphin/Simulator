#include <bits/stdc++.h>
#ifndef LRU_HPP
#define LRU_HPP
// This Cache just evicts the first position when all the positions are occupied.
// There is ordering among the free positions to be served.

class LRUcache
{
public:
    LRUcache();
    bool request(int64_t pageid);
    void print();

private:
    bool evict(int64_t position);
    bool load(int64_t pageid);
    int64_t getfreeposition();
    void priority(int64_t pos);

    // positions are numbered from 1 to CACHELINE_SIZE
    std::map<int64_t, int64_t> pagetoposition;
    std::map<int64_t, int64_t> positiontopage;
    int last_hit = 1;
    std::deque<int64_t> positions; // sorted according to last usage
                                   // first one is the last used.
    const int CACHELINE_SIZE = 3;
};
#endif