#include <stdio.h>

void suma(int *a, int b) {
    *a=*a + b;
}

void resta(int *a, int b) {
    *a=*a - b;
}

void multiplicacion(int *a, int b) {
    *a=*a * b;
}

void division(int *a, int b, float *resultado) {
    if (b == 0) {
        printf("Error: División por cero no permitida.\n");
    } else {
        *resultado=(float)(*a) / b; 
    }
}

int main() {
    int a, b, opcion;
    float resdiv;

    printf("Ingrese el primer número: ");
    scanf("%d", &a); 
    printf("Ingrese el segundo número: ");
    scanf("%d", &b);

    printf("\nSeleccione la operación que desea realizar:\n");
    printf("1. Suma\n");
    printf("2. Resta\n");
    printf("3. Multiplicación\n");
    printf("4. División\n");
    printf("Ingrese su opción: ");
    scanf("%d", &opcion);

    switch(opcion) {
        case 1:
            suma(&a, b);
            printf("Resultado de la suma: %d\n", a);
            break;
        case 2:
            resta(&a, b);
            printf("Resultado de la resta: %d\n", a);
            break;
        case 3:
            multiplicacion(&a, b);
            printf("Resultado de la multiplicación: %d\n", a);
            break;
        case 4:
            division(&a, b, &resdiv);
            if (b != 0)
                printf("Resultado de la división: %.2f\n", resdiv);  
            break;
        default:
            printf("Opción no válida.\n");
    }

    return 0;
}
