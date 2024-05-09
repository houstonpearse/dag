#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void print_int_array(int *array, int size, char sep) {
    int i;
    for (i=0;i<size;i++) {
        printf("%d%c",array[i],sep);
    }
}

int* permutation(int size) {
    srand(time(NULL));
    int i,j,tmp, *perm = (int*)malloc(size*sizeof(int));
    for (i=0;i<size;i++) {
        perm[i] = i;
    }
    for (i=size-1;i>0;i--) {
        j = rand()%(i+1);
        tmp = perm[j]; 
        perm[j] = perm[i];
        perm[i] = tmp;
    } 
    return perm;
}

int observe(long double p) {
    return rand() < RAND_MAX*p;
}