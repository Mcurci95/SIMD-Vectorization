
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int dot_product_naive(size_t N, int *a, int *b) {
    int product;
    for (size_t i = 0; i < N; i++) {
        product += a[i] * b[i];
    }
    return product;
}

int dot_product(size_t N, int *a, int *b) {
    int product = 0;
    

    #pragma omp parallel for reduction(+:product)
    for (size_t i = 0; i < N; i++) {
        product += a[i] * b[i];
    }

    return product;
}

int main() {

    double time_spent1 = 0.0;
	double time_spent2 = 0.0;
	

    int N = 100000;
    int a[N];
    int b[N];

    for (int i = 0; i < N; i++) {
        a[i] = 1;
        b[i] = 1;
    }
    // int a[] =  {1,2,3,4};
    // int b[] =  {1,2,3,4};

    clock_t begin = clock();
    int product = dot_product_naive(N, &a, &b);
    clock_t end = clock();
	time_spent1 += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%d\n", product);
    printf("Time elapsed is %f seconds for naive dot product.\n", time_spent1);


    begin = clock();

    int new_product = dot_product(N, &a, &b);
    printf("%d\n", new_product);
    end = clock();
	time_spent2 += (double)(end - begin) / CLOCKS_PER_SEC;

    	printf("Time elapsed is %f seconds for OPENMP parallel dot product\n", time_spent2);

	printf("%f X time faster.\n", time_spent1/time_spent2);
    
}