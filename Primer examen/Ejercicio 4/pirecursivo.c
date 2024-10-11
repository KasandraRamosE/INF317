/*
PI RECURSIVO
Serie de Leibniz:
pi= 4 * (1 - 1/3 + 1/5 - 1/7 + 1/9 - ...)
       
         (-1)^(i-1) / (2*i-1)
*/

#include <stdio.h>

double pirecursivo(double *n, double signo) {
    double termino= 1.0 / (2.0 * (*n) - 1.0);
    double aux = (2.0 * (*n) - 1.0);
    //printf("aux %.15f\n", aux);
    if (aux <= 1.0) {
        return 1.0;
    }
   
    if (signo == -1.0){
    signo= 1.0;}
    else{
    signo= -1.0;}
    //printf("%.2f(1/ %.15f)\n", signo,aux);
    *n-=1;
    return signo * termino + pirecursivo(n,signo);
}

int main() {
    double res;
    double n= 100000;  
    res= pirecursivo(&n,1.0);
    res *= 4.0;
    printf("Valor de pi: %.4f\n", res);
    return 0;
}
