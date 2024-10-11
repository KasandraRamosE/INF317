// PI ITERATIVO
// serie de leibniz para pi
#include <stdio.h>

void iterativo(double *pi, int iteraciones) {
    *pi=0.0;
    int signo=1;
    for (int i=0; i<iteraciones; i++) {
        *pi += signo * (4.0 / (2*i+1));
        signo = -signo;
    }
}

int main() {
    double pi;
    int iteraciones = 100000;

    iterativo(&pi, iteraciones);
    printf("Valor de pi: %.4f\n", pi);

    return 0;
}