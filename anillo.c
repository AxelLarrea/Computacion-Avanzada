#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char* argv[]) {
    int node, n_nodes;
    int n = 2;
    char message[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &node);
    MPI_Comm_size(MPI_COMM_WORLD, &n_nodes);
    MPI_Status status;
    
    if (node == 0) {
        sprintf(message, "Hola soy el proceso 0 y envio al proceso %d ", node + 1);
        MPI_Send(message, 100, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        printf(message);
        fflush(stdout);
    }

    for (int i = 0; i < n; i++) {
        if (node == 0) {
            MPI_Recv(message, 100, MPI_CHAR, n_nodes-1 , 0, MPI_COMM_WORLD, &status);
        }
        else
            MPI_Recv(message, 100, MPI_CHAR, node-1, 0, MPI_COMM_WORLD, &status);
            sprintf(message, "Hola soy el proceso %d y envio al proceso %d \n ", node, (node+1)%n_nodes);
            MPI_Send(message, 100, MPI_CHAR, (node+1)%n_nodes, 0, MPI_COMM_WORLD);
            printf(message);
            fflush(stdout);
    }
    MPI_Finalize();
}