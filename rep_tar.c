#include <stdio.h>
#include "omp.h"

int main(int argc, char **argv){
    int n,tid;
    omp_set_num_threads(5);
    #pragma omp parallel private (tid)
    {
        tid = omp_get_thread_num();
        for(n=0;n<10;n++){
            printf("Hola mundo %d \n",tid);
        }
    }
    return(0);
}


// int main(int argc, char **argv){
//     int n,tid;
//     omp_set_num_threads(5);
//     #pragma omp parallel private (tid)
//     {
//         tid = omp_get_thread_num();
//         #pragma omp for
//             for(n=0;n<10;n++){
//                 printf("Hola mundo %d \n",tid);
//             }
//     }
//     return(0);
// }