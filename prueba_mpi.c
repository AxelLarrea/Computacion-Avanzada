#include<stdio.h>
#include "mpi.h"


// int main(int argc, char **argv){
//     int node;
//     MPI_Init(&argc, &argv);
//     MPI_Comm_rank(MPI_COMM_WORLD, &node);
//     printf("Hello World fromNode %d\n",node);
//     MPI_Finalize();
// }

int main(int argc, char** argv) {
	int node, n_nodes;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &node);
	MPI_Comm_size(MPI_COMM_WORLD, &n_nodes);
	if (node != 2) {
		char message[30];
		sprintf(message, "Hello World fromNode %d\n", node);
		MPI_Send(message, 30, MPI_CHAR, 2, 0, MPI_COMM_WORLD);
	}
	else {
		for (int sender = 0; sender < n_nodes; sender++) {
            if (sender == 2) {
                sender = sender+1;
            };

			char message[30];
			MPI_Status status;
			MPI_Recv(message, 30, MPI_CHAR, sender, 0, MPI_COMM_WORLD, &status);
			printf("Hola soy el proceso 2 y recibo: %s", message);
		}
	}
	return MPI_Finalize();
}
