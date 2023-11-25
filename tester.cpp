#include <MarkP.hpp>
#include <Mark0.hpp>
#include <LRU.hpp>
#include <LFU.hpp>
#include <cstring>
int64_t getrand()
{
    return rand();
}
// Arguments are input_file_name and cache_type
int main(int argv, char *argc[])
{
    srand(time(0));
    char input_dir[] = "input/";
    char output_dir[] = "output/";

    assert(argv == 4);
    char *Cache_type = argc[2];
    std::string output_file = std::string(output_dir) + std::string(argc[1]) + "_" + std::string(argc[3]) + std::string(".") + std::string(Cache_type);
    std::string input_file = std::string(input_dir) + std::string(argc[1]);

    double alpha = atof(argc[3]);
    const int error_multiplier = 1000;

    std::fstream fp(input_file, std::ios::in);
    printf("Opening input file : %s\n", argc[1]);
    char *input_file_split = strtok(argc[1], "_");
    input_file_split = strtok(NULL, "_");
    int cache_size = atoi(input_file_split);
    input_file_split = strtok(NULL, "_");
    int max_pages = atoi(input_file_split);
    input_file_split = strtok(NULL, "_");
    int opt_misses = atoi(input_file_split);
    printf("Cache Size : %d\n", cache_size);
    printf("Max Pages : %d\n", max_pages);
    printf("Optimal Misses : %d\n", opt_misses);

    assert(fp.is_open());

    std::vector<int64_t> request_set;
    std::map<int64_t, int64_t> request_cnt;
    std::map<int64_t, int64_t> misses_cnt;
    int64_t tot_req = 0, tot_misses = 0;

    MarkPcache Mpcache(cache_size);
    Mark0cache M0cache(cache_size);
    LFUcache LFcache(cache_size);
    LRUcache LRcache(cache_size);

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
            request_set.push_back(request);
        }
        request_cnt[request]++;
        tot_req++;

        bool hit = true;

        if (strcmp(Cache_type, "MarkP") == 0)
        {
            int64_t rand = getrand() % error_multiplier;
            if (rand < alpha * error_multiplier)
            {
                phasepred = 1 - phasepred;
            }

            hit = Mpcache.request(request, phasepred);
        }
        else if (strcmp(Cache_type, "Mark0") == 0)
        {
            int64_t rand = getrand() % error_multiplier;
            if (rand < alpha * error_multiplier)
            {
                optpred = 1 - optpred;
            }
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

    std::fstream fpout(output_file, std::ios::out);

    assert(fpout.is_open());
    sort(request_set.begin(), request_set.end());
    fpout << request_set.size() << " " << tot_req << " " << tot_misses << "\n";
    // for (auto x : request_set)
    // {
    //     fpout << x << " " << request_cnt[x] << " " << misses_cnt[x] << "\n";
    // }
    fpout.close();
    return 0;
}