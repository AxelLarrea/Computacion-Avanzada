#include <stdio.h>
#include <string.h>
#include "mpi.h"

// BLOQUEANTE
// int main(int argc, char* argv[]){
//     int my_rank;
//     int n;
//     int n_nodes;
//     MPI_Init(&argc, &argv);
//     MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
//     MPI_Comm_size(MPI_COMM_WORLD, &n_nodes);
//     if (my_rank == 0) {
//         printf("Hola, ingresa un numero: ");
//         scanf("%d",&n);
//         for (int destino = 1; destino < n_nodes; destino++){
//             MPI_Send(&n, 1, MPI_INT, destino, 0, MPI_COMM_WORLD);
//         }
//     }
//     else {
//         MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//         printf("Hola, soy el proceso %d y el numero es %d\n", my_rank, n);
//     }
//     return MPI_Finalize();
// }

 
//NO BLOQUEANTE
int main(int argc, char* argv[]){
    int my_rank;
    int n;
    int n_nodes;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n_nodes);
    MPI_Request request;
    if (my_rank == 0) {
        printf("Hola, ingresa un numero: ");
        scanf("%d",&n);
        for (int destino = 1; destino < n_nodes; destino++){
            MPI_Isend(&n, 1, MPI_INT, destino, 0, MPI_COMM_WORLD, &request);
        }
    }
    else {
        MPI_Irecv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, MPI_STATUS_IGNORE);
        printf("Hola, soy el proceso %d y el numero es %d\n", my_rank, n);
    }
    return MPI_Finalize();
}