#ifndef ARTEMIS_H
#define ARTEMIS_H
#define G_DEFAULT 9.80
typedef struct {
    double aceleracion[2];
    double tiempo_desacople, altura_objetivo, gravedad;
} Parametros;
typedef struct {
    double v1, y1, t2, v2, altura_adicional, altura_maxima, aceleracion_g;
} Resultados;
void cargarParametrosPorDefecto(Parametros *p);
int calcularResultados(const Parametros *p, Resultados *r);
void ejecutarSimulador(void);
#endif
