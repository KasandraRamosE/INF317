#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10  

int main(int argc, char* argv[]) {
    int rank, size;
    int vA[SIZE], vB[SIZE], vectorResultado[SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 3) {
        if (rank == 0) {
            printf("Se requieren exactamente 3 procesos.\n");
        }
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        for (int i = 0; i < SIZE; i++) {
            vA[i] = i;       // vA = [0, 1, 2, 3, 4, ...]
            vB[i] = SIZE - i; // vB = [10, 9, 8, 7, 6, ...]
        }

        MPI_Send(vA, SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(vB, SIZE, MPI_INT, 1, 1, MPI_COMM_WORLD);
        MPI_Send(vA, SIZE, MPI_INT, 2, 2, MPI_COMM_WORLD);
        MPI_Send(vB, SIZE, MPI_INT, 2, 3, MPI_COMM_WORLD);

        int resultadoImpares[SIZE];
        int resultadoPares[SIZE];

        MPI_Recv(resultadoImpares, SIZE, MPI_INT, 1, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(resultadoPares, SIZE, MPI_INT, 2, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = 0; i < SIZE; i++) {
            if (i % 2 == 0) {
                vectorResultado[i] = resultadoPares[i];
            } else {
                vectorResultado[i] = resultadoImpares[i];
            }
        }

        printf("Vector A: ");
        for (int i = 0; i < SIZE; i++) {
            printf("%d ", vA[i]);
        }
        printf("\n");

        printf("Vector B: ");
        for (int i = 0; i < SIZE; i++) {
            printf("%d ", vB[i]);
        }
        printf("\n");

        printf("Resultado de la suma: ");
        for (int i = 0; i < SIZE; i++) {
            printf("%d ", vectorResultado[i]);
        }
        printf("\n");
    } else if (rank == 1) {
        int vA[SIZE], vB[SIZE], resultadoImpares[SIZE];
        MPI_Recv(vA, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(vB, SIZE, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = 1; i < SIZE; i += 2) {
            resultadoImpares[i] = vA[i] + vB[i];
        }

        MPI_Send(resultadoImpares, SIZE, MPI_INT, 0, 4, MPI_COMM_WORLD);
    } else if (rank == 2) {
        int vA[SIZE], vB[SIZE], resultadoPares[SIZE];
        MPI_Recv(vA, SIZE, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(vB, SIZE, MPI_INT, 0, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = 0; i < SIZE; i += 2) {
            resultadoPares[i] = vA[i] + vB[i];
        }

        MPI_Send(resultadoPares, SIZE, MPI_INT, 0, 5, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}