typedef struct {
    char nombre[25];
    int (*funcion)(int n);
    double n;
    double sobreestimada;
    double subestimada;
    double ajustada;
}algoritmo;

double microsegundos();

void printArray(int *a, int n);
//Printea un array de enteros, neesita el tamaño del array para ello.

void arraysIguales(int n, int size, int **a);
//Recibe un numero n de array de tamaño n y muestra si son iguales.

void medirTiempos(int(*funcion)(), int n);