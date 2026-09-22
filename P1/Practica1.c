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
    double phi = (1 + sqrt(5))/2;
    *sub = t / (pow(1.1, n));
    *aj = t / (pow(phi, n));
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
    *aj = t / n;
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
    t = h*h;
    h = 2*k*h + t;
    k = k*k + t;
    n = n/2;
 }
 return j;
}

void cotasFib3(double t, double n, double *sub, double *sob, double *aj)
{
    *sub = t / (sqrt((log(n))));
    *aj = t / log(n);
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

void generarSecuenciaFib(int  *a, int n, int (*algoritmo)(int)){
     int i = 0;
    for ( i = 0; i < n; i++){
        a[i] = algoritmo(i + 1);
    }
}

void printTest(int **a){
    int i = 0;
    printf("|     n     |  fib1(n)  |  fib2(n)  |  fib2(n)  |\n");
    for (i = 0; i < 20; i++){
        printf("| %9d | %9d | %9d | %9d |\n",
             i + 1, a[0][i], a[1][i], a[2][i]);
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
    generarSecuenciaFib(f1, 20, fib_1);
    generarSecuenciaFib(f2, 20, fib_2);
    generarSecuenciaFib(f3, 20, fib_3);
    arraysIguales(4,20,a);
    printTest(a);
    free(f20),free(f1),free(f2),free(f3),free(a);
    printf("\n\n\n\n\n");
}

double medirTiempo(int(*fib)(int n),int n,char * micro){
    double t1 = 0, t2 = 0, t = 0 ;
    int i = 0, k = 1000;
    t1 = microsegundos();
    fib(n);
    t2 = microsegundos();
    strcpy(micro, " ");
    t = t2 - t1;
    if ( t < 500){
         k = 1000;
         strcpy(micro,"*");
        t1 = microsegundos();
        for ( i = 0; i < k; i++){
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
    int i = 0;
    char * micro = malloc(sizeof(char) * 3);
    printf(" %72s \n\n", args.nombre);   
    printf("%15s | %7s%15s  | %7s%15s  | %7s%15s  | %22s  |\n","Size",
        "Cota:",args.subestimada,"Cota: ",args.ajustada,
        "Cota:",args.sobreestimada,"Tiempo");  
    printf("%15s | %24s| %24s| %24s| %24s|\n","","","","","");
    for(i = 0; i < args.size; i ++){
        t = medirTiempo(args.fib, args.n[i], micro);
        cotas(t,args.n[i],&sub,&sobre,&aj);
        printf("%2s %12d |%24lf |%24lf |%24lf |%24lf |\n"
            ,micro,(int)args.n[i],sub,aj,sobre,t);
    }
    free(micro);
    printf("\n\n\n");
}

int main() {
    testFibs();
    //Definimos el Fibonacci numero 1.
    algoritmoFib FIB_1 = {.n = {2,4,8,16,32}};
    FIB_1.size = 5;
    FIB_1.fib = fib_1;
    strcpy(FIB_1.nombre,"--Fibonacci V1--");
    strcpy(FIB_1.sobreestimada, "(1.1)^n");
    strcpy(FIB_1.ajustada, "(φ)^n");
    strcpy(FIB_1.subestimada, "2^n");

    //Definimos el Fibonnacci 2.
    algoritmoFib FIB_2= {.n = {1000, 10000, 100000, 1000000, 
                             10000000,100000000,}};
    FIB_2.size = 6;
    FIB_2.fib = fib_2;
    strcpy(FIB_2.nombre, "--Fibonacci V2--");
    strcpy(FIB_2.sobreestimada, "(pow(n, 0.8))");
    strcpy(FIB_2.ajustada, "n");
    strcpy(FIB_2.subestimada, "n*log(n)");
    
    //Definimos el Fibonnacci 3.
    algoritmoFib FIB_3 = {.n = {1000, 10000, 100000, 1000000, 
                             10000000,100000000,1000000000,}};
    FIB_3.size = 7;
    FIB_3.fib = fib_3;
    strcpy(FIB_3.nombre, "--Fibonacci V3--");
    strcpy(FIB_3.sobreestimada, "sqrt((log(n)))");
    strcpy(FIB_3.ajustada, "log n");
    strcpy(FIB_3.subestimada, "pow(n,0.5)");
    for(int i = 0; i< 1000; i++){
        fib_2(i);
    }
    printearCotas(FIB_1, cotasFib1);
    printearCotas(FIB_2, cotasFib2);
    printearCotas(FIB_3, cotasFib3);
    }
