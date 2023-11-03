#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"

// Un proceso por cada fila de la matriz

int main(int argc, char* argv[]) {
    int my_rank, nodes;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nodes);

    if (my_rank == 0) {
        int x = nodes-1;
        int y = nodes-1;
        int mat[x][y];
        int vec[y];
        int res[y];
        int res2[y];
        
        //Inicialización
        for (int i = 0; i < y; i++){
            res2[i] = 0; 
        }

        for (int i = 0; i < y; i++){
            vec[i] = 0; 
        }

        for (int i = 0; i < x; i++){
            for (int j = 0; j < y; j++){
                mat[i][j] = 0;
            }
        }
        
        // Carga de datos random
        for (int i = 0; i < x; i++){
            for (int j = 0; j < y; j++){
                mat[i][j] = rand()%10;
            }
        }

        for (int i = 0; i < y; i++){
            vec[i] = rand()%10; 
        }
        
        printf("Mat cargada: \n");
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++){
                printf("%d\t ", mat[i][j]);
            }
            printf("\n");
        }

        printf("Vec cargado: \n");
        for (int i = 0; i < y; i++) {
            printf("%d\n", vec[i]);
        }



        for (int i = 1; i < nodes; i++) {
            MPI_Send(&mat[i - 1], y, MPI_INT, i, 1, MPI_COMM_WORLD);
            MPI_Send(&vec, y, MPI_INT, i, 2, MPI_COMM_WORLD);
            MPI_Send(&y, 1, MPI_INT, i, 3, MPI_COMM_WORLD);
        }

        for (int i = 1; i < nodes; i++) {
            MPI_Recv(&res, y, MPI_INT, i, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (int j = 0; j < y; j++) {
                res2[i-1] += res[j];
            }
        }

        printf("Matriz resultado: \n");
        for (int i = 0; i < y; i++) {
            printf("%d \n", res2[i]);
        }
    }
    else {
        int y;
        MPI_Recv(&y, 1, MPI_INT, 0, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        int res[y];
        int mat2[y];
        int vec2[y];

        MPI_Recv(&mat2, y, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&vec2, y, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


        for (int j = 0; j < y; j++) {
            res[j] = (vec2[j] * mat2[j]);
        }
        MPI_Send(&res, y, MPI_INT, 0, 4, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}