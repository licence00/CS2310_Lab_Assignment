#include <stdio.h>
#include <stdint.h>
#include <x86intrin.h>
#include <emmintrin.h>
int main()
{
    int a[130];
    unsigned int t1,t2,diff1,diff2,diff3,diff4;
    unsigned int diff5,diff6,diff7;
     for (int i=0;i<130;i++) 
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
    tmp=a[63];
    _mm_lfence();
    t2 = __rdtsc();
    _mm_lfence();
    diff2 = t2 - t1;
    printf("Cache Access latency for a[63] %lu\n",diff2);

    _mm_lfence();
    t1 = __rdtsc();
    tmp=a[64];
    _mm_lfence();
    t2 = __rdtsc();
    _mm_lfence();
    diff3 = t2 - t1;
    printf("Cache Access latency for a[64] %lu\n",diff3);

    _mm_lfence();
    t1 = __rdtsc();
    tmp = a[127];
    _mm_lfence();
    t2 = __rdtsc();
    _mm_lfence();
    diff4 = t2 - t1;
    printf("Cache Access latency for a[127] %lu\n",diff4);

    _mm_lfence();
    t1 = __rdtsc();
    tmp = a[128];
    _mm_lfence();
    t2 = __rdtsc();
    _mm_lfence();
    diff5 = t2 - t1;
    printf("Cache Access latency for a[128] %lu\n",diff5);

    _mm_lfence();
    t1 = __rdtsc();
    tmp = a[143];
    _mm_lfence();
    t2 = __rdtsc();
    _mm_lfence();
    diff6 = t2 - t1;
    printf("Cache Access latency for a[143] %lu\n",diff6);

    _mm_lfence();
    t1 = __rdtsc();
    tmp = a[144];
    _mm_lfence();
    t2 = __rdtsc();
    _mm_lfence();
    diff7 = t2 - t1;
    printf("Cache Access latency for a[144] %lu\n",diff7);
}