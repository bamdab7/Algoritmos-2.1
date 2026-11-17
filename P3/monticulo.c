void inicializarMonticulo(monticulo *m, int tamMax)
{ /* vacío */
    m->ultimo = -1;
    m->tamMax = tamMax;
    m->vector = malloc(tamMax * sizeof(arista));
}
void liberarMonticulo(monticulo *m)
{
    free(m->vector);
    m->vector = NULL;
    m->ultimo = -1;
}
int monticuloVacio(monticulo *m)
{
    return m->ultimo == -1;
}
static void intercambiar(arista *a, arista *b)
{
    arista tmp = *a;
    *a = *b;
    *b = tmp;
}
static void flotar(monticulo *m, int i)
{
    while (i > 0 && m->vector[(i - 1) / 2].peso > m->vector[i].peso)
    {
        intercambiar(&m->vector[(i - 1) / 2], &m->vector[i]);
        i = (i - 1) / 2;
    }
}
static void hundir(monticulo *m, int i)
{
    /* COMPLETAR: Hundir de teoría para un montículo de mínimos
    cuyo vector empieza en la posición 0 */
}
void insertar(arista x, monticulo *m)
{
    if (m->ultimo == m->tamMax - 1)
    {
        fprintf(stderr, "Error: montículo lleno\n");
        exit(EXIT_FAILURE);
    }
    m->ultimo++;
    m->vector[m->ultimo] = x;
    flotar(m, m->ultimo);
}
arista eliminarMin(monticulo *m)
{
    arista x;
    if (monticuloVacio(m))
    {
        fprintf(stderr, "Error: montículo vacío\n");
        exit(EXIT_FAILURE);
    }
    x = m->vector[0];
    m->vector[0] = m->vector[m->ultimo];
    m->ultimo--;
    if (m->ultimo >= 0)
        hundir(m, 0);
    return x;
}