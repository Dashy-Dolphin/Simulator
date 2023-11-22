#include <bits/stdc++.h>
#ifndef CACHELINE_HPP
#define CACHELINE_HPP

const int CACHELINE_SIZE = 3;
// This Cache just evicts the first position when all the positions are occupied.
// There is ordering among the free positions to be served.

class CacheLine
{
public:
    CacheLine();
    bool request(int64_t pageid);
    void print();

private:
    bool evict(int64_t position);
    bool load(int64_t pageid);
    int64_t getfreeposition();

    std::set<int64_t> freepositions; // positions are numbered from 1 to CACHELINE_SIZE
    std::map<int64_t, int64_t> pagetoposition;
    std::map<int64_t, int64_t> positiontopage;
};
#endif