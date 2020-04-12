#include <stdio.h>
#include <smmintrin.h>
#include <immintrin.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_LEN 10


float min(size_t n, float *a) {
    float min = a[0];

    for (int i=0; i < n; i++) {
        if (a[i] < min)
            min = a[i];
    }

    return min;
}

int main() {
    float arr[MAX_LEN];
    int n = 10;
    for(int i = 0; i < MAX_LEN; i++)
        arr[i] = (float) i;
    float min_value = min(n, arr);
    printf("%f", min_value);
}
