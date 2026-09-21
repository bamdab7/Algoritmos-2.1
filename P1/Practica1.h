typedef struct{
    char nombre[25];
    char subestimada[25];
    char sobreestimada[25];
    char ajustada[25];
    int (*fib)(int n);
    double n[10];
    int size;
} algoritmoFib;

int fib_1(int n);
//  Algoritmo con la peor coplejidad de todos, siento esta exponencial,
//lo cual lo vuelve inservible para el calculo de valores altos.

void cotasFib1(double t,double n,double *sub, double *sob, double *aj);

int fib_2(int n);

void cotasFib2(double t, double n, double *sub, double *sob, double *aj);

int fib_3(int n);

void cotasFib3(double t, double n, double *sub, double *sob, double *aj);

void setFibonacci(int *a);
//  Devuelve un array de enteros con los primeros 20 valores de fibonacci,
// es necesario hacer free del array posteriormente.

void generarSecuenciaFib(int *a, int n, int (*algoritmo)(int));
// Rellena un array 'a' de tamaño 'n' con la secuencia de fibonacci.

void testFibs();

double medirTiempo(int (*fib)(int n), int n, char *micro);

void printearCotas(algoritmoFib args,void (*cotas)
(double t,double n,double *sub, double *sob, double *aj));