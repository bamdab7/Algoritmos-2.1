# P2 — una tabla por llamada

Compilar y ejecutar:

```sh
make
./test
```

`printearCotas(args, calcularCotas, inicializar, rellenarCotas)` imprime una tabla.
`args` contiene el nombre, el algoritmo, el umbral y los tamaños de entrada.
Las otras funciones calculan las cotas, inicializan el vector y rellenan los
textos de cabecera, respectivamente. Por ejemplo:

```c
Fusion.umbral = 20;
printearCotas(Fusion, cotasFusionU20, aleatorio, stringsCotasFusionU20);
```

Cada función `stringsCotas...` rellena `char cotas[3][40]` en orden:
subestimada, ajustada y sobreestimada. Sus textos deben coincidir con las
fórmulas de la función de cálculo elegida.

El nombre de inicialización se obtiene a partir de la función recibida:
`ascendente`, `descendente` o `aleatorio`; para otras se muestra `Personalizada`.

La función de cálculo conserva el orden de parámetros del proyecto original:
`(t, n, &subestimada, &sobreestimada, &ajustada)`.

`imprimirTablasFusion` agrupa tres llamadas a `printearCotas`, una por
inicialización. El programa imprime doce tablas: tres de inserción y nueve
de fusión (tres por cada umbral: 1, 20 y 200).
