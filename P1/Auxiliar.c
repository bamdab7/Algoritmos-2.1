#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#include "Practica1.h"

void printArray(int *a, int n){
    // 'a' Array a printear.
    // 'n' tamaño array.
    printf("[");
    for (int i = 0 ; i < n -1; i++ ){
        printf("%d, ",a[i]);
    }
    printf("%d]\n\n",a[n-1]);
}

void arraysIguales(int n, int size, int **a)
{
    // 'a' array de arrays a comparar.
    // 'n' numero de arrays a comparar.
    // "size" tamaño de los arrays  (se asume que son del mismo tamaño)
    bool x = true;
    for(int i = 0; i < size; i ++ ){
        for(int j = 1; j < n; j++ ){
            if(!(a[j][i] == a[j-1][i]))
            x = false;
        }
    }
    if(x)
    printf("Los arrays son iguales\n\n");   
     else{
    printf("Los arrays no son iguales\n\n");
     }
     for (int i = 0; i < n; i++) {
         printArray(a[i], size);
     }
}


