#include <stdio.h>
#include "omp.h"

int main(int argc, char **argv){
    int id;
    omp_set_num_threads(5);
    #pragma omp parallel private (id)
    {
        id = omp_get_thread_num();
        printf("Hola mundo desde el Thread %d \n",id);
    
    }
    return 0;
}