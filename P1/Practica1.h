
int fib_1(int n);
//  Algoritmo con la peor coplejidad de todos, siento esta exponencial,
//lo cual lo vuelve inservible para el calculo de valores altos.

int fib_2(int n);

int fib_3(int n);

void setFibonacci(int *a);
//  Devuelve un array de enteros con los primeros 20 valores de fibonacci,
// es necesario hacer free del array posteriormente.

void generarSecuenciaFib(int *a, int n, int (*algoritmo)(int));
// Rellena un array 'a' de tamaño 'n' con la secuencia de fibonacci.

void testFibs();