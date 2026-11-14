#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include "validaciones.h"

double leerReal(const char *mensaje, double min, double max) {
    char s[128], *fin;
    double x;
    for (;;) {
        printf("%s", mensaje);
        if (!fgets(s, sizeof s, stdin)) { clearerr(stdin); continue; }
        errno = 0; x = strtod(s, &fin);
        while (isspace((unsigned char)*fin)) fin++;
        if (fin == s || *fin || errno == ERANGE) {
            puts("Entrada invalida: ingrese un numero."); continue;
        }
        if (x < min || x > max) {
            printf("Fuera de rango (%.2f a %.2f).\\n", min, max); continue;
        }
        return x;
    }
}
int leerEntero(const char *m, int min, int max) {
    double x;
    for (;;) {
        x = leerReal(m, min, max);
        if (x == (int)x) return (int)x;
        puts("Debe ingresar un numero entero.");
    }
}
void pausar(void) {
    char s[8];
    printf("\\nPresione ENTER para continuar...");
    fgets(s, sizeof s, stdin);
}
