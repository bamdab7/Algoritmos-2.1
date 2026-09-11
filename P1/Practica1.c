#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <sys/time.h>
#include <string.h>

#include "Practica1.h"
#include "Auxiliar.h"


// -- Codigo Practica -- //

int fib_1(int n){
    if(n < 2)
 return n;
    else
 return fib_1(n-1) + fib_1(n-2);
}

void cotasFib1(double t, double n, double *sub, double *sob, double *aj){
    *sub = t / (pow(1.1, n));
    *aj = t / (pow(1.2, n));
    *sob = t / (pow(2.0, n));
}

int fib_2(int n){
    int i = 1, j = 0;
    for(int k = 0; k < n; k++){
        j = i + j;
        i = j - i;
    }
 return j;
}

void cotasFib2(double t, double n, double *sub, double *sob, double *aj){
    *sub = t / (pow(n, 0.8));
    *aj = t / (pow(1.2, n));
    *sob = t / (n * log(n));
}


int fib_3(int n){
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

void cotasFib3(double t, double n, double *sub, double *sob, double *aj)
{
    *sub = t / (sqrt((log(n))));
    *aj = t / (pow(1.2, n));
    *sob = t / (pow(n,0.5));
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
    free(f20),free(f1),free(f2),free(f3),free(a);
}

double medirTiempo(int(*fib)(int n),int n){
    double t1 = 0, t2 = 0, t = 0 ;
    t1 = microsegundos();
     fib(n);
    t2 = microsegundos();
    t = t2 - t1;
    if ( t < 500){
        int k = 1000;

        t1 = microsegundos();
        for (int i = 0; i < k; i++){
            fib(n);
        }
        t2 = microsegundos();
        t = (t2 - t1) / k;
    }
  return t;
}

void printearCotas(algoritmoFib args, void (*cotas)
(double t,double n,double *sub, double *sob, double *aj)){
    double t, sub = 0, sobre = 0, aj = 0;
    printf(" \t\t\t\t\t\t\t\t\t--%s-- \n\n", args.nombre);   
    printf("\t\tSize\t  |  Cota: %15s \t|  Cota: %15s     |",args.subestimada,args.ajustada);
    printf("  Cota: %15s\t  |            Tiempo\t       |\n",args.sobreestimada);
        printf("\t\t\t  |\t\t\t\t|\t\t\t     |\t\t\t\t  |\t\t\t       |\n");
    for(int i = 0; i < args.size; i ++){
        t = medirTiempo(args.fib, args.n[i]);
        cotas(t,args.n[i],&sub,&sobre,&aj);
        printf("%25lf | %25lf   | %25lf  | %25lf  | %25lf  |\n"
            ,args.n[i],t,sub,aj,sobre);
    }
    printf("\n\n\n");
}

int main() {
    srand(time(NULL)); // Cambiar por un entrero para resultados constantes
    //testFibs();
    //Definimos el Fibonacci numero 1.
    algoritmoFib FIB_1 = {.n = {2,4,8,16,32}};
    FIB_1.size = 5;
    FIB_1.fib = fib_1;
    strcpy(FIB_1.nombre,"Fibonacci V1");
    strcpy(FIB_1.sobreestimada, "(1.1)^n");
    strcpy(FIB_1.ajustada ,"(1.2)^n");
    strcpy(FIB_1.subestimada, "2^n");

    //Definimos el Fibonnacci 2.
    algoritmoFib FIB_2= {.n = {1000, 10000, 100000, 1000000, 10000000}};
    FIB_2.size = 5;
    FIB_2.fib = fib_2;
    strcpy(FIB_2.nombre, "Fibonacci V2");
    strcpy(FIB_2.sobreestimada, "(pow(n, 0.8))");
    strcpy(FIB_2.ajustada, "pow(1.2, n)");
    strcpy(FIB_2.subestimada, "n*log(n)");
    
    //Definimos el Fibonnacci 3.
    algoritmoFib FIB_3 = {.n = {1000, 10000, 100000, 1000000, 10000000}};
    FIB_3.size = 5;
    FIB_3.fib = fib_2;
    strcpy(FIB_3.nombre, "Fibonacci V3");
    strcpy(FIB_3.sobreestimada, "sqrt((log(n)))");
    strcpy(FIB_3.ajustada, "pow(1.2, n)");
    strcpy(FIB_3.subestimada, "pow(n,0.5)");
    printearCotas(FIB_1, cotasFib1);
    printearCotas(FIB_2, cotasFib2);
    printearCotas(FIB_3, cotasFib2);
    }