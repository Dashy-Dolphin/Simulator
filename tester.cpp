#include <MarkP.hpp>

int main()
{
    printf("Namaste World\n");

    int requests[] = {1, 2, 3, 4, 5, 3, 2, 3, 3, 4, 5};

    MarkPcache Cache;

    for (int i = 0; i < sizeof(requests) / sizeof(requests[0]); i++)
    {
        int r = requests[i];
        printf("Request %d ", requests[i]);

        if (!Cache.request(r,0))
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