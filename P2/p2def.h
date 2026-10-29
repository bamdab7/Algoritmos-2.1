#ifndef P2_H
#define P2_H

#include <stdbool.h>

/* Guarda el nombre, la inicializacion, las cotas y los tamaños de entrada. */
typedef struct {
    char nombre[25];
    char inicializacion[3]
                       [12]; /* "Aleatorio", "Ascendente" o "Descendente". */
    int umbral;              /* Umbral de fusion; no se usa en insercion. */
    char subestimada[25];
    char sobreestimada[25];
    char ajustada[25];
    void (*sort)(int v[], int n, int umbral);
    double n[10];
    int size;
} AlgPrintArgs;

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

/* Ordena el vector de menor a mayor mediante insercion. */
void ordenacionInsercion(int v[], int n);

/* Adapta la insercion a la firma (v, n, umbral) de las funciones de medicion.
 */
void insercionMedicion(int v[], int n, int umbral);

/* Fusiona los intervalos ordenados [izq, medio] y [medio + 1, der]. */
void fusionar(int v[], int izq, int medio, int der, int aux[]);

/* Ordena [izq, der] reutilizando el vector auxiliar. */
void ordenacionFusionHibridaAux(int v[], int izq, int der, int aux[],
                                int umbral);

/* Ordena por fusion e insercion para intervalos de tamaño <= umbral. */
void ordenacionFusionHibrida(int v[], int n, int umbral);

/* Comprueba si el vector esta ordenado de menor a mayor. */
bool isSorted(int v[], int n);

/* Prueba isSorted con vectores ordenados y desordenados. */
void testIsSorted(int v[]);

/* Comprueba la ordenacion por insercion con vectores aleatorios. */
void testInsercion(int v[]);

/* Comprueba la ordenacion por fusion con vectores aleatorios
y el umbral dado. */
void testFusion(int v[], int umbral);

/* Reserva el vector de pruebas, ejecuta los tests y libera la memoria. */
void test(void);

/* Obtiene la hora actual en microsegundos. */
double microsegundos(void);

/* Mide la ordenacion y descuenta la inicializacion al repetir medidas cortas. */
double medirTiempo(void (*alg)(int[], int, int),
                   void (*inicializar)(int[], int), int v[], int n, int umbral,
                   char* micro, int* repeticiones);

/* Calcula t/n^1.8, t/n^2 y t/n^2.2 para insercion aleatoria o descendente. */
void cotasInsercion(double t, double n, double* sub, double* sob, double* aj);

/* Calcula t/n^0.8, t/n y t/n^1.2 para insercion ascendente (mejor caso). */
void cotasInsercionAscendente(double t, double n, double* sub, double* sob,
                              double* aj);

/* Calcula t/(n^0.8*log n), t/(n*log n) y t/(n^1.2*log n) para fusion. */
void cotasFusion(double t, double n, double* sub, double* sob, double* aj);

/* Imprime las dos filas de cabecera de la tabla de cotas. */
void imprimirCabeceraCotas(AlgPrintArgs args, int j);

/* Muestra una tabla de tiempos y cotas, como en la practica 1. */
void printearCotas(AlgPrintArgs args,
                   void (*cotas)(double t, double n, double* sub, double* sob,
                                 double* aj));

#endif /* P2_H */