#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define n 4

void generarmat(int mat[n][n]){
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            mat[i][j]=rand() % 10;
        }
    }
}

void imprimirmat(int mat[n][n]){
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
}

int main(int argc,char* argv[]){
    int rank,size;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if (rank==0)
        srand(time(NULL));

    int A[n][n],B[n][n],C[n][n];
    int i,j,k;

    int rows_per_process=n / size;
    int remainder=n % size;

    if (rank==0){
        generarmat(A);
        generarmat(B);
        printf("matriz A:\n");
        imprimirmat(A);
        printf("matriz B:\n");
        imprimirmat(B);
    }

    MPI_Bcast(B,n*n,MPI_INT,0,MPI_COMM_WORLD);

    int rows_to_handle=rows_per_process+(rank<remainder ? 1 : 0);
    int sub_A[rows_to_handle][n];
    int sub_C[rows_to_handle][n];

    if (rank==0){
        int offset=rows_to_handle;
        for (int proc=1; proc<size; proc++){
            int rows_for_proc=rows_per_process+(proc<remainder ? 1 : 0);
            MPI_Send(&A[offset][0],rows_for_proc*n,MPI_INT,proc,0,MPI_COMM_WORLD);
            offset += rows_for_proc;
        }

        for (i=0; i<rows_to_handle; i++){
            for (j=0; j<n; j++)
                sub_A[i][j]=A[i][j];
        }
    } else{
        MPI_Recv(&sub_A,rows_to_handle*n,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    }

    for (i=0; i<rows_to_handle; i++){
        for (j=0; j<n; j++){
            sub_C[i][j]=0;
            for (k=0; k<n; k++) 
                sub_C[i][j] += sub_A[i][k]*B[k][j];
        }
    }

    if (rank==0){
        for (i=0; i<rows_to_handle; i++){
            for (j=0; j<n; j++)
                C[i][j]=sub_C[i][j];
        }

        int offset=rows_to_handle;
        for (int proc=1; proc<size; proc++){
            int rows_for_proc=rows_per_process+(proc<remainder ? 1 : 0);
            MPI_Recv(&C[offset][0],rows_for_proc*n,MPI_INT,proc,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            offset += rows_for_proc;
        }

        printf("multiplicacion:\n");
        imprimirmat(C);
    } else{
        MPI_Send(&sub_C,rows_to_handle*n,MPI_INT,0,0,MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
