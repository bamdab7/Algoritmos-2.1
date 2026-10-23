#ifndef P2_H
#define P2_H

#include <stdbool.h>

/* Guarda el nombre, la inicializacion, las cotas y los tamaños de entrada. */
typedef struct {
    char nombre[25];
    char inicializacion[12]; /* "Aleatorio", "Ascendente" o "Descendente". */
    int umbral;              /* Umbral de fusion; no se usa en insercion. */
    char subestimada[25];
    char sobreestimada[25];
    char ajustada[25];
    void (*sort)(int v[], int n, int umbral);
    double n[10];
    int size;
} sortAlgorithm;

/* Inicializa la semilla del generador de numeros pseudoaleatorios. */
void inicializar_semilla(void);

/* Rellena el vector con enteros pseudoaleatorios entre -n y n. */
void aleatorio(int v[], int n);

/* Rellena el vector con los valores de 0 a n - 1. */
void ascendente(int v[], int n);

/* Rellena el vector con los valores de n - 1 a 0. */
void descendente(int v[], int n);

/* Muestra el vector entre corchetes y recorta la salida si es larga. */
void printearVector(int v[], int n);

/* Ordena el vector de menor a mayor mediante insercion; ignora el umbral. */
void orndenacionPorInserccion(int* v, int n, int umbral);

/* Comprueba si el vector esta ordenado de menor a mayor. */
bool isSorted(int v[], int n);

/* Prueba isSorted con vectores ordenados y desordenados. */
void testIsSorted(int v[]);

/* Comprueba la ordenacion por insercion con vectores aleatorios. */
void testInserccion(int v[]);

/* Reserva el vector de pruebas, ejecuta los tests y libera la memoria. */
void test(void);

/* Obtiene la hora actual en microsegundos. */
double microsegundos(void);

/* Mide la ordenacion y descuenta la inicializacion al repetir medidas cortas.
 */
double medirTiempo(void (*alg)(int[], int, int),
                   void (*inicializar)(int[], int), int v[], int n,
                   int umbral, char* micro);

/* Calcula t/n^1.8, t/n^2 y t/n^2.2 para insercion aleatoria o descendente. */
void cotasInserccion(double t, double n, double* sub, double* sob, double* aj);

/* Muestra una tabla de tiempos y cotas, como en la practica 1. */
void printearCotas(sortAlgorithm args,
                   void (*cotas)(double t, double n, double* sub, double* sob,
                                 double* aj),
                   void (*inicializar)(int[], int));

#endif /* P2_H */
