#include "p2.h"
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define INFINITO INT_MAX /* de <limits.h> */
#define PESO_MAX 1000

typedef int** matriz;

matriz crearMatriz(int n) {
    int i;
    matriz aux;
    if ((aux = malloc(n * sizeof(int*))) == NULL)
        return NULL;
    for (i = 0; i < n; i++)
        if ((aux[i] = malloc(n * sizeof(int))) == NULL)
            return NULL;
    return aux;
}
void liberarMatriz(matriz m, int n) {
    int i;
    for (i = 0; i < n; i++)
        free(m[i]);
    free(m);
}
/* Matriz de adyacencia de un grafo dado por su lista de aristas {u, v, peso}
 */
void iniMatrizAristas(matriz m, int n, int numAristas, int aristas[][3]) {  
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            m[i][j] = (i == j) ? 0 : INFINITO;
    for (i = 0; i < numAristas; i++)
        m[aristas[i][0]][aristas[i][1]] = m[aristas[i][1]][aristas[i][0]] =
            aristas[i][2];
}

/* Grafo completo con pesos en [1..PESO_MAX]. Devuelve el nºde aristas */
int iniGrafoDenso(matriz m, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        m[i][i] = 0;
        for (j = i + 1; j < n; j++)
            m[i][j] = m[j][i] = rand() % PESO_MAX + 1;
    }
    return n * (n - 1) / 2;
}
/* Grafo conexo con k*n aristas: un árbol aleatorio más aristas
aleatorias. Devuelve el número de aristas */
int iniGrafoDisperso(matriz m, int n, int k) {
    int i, j, u, v, numAristas = 0, maxAristas = n * (n - 1) / 2;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            m[i][j] = (i == j) ? 0 : INFINITO;
    for (v = 1; v < n; v++) {
        u = rand() % v;
        m[u][v] = m[v][u] = rand() % PESO_MAX + 1;
        numAristas++;
    }
    if (k * n < maxAristas)
        maxAristas = k * n;
    while (numAristas < maxAristas) {
        u = rand() % n;
        v = rand() % n;
        if (u != v && m[u][v] == INFINITO) {
            m[u][v] = m[v][u] = rand() % PESO_MAX + 1;
            numAristas++;
        }
    }
    return numAristas;
}

typedef struct nodo { /* nodo de una lista de adyacencia */
    int vertice;
    int peso;
    struct nodo* sig;
} nodo;
typedef nodo** listas; /* listas[v]: adyacentes de v */

listas matrizAListas(matriz m, int n){
   listas l = malloc(sizeof(nodo* )* n);
   nodo* arista;
   nodo* aux;
   for( int i = 0; i < n; i++){
       l[i] = NULL;
       for (int j = 0; j < n; j++) {
           if (m[i][j] != 0 && m[i][j] != INFINITO){
               arista = malloc(sizeof(nodo));
               arista->peso = m[i][j];
               arista->vertice = j;
               arista->sig = NULL;
               if(l[i] == NULL)
               l[i] = arista;
               else{
                for(aux = l[i]; aux->sig != NULL; aux = aux->sig );
                aux->sig = arista;
               }
           }
       }
   }
   return l ;
}