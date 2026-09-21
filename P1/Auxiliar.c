#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <sys/time.h>

#include "Practica1.h"

/* obtiene la hora actual en microsegundos */
double microsegundos()
{
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void printArray(int *a, int n){
    // 'a' Array a printear.
    // 'n' tamaño array.
    printf("[");
    for (int i = 0 ; i < n -1; i++ ){
        printf("%d, ",a[i]);
    }
    printf("%d]\n\n",a[n-1]);
}

void arraysIguales(int n, int size, int **a){
    // 'a' array de arrays a comparar.
    // 'n' numero de arrays a comparar.
    // "size" tamaño de los arrays  (se asume que son del mismo tamaño)
    int i = 0, j = 0;
    bool x = true;
    for( i = 0; i < size; i ++ ){
        for( j = 1; j < n; j++ ){
            if(!(a[j][i] == a[j-1][i]))
            x = false;
        }
    }
    if(x)
        printf("Los arrays son iguales\n\n");   
    else{
        printf("Los arrays no son iguales\n\n");
     }
}


