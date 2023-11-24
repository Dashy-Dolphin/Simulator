#include <MarkP.hpp>
#include <Mark0.hpp>
#include <LRU.hpp>
#include <LFU.hpp>

int main(int argv, char *argc[])
{
    char input_dir[] = "input/";
    char output_dir[] = "output/";

    assert(argv == 3);
    std::string input_file = std::string(input_dir) + std::string(argc[1]);

    std::fstream fp(input_file, std::ios::in);

    assert(fp.is_open());

    std::vector<int64_t> request_set;
    std::map<int64_t, int64_t> request_cnt;
    std::map<int64_t, int64_t> misses_cnt;
    int64_t tot_req = 0, tot_misses = 0;

    MarkPcache Mpcache;
    Mark0cache M0cache;
    LFUcache LFcache;
    LRUcache LRcache;

    char *Cache_type = argc[2];
    while (!fp.eof())
    {
        std::string line;
        std::getline(fp, line);
        int64_t request;
        int optpred, phasepred;

        std::stringstream ss(line);
        ss >> request >> optpred >> phasepred;
        if (request == 0)
        {
#ifdef Debug
            printf("Invalid Request 0\n", request);
#endif
            break;
        }
        if (request_cnt[request] == 0)
        {
            request_set.push_back(requRequest %ld == 0)
        {

            hit = Mpcache.request(request, phasepred);
        }
        else if (strcmp(Cache_type, "Mark0") == 0)
        {
            hit = M0cache.request(request, optpred);
        }
        else if (strcmp(Cache_type, "LFU") == 0)
        {
            hit = LFcache.request(request);
        }
        else if (strcmp(Cache_type, "LRU") == 0)
        {
            hit = LRcache.request(request);
        }

        if (!hit)
        {
            tot_misses++;
            misses_cnt[request]++;
        }

        fflush(stdout);
    }

    fp.close();
    std::string output_file = std::string(output_dir) + std::string(argc[1]) + std::string(".") + std::string(Cache_type);

    std::fstream fpout(output_file, std::ios::out);

    assert(fpout.is_open());
    fpout << request_set.size() << " " << tot_req << " " << tot_misses << "\n";
    for (auto x : request_set)
    {
        fpout << x << " " << request_cnt[x] << " " << misses_cnt[x] << "\n";
    }
    fpout.close();
    return 0;
}