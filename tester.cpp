#include <MarkP.hpp>
#include <Mark0.hpp>
#include <LRU.hpp>
#include <LFU.hpp>


int main(int argv, char *argc[])
{
    char input_dir[] = "input/";
    char output_dir[] = "output/";

    assert(argv == 2);
    std::string input_file = std::string(input_dir) + std::string(argc[1]);
    std::string output_file = std::string(output_dir) + std::string(argc[1]);

    std::fstream fp(input_file, std::ios::in);

    assert(fp.is_open());

    std::vector<int64_t> request_set;
    std::map<int64_t, int64_t> request_cnt;
    std::map<int64_t, int64_t> misses_cnt;
    int64_t tot_req = 0, tot_misses = 0;

    while (!fp.eof())
    {
        std::string line;
        std::getline(fp, line);
        int64_t request;
        int optpred, phasepred;

        std::stringstream ss(line);
        ss >> request >> optpred >> phasepred;

        if (request_cnt[request] == 0)
        {
            request_set.push_back(request);
        }
        request_cnt[request]++;
        tot_req++;
    }

    fp.close();

    std::fstream fpout(output_file, std::ios::out);

    assert(fpout.is_open());
    fpout << request_set.size() << " " << tot_req << " " << tot_misses << "\n";
    for (auto x : request_set)
    {
        fpout << x << " " << request_cnt[x] << " " << misses_cnt[x] << "\n";
    }
    fpout.close();
    return 0;



    int requests[] = {1, 2, 3, 4, 5, 3, 2, 3, 3, 4, 5};

    MarkPcache Cache;

    for (int i = 0; i < sizeof(requests) / sizeof(requests[0]); i++)
    {
        int r = requests[i];
        printf("Request %d ", requests[i]);

        if (!Cache.request(r, 0))
        {
            printf("Miss");
        }
        else
        {
            printf("Hit");
        }

        printf("\n");

        Cache.print();
    }
    return 0;
}