#include <stdio.h>
#include <stdint.h>
#include <x86intrin.h>
#include <emmintrin.h>
int main()
{
    int a[50];
    unsigned int t1,t2,diff1,diff2,diff3,diff4;
    unsigned int diff5,diff6,diff7,diff8,diff9;
     for (int i=0;i <50;i++) 
     {
        _mm_lfence();
        _mm_clflush(&a[i]);
        _mm_lfence();
     }

    _mm_lfence();
    t1 = __rdtsc();
    _mm_lfence();
    int tmp=a[0];
    _mm_lfence();
    t2 = __rdtsc();
    _mm_lfence();
    diff1 = t2 - t1;
    printf("Cache Access latency for a[0] %lu\n",diff1);

    _mm_lfence();
    t1 = __rdtsc();
    tmp=a[7];
    _mm_lfence();
    t2 = __rdtsc();
    _mm_lfence();
    diff2 = t2 - t1;
    printf("Cache Access latency for a[7] %lu\n",diff2);

    _mm_lfence();
    t1 = __rdtsc();
    tmp=a[8];
    _mm_lfence();
    t2 = __rdtsc();
    _mm_lfence();
    diff3 = t2 - t1;
    printf("Cache Access latency for a[8] %lu\n",diff3);

    _mm_lfence();
    t1 = __rdtsc();
    tmp = a[15];
    _mm_lfence();
    t2 = __rdtsc();
    _mm_lfence();
    diff4 = t2 - t1;
    printf("Cache Access latency for a[15] %lu\n",diff4);

    _mm_lfence();
    t1 = __rdtsc();
    tmp = a[16];
    _mm_lfence();
    t2 = __rdtsc();
    _mm_lfence();
    diff5 = t2 - t1;
    printf("Cache Access latency for a[16] %lu\n",diff5);

    _mm_lfence();
    t1 = __rdtsc();
    tmp = a[23];
    _mm_lfence();
    t2 = __rdtsc();
    _mm_lfence();
    diff6 = t2 - t1;
    printf("Cache Access latency for a[23] %lu\n",diff6);

    _mm_lfence();
    t1 = __rdtsc();
    tmp = a[24];
    _mm_lfence();
    t2 = __rdtsc();
    _mm_lfence();
    diff7 = t2 - t1;
    printf("Cache Access latency for a[24] %lu\n",diff7);

    _mm_lfence();
    t1 = __rdtsc();
    tmp = a[31];
    _mm_lfence();
    t2 = __rdtsc();
    _mm_lfence();
    diff8 = t2 - t1;
    printf("Cache Access latency for a[31] %lu\n",diff8);

    _mm_lfence();
    t1 = __rdtsc();
    tmp = a[32];
    _mm_lfence();
    t2 = __rdtsc();
    _mm_lfence();
    diff9 = t2 - t1;
    printf("Cache Access latency for a[32] %lu\n",diff9);
}