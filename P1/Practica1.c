#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <sys/time.h>
#include "Practica1.h"
#include "Auxiliar.h"


// -- Codigo Practica -- //

int fib_1(int n){
    if(n < 2)
 return n;
    else
 return fib_1(n-1) + fib_1(n-2);
}

int fib_2(int n){
    int i = 1, j = 0;
    for(int k = 0; k < n; k++){
        j = i + j;
        i = j - i;
    }
 return j;
}

int fib_3(int n)
{
    int i = 1, j = 0, k = 0, h = 1, t = 0;
    while(n>0){
        if (!(n % 2 == 0)){
            t = j * h;
            j = i*h + j*k + t;
            i = i*k + t;
        }
    t = pow(h,2);
    h = 2*k*h + t;
    k = pow(k,2) + t;
    n = n/2;
}
return j;
}

void setFibonacci(int *a)
{
    int m[20] = { 1, 1, 2, 3, 5, 8, 13, 21,
                                34, 55, 89, 144, 233, 377,
                                610, 987, 1597, 2584, 4181, 6765};
    for (int i = 0; i < 20; i++)
    {
        a[i] = m[i];
    }
}

void generarSecuenciaFib(int  *a, int n, int (*algoritmo)(int))
{
    for (int i = 0; i < n; i++){
        a[i] = algoritmo(i + 1);
    }
}

void testFibs(){
    int *f20 = malloc(sizeof(int) * 20);
    int *f1 = malloc (sizeof(int) * 100);
    int *f2 = malloc(sizeof(int) * 100);
    int *f3 = malloc(sizeof(int) * 100);
    int **a = malloc(sizeof(int * ) * 4);
    a[3] = f20, a[0] = f1, a[1] = f2, a[2] = f3;

    setFibonacci(f20);
    generarSecuenciaFib(f1, 40, fib_1);
    generarSecuenciaFib(f2, 40, fib_2);
    generarSecuenciaFib(f3, 40, fib_3);
    arraysIguales(4,20,a);
    arraysIguales(3,40, a);
    if(fib_3(200) == fib_3(200))
    printf("\n iguales");
    else{
        printf("no son iguales\n");
        }
}


int main(int argc, char *argv[]) {
    testFibs();
        srand(time(NULL)); // Cambiar por un entrero para resultados constantes
    }
