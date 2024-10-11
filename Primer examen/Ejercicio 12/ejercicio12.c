#include <stdio.h>
#include <omp.h>

int main() {

int n;
    printf("Ingrese la cantidad de terminos para la serie de fibonacci: ");
    scanf("%d", &n);
   
    int fib[n];
    int i;

    fib[0]= 0;
    fib[1]= 1;

    #pragma omp parallel shared(fib) private(i)
    {
        #pragma omp for ordered
        for (i=2;i<n;i++) {
        #pragma omp ordered
            fib[i] = fib[i-1] + fib[i-2];
        }
    }

    printf("Serie de Fibonacci:\n");
    for (i=0; i<n; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");

    return 0;
}