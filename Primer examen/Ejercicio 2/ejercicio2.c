#include <stdio.h>

int suma(int a, int b){
    return a+b;
}
int resta(int a, int b){
    return a-b;
}
int multiplicacion(int a, int b){
    return a*b;
}
float division(int a, int b){
    if(b==0){
        printf("Error: Division por cero no permitida \n");
        return 0.0;
    }
    return (float)a/b;
}

int main(){
    int a, b, opcion;
    float res;

    printf("Ingrese el primer numero: ");
    scanf("%d", &a);
    printf("Ingrese el segundo numero: ");
    scanf("%d", &b);

    printf("\nSeleccione la operacion que desea realizar:\n");
    printf(" 1. Suma\n 2. Resta\n 3. Multiplicacion\n 4. Division\n");
    printf("Ingrese su opcion: ");
    scanf("%d", &opcion);

    switch(opcion) {
        case 1:
            res= suma(a, b);
            printf("resultado de la suma: %d\n", (int)res);
            break;
        case 2:
            res= resta(a, b);
            printf("resultado de la resta: %d\n", (int)res);
            break;
        case 3:
            res= multiplicacion(a, b);
            printf("resultado de la multiplicación: %d\n", (int)res);
            break;
        case 4:
            res= division(a, b);
            if (b!=0)
                printf("res de la división: %.2f\n", res);
            break;
        default:
            printf("Opción no válida.\n");
    }

    return 0;

}