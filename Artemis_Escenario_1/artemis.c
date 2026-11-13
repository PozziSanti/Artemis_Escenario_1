#include <stdio.h>
#include <math.h>
#include "artemis.h"
#include "validaciones.h"

void cargarParametrosPorDefecto(Parametros *p) {
    p->aceleracion[0] = 20.0;
    p->aceleracion[1] = 12.5;
    p->tiempo_desacople = 120.0;
    p->altura_objetivo = 160000.0;
    p->gravedad = G_DEFAULT;
}

int calcularResultados(const Parametros *p, Resultados *r) {
    double delta_h, v2cuad;
    if (!p || !r || p->aceleracion[0] <= 0 || p->aceleracion[1] <= 0 ||
        p->tiempo_desacople <= 0 || p->altura_objetivo <= 0 || p->gravedad <= 0)
        return 0;
    r->v1 = p->aceleracion[0] * p->tiempo_desacople;
    r->y1 = 0.5 * p->aceleracion[0] * p->tiempo_desacople * p->tiempo_desacople;
    delta_h = p->altura_objetivo - r->y1;
    if (delta_h <= 0) return 0;
    v2cuad = r->v1*r->v1 + 2*p->aceleracion[1]*delta_h;
    r->v2 = sqrt(v2cuad);
    r->t2 = (r->v2-r->v1)/p->aceleracion[1];
    r->altura_adicional = r->v2*r->v2/(2*p->gravedad);
    r->altura_maxima = p->altura_objetivo+r->altura_adicional;
    r->aceleracion_g = p->aceleracion[0]/p->gravedad;
    return 1;
}

static void informe(const Parametros *p, const Resultados *r) {
    printf("\\n===== INFORME DEL ASCENSO SLS / ARTEMIS =====\\n");
    printf("a) Desacople SRB (t=%.2f s): v1=%.2f m/s; y1=%.2f m\\n",
           p->tiempo_desacople,r->v1,r->y1);
    printf("b) Apagado a %.2f m: v2=%.2f m/s; duracion fase 2=%.2f s\\n",
           p->altura_objetivo,r->v2,r->t2);
    printf("c) Altura adicional por inercia=%.2f m; altura maxima=%.2f m\\n",
           r->altura_adicional,r->altura_maxima);
    printf("d) Aceleracion fase 1=%.3f g\\n",r->aceleracion_g);
    puts("=============================================");
}

static void configurar(Parametros *p) {
    Parametros anterior=*p;
    p->aceleracion[0]=leerReal("Aceleracion fase 1 (m/s2): ",0.01,1000);
    p->tiempo_desacople=leerReal("Tiempo hasta desacople (s): ",0.01,100000);
    p->aceleracion[1]=leerReal("Aceleracion fase 2 (m/s2): ",0.01,1000);
    p->altura_objetivo=leerReal("Altura objetivo (m): ",1,100000000);
    p->gravedad=leerReal("Gravedad (m/s2): ",0.01,100);
    if (0.5*p->aceleracion[0]*p->tiempo_desacople*p->tiempo_desacople >= p->altura_objetivo) {
        puts("La fase 1 alcanza/supera la altura objetivo. Se conserva la configuracion anterior.");
        *p=anterior;
    }
}

void ejecutarSimulador(void) {
    Parametros p; Resultados r; int op;
    cargarParametrosPorDefecto(&p);
    do {
        puts("\\n===== SIMULADOR ARTEMIS: ESCENARIO 1 =====");
        puts("1. Apartado a: velocidad y altura al desacople");
        puts("2. Apartado b: velocidad al apagar motores");
        puts("3. Apartado c: altura maxima ante falla");
        puts("4. Apartado d: aceleracion en multiplos de g");
        puts("5. Mostrar todos los resultados");
        puts("6. Modificar parametros");
        puts("7. Restaurar valores de la consigna");
        puts("0. Salir");
        op=leerEntero("Opcion: ",0,7);
        if (op==6) configurar(&p);
        else if (op==7) cargarParametrosPorDefecto(&p);
        else if (op>=1 && op<=5) {
            if (!calcularResultados(&p,&r)) puts("No se puede resolver con estos parametros.");
            else if (op==5) informe(&p,&r);
            else if (op==1) printf("v1=%.2f m/s; y1=%.2f m\\n",r.v1,r.y1);
            else if (op==2) printf("v2=%.2f m/s; tiempo fase 2=%.2f s\\n",r.v2,r.t2);
            else if (op==3) printf("Altura maxima=%.2f m\\n",r.altura_maxima);
            else printf("Aceleracion=%.3f g\\n",r.aceleracion_g);
        }
        if (op!=0) pausar();
    } while(op!=0);
    puts("Simulacion finalizada.");
}
