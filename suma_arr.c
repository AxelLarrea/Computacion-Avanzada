#include <stdio.h>
#include "omp.h"

int main(int argc, char **argv){
    int n,id;
    int vec1[] = {0,3,5,1,2,4,6,9};
    int vec2[] = {1,7,2,4,3,4,1,3};
    int res[8];

    printf("Vector 1: \n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", vec1[i]);
    }
    printf("\n");

    printf("Vector 2: \n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", vec2[i]);
    }
    printf("\n");

    int c_elem = 8/2;
    omp_set_num_threads(2);
    #pragma omp parallel private (id,n)
    {
        id = omp_get_thread_num();
        int li = id*c_elem;
        int ls = (id + 1)*c_elem;
        for(n=li;n<ls;n++){
            res[n] = vec1[n]+vec2[n];
            printf("Resultado %d, proceso %d \n",res[n], id);
        }
    }

    printf("Vector resultado: \n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    return(0);
}