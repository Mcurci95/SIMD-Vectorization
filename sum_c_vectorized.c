#include <stdio.h>
#include <smmintrin.h>
#include <immintrin.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_LEN 120000

//trivial sum
int sum_n(int *arr)
{
    int sum = 0;
    for (int i = 0; i < MAX_LEN; i++)
        sum += arr[i];
    return sum;
}

int sum_v(int *arr)
{
    __m128i a_simd;
    //get `128 bit 0 vector
    __m128i sum = _mm_setzero_si128();
    int bitsum[4];
    //skip 4 for 128bit
    for (int i = 0; i < MAX_LEN; i += 4)
    {
        //return 128 bit vector stored at array pointers
        a_simd = _mm_loadu_si128((__m128i *)&arr[i]);
        // add the result in 0 bit vector previously initialized
        sum = _mm_add_epi32(sum, a_simd);
    }
    //store result in the new array
    _mm_storeu_si128((__m128i *)bitsum, sum);
    return bitsum[0] + bitsum[1] + bitsum[2] + bitsum[3];
}

int main()
{

    	int arr[MAX_LEN];
    	for (int i = 0; i < MAX_LEN; i++)
        	arr[i] = 1;

	double time_spent1 = 0.0;
	double time_spent2 = 0.0;
	clock_t begin = clock();

	printf("sum = %d\n", sum_n(arr));

	clock_t end = clock();
	time_spent1 += (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Time elpased is %f seconds for naive sum.\n", time_spent1);

    	begin = clock();

	printf("sum = %d\n", sum_v(arr));

    	end = clock();
	time_spent2 += (double)(end - begin) / CLOCKS_PER_SEC;

    	printf("Time elpased is %f seconds for 128bit vectorize sum\n", time_spent2);

	printf("%f X time faster.\n", time_spent1/time_spent2);
	return 0;
}