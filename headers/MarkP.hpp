#include <bits/stdc++.h>
#ifndef MARKP_HPP
#define MARKP_HPP

const int CACHELINE_SIZE = 3;
// This Cache just evicts the first position when all the positions are occupied.
// There is ordering among the free positions to be served.

class MarkPcache
{
public:
    MarkPcache();
    bool request(int64_t pageid,int64_t prediction);
    void print();

private:
    bool evict(int64_t position);
    bool load(int64_t pageid);
    int64_t getfreeposition();
    int64_t getrand();

    std::set<int64_t> freepositions; // positions are numbered from 1 to CACHELINE_SIZE
    std::map<int64_t, int64_t> pagetoposition;
    std::map<int64_t, int64_t> positiontopage;
    std::map<int64_t,int64_t> pagestopred;  //marked pages into cache
    std::vector<int64_t> unmarked1; //unmarked pages into cache in prediction 0
    std::vector<int64_t> unmarked0; //unmarked pages into cache in prediction 1
};
#endif
