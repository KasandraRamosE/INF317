#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define SIZE 6
#define MAX_LEN 50

int main(int argc,char* argv[]) {
    int rank,size;
    char cadenas[SIZE][MAX_LEN]={"cadena0","cadena1","cadena2","cadena3","cadena4","cadena5"};

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if (size != 3) {
        if (rank==0)
            printf("Se requieren exactamente 3 procesos.\n");
        MPI_Finalize();
        return 1;
    }

    if (rank==0) {
        for (int i=1; i<SIZE; i+=2)
            MPI_Send(cadenas[i],MAX_LEN,MPI_CHAR,2,i,MPI_COMM_WORLD);
        for (int i=0; i<SIZE; i+=2)
            MPI_Send(cadenas[i],MAX_LEN,MPI_CHAR,1,i,MPI_COMM_WORLD);
    } else if (rank==1) {
        printf("Procesador 1 (posiciones pares):\n");
        for (int i=0; i<SIZE; i+=2) {
            char buffer[MAX_LEN];
            MPI_Recv(buffer,MAX_LEN,MPI_CHAR,0,i,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            printf(" Posicion %d: %s\n",i,buffer);
        }
    } else if (rank==2) {
        printf("Procesador 2 (posiciones impares):\n");
        for (int i=1; i<SIZE; i+=2) {
            char buffer[MAX_LEN];
            MPI_Recv(buffer,MAX_LEN,MPI_CHAR,0,i,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            printf(" Posicion %d: %s\n",i,buffer);
        }
    }

    MPI_Finalize();
    return 0;
}