# P2 — una tabla por llamada

Compilar y ejecutar desde esta carpeta:

```sh
make
./test
```

`printearCotas(args, calcularCotas, inicializar)` imprime una sola tabla.
`args` contiene el algoritmo, el umbral, los tamaños y los textos de esa tabla.
Por ejemplo:

```c
strcpy(Fusion.inicializacion, "Aleatorio");
Fusion.umbral = 20;
printearCotas(Fusion, cotasFusionU20, aleatorio);
```

Al cambiar la función de cotas, ajusta también `subestimada`, `ajustada` y
`sobreestimada` si las fórmulas cambian. `inicializacion` es el nombre que
aparece en el título; la función recibida determina cómo se rellena el vector.

La función de cotas conserva el orden de parámetros del proyecto original:
`(t, n, &subestimada, &sobreestimada, &ajustada)`.

El `main` incluye doce llamadas independientes: tres para inserción y nueve
para fusión (tres inicializaciones por cada umbral: 1, 20 y 200).
