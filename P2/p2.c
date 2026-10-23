#include "p2.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void inicializar_semilla() {
    srand(time(NULL));
}

void aleatorio(int v[], int n) {
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
}

void ascendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++)
        v[i] = i;
}

void descendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++)
        v[i] = n - 1 - i;
}

void printearVector(int v[], int n) {
    int i, longitud = 0;
    const int maxlen = 120;
    char s[maxlen];
    if (n == 0) {
        printf("[]\n");
        return;
    }
    s[0] = '\0';
    for (i = 0; i < n; i++) {
        longitud +=
            snprintf(s + longitud, (size_t)maxlen - longitud, "%d,", v[i]);
        if (longitud >= maxlen) {
            printf("[%s...]\n", s);
            return;
        }
    }
    s[longitud - 1] = ']';
    printf("[%s\n", s);
}

bool isSorted(int v[], int n) { // O(n)
    int i = 1;
    for (i = 1; i < n; i++) {
        if (v[i - 1] > v[i])
            return false;
    }
    return true;
}

void orndenacionPorInserccion(int* v, int n, int umbral) {
    int i = 1, j = 0, x = 0;

    (void)umbral;
    for (i = 1; i < n; i++) {
        x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > x) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = x;
    }
}

void testIsSorted(int v[]) {
    ascendente(v, 20);
    printf("Ascendente (n = 20)\n");
    printf("  Vector:    ");
    printearVector(v, 20);
    printf("  Ordenado:  %s\n\n", isSorted(v, 20) ? "Si" : "No");
    descendente(v, 20);
    printf("Descendente (n = 20)\n");
    printf("  Vector:    ");
    printearVector(v, 20);
    printf("  Ordenado:  %s\n\n", isSorted(v, 20) ? "Si" : "No");

    ascendente(v, 20);
    v[19] = -1;
    printf("Ultimo elemento fuera de orden (n = 20)\n");
    printf("  Vector:    ");
    printearVector(v, 20);
    printf("  Ordenado:  %s\n\n", isSorted(v, 20) ? "Si" : "No");
}

void testInserccion(int v[]) {
    int i, exitos = 0;
    for (i = 0; i < 100; i++) {
        aleatorio(v, 1000);
        orndenacionPorInserccion(v, 1000, -1);
        if (isSorted(v, 1000))
            exitos++;
    }
    printf("100 vectores aleatorios (n = 1000)\n");
    printf("  Correctos: %d/100\n", exitos);
    printf("  Resultado: %s\n\n", exitos == 100 ? "Exito" : "Fallo");

    printf("Aleatorio (n = 10000)\n");
    aleatorio(v, 10000);
    printf("  Antes:     ");
    printearVector(v, 10000);
    orndenacionPorInserccion(v, 10000, -1);
    printf("  Despues:   ");
    printearVector(v, 10000);
    printf("  Ordenado:  %s\n\n", isSorted(v, 10000) ? "Si" : "No");
    aleatorio(v, 20);
    printf("Aleatorio (n = 20)\n");
    printf("  Antes:     ");
    printearVector(v, 20);
    orndenacionPorInserccion(v, 20, -1);
    printf("  Despues:   ");
    printearVector(v, 20);
    printf("  Ordenado:  %s\n\n", isSorted(v, 20) ? "Si" : "No");
}

void test() {
    int* v = malloc(sizeof(int) * 10000);
    printf("------------------------------------------------------------\n");
    printf(" TEST isSorted\n");
    printf("------------------------------------------------------------\n\n");
    testIsSorted(v);
    printf("------------------------------------------------------------\n");
    printf(" TEST Insercion\n");
    printf("------------------------------------------------------------\n\n");
    testInserccion(v);
    printf("------------------------------------------------------------"
           "\n\n\n\n\n\n\n");
    free(v);
}

double medirTiempo(void (*alg)(int[], int, int),
                   void (*inicializar)(int[], int), int v[], int n,
                   int umbral, char* micro) {
    double ta, tb, t, t1, t2;
    int i, K = 1000;
    strcpy(micro, " ");
    inicializar(v, n);
    ta = microsegundos();
    alg(v, n, umbral);
    tb = microsegundos();
    t = tb - ta;

    if (t < 500) {
        strcpy(micro, "*");
        do {
            ta = microsegundos();
            for (i = 0; i < K; i++) {
                inicializar(v, n);
                alg(v, n, umbral);
            }
            tb = microsegundos();
            t1 = tb - ta;

            ta = microsegundos();
            for (i = 0; i < K; i++) {
                inicializar(v, n);
            }
            tb = microsegundos();
            t2 = tb - ta;

            t = (t1 - t2) / K;
            K *= 2;
        } while ((t1 - t2) < 500);
    }

    return t;
}

void cotasInserccion(double t, double n, double* sub, double* sob,
                     double* aj) {
    *sub = t / pow(n, 1.8);
    *aj = t / pow(n, 2.0);
    *sob = t / pow(n, 2.2);
}

void printearCotas(sortAlgorithm args,
                   void (*cotas)(double t, double n, double* sub, double* sob,
                                 double* aj),
                   void (*inicializar)(int[], int)) {
    int* v = malloc(sizeof(int) * (int)args.n[args.size - 1]);
    double t, sub = 0, sobre = 0, aj = 0;
    int i = 0;
    char micro[3];
    char titulo[96];
    const char separador[] =
        "---------------------------------------------------------------"
        "---------------------------------------------------------------";
    if (args.umbral == -1) {
        snprintf(titulo, sizeof(titulo), "%s - Inicializacion: %s",
                 args.nombre, args.inicializacion);
    } else {
        snprintf(titulo, sizeof(titulo),
                 "%s - Inicializacion: %s - Umbral: %d", args.nombre,
                 args.inicializacion, args.umbral);
    }
    printf("\n%35s[%s]\n\n", "", titulo);
    printf("%s\n", separador);
    printf("%15s | %24s | %24s | %24s | %24s |\n", "Size", "Tiempo",
           "Subestimada", "Ajustada", "Sobreestimada");
    printf("%15s | %24s | %24s | %24s | %24s |\n", "n", "t(n)",
           args.subestimada, args.ajustada, args.sobreestimada);
    printf("%s\n", separador);
    for (i = 0; i < args.size; i++) {
        t = medirTiempo(args.sort, inicializar, v, (int)args.n[i],
                        args.umbral, micro);
        cotas(t, args.n[i], &sub, &sobre, &aj);
        printf("%2s %12d | %24.5f | %24.10lf | %24.10lf | %24.10lf |\n", micro,
               (int)args.n[i], t, sub, aj, sobre);
    }
    printf("%s\n", separador);
    printf("\n");
    free(v);
}

int main() {
    sortAlgorithm insercion = {.nombre = "Insercion",
                               .umbral = -1,
                               .subestimada = "t(n)/n^1.8",
                               .sobreestimada = "t(n)/n^2.2",
                               .ajustada = "t(n)/n^2",
                               .sort = orndenacionPorInserccion,
                               .n = {500, 1000, 2000, 4000, 8000, 16000},
                               .size = 6};

    /* Configuracion prep   arada para las tablas de tiempos. */
    inicializar_semilla();
    // test();
    strcpy(insercion.inicializacion, "Aleatorio");
    printearCotas(insercion, cotasInserccion, aleatorio);
    strcpy(insercion.inicializacion, "Ascendente");
    printearCotas(insercion, cotasInserccion, ascendente);
    strcpy(insercion.inicializacion, "Descendente");
    printearCotas(insercion, cotasInserccion, descendente);
}
