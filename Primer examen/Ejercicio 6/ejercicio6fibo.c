#include <stdio.h>

void fibonacci(int n) {
    int fibo1[1]= {0}; 
    int fibo2[1]= {1}; 
    int siguiente[1];       

    if (n >= 1)
        printf("%d ", fibo1[0]);
    if (n >= 2)
        printf("%d ", fibo2[0]);

    for (int i= 2; i < n; i++) { 
        siguiente[0]= fibo1[0]+fibo2[0];  
        fibo1[0]= fibo2[0];          
        fibo2[0]= siguiente[0];            
        printf("%d ",fibo2[0]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Ingrese la cantidad de terminos para la serie de fibonacci: ");
    scanf("%d", &n);

    fibonacci(n);
    
    return 0;
}
