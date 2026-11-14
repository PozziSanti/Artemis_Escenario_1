# TFI — Simulador de Misiones Artemis | Escenario 1

**UTN Facultad Regional Resistencia — Algoritmos y Estructuras de Datos**  
**Escenario:** Ascenso y Propulsión con el SLS (MRUV y Desprendimiento).  
**Lenguaje:** C11.

## Descripción
El programa simula el ascenso vertical de Orion impulsada por el cohete SLS. Parte del reposo, acelera durante la primera fase con los motores principales y los SRB, se desprenden los SRB y continúa acelerando con el núcleo hasta alcanzar la altura de apagado. Se desprecia la resistencia del aire, tal como indica la consigna.

## Datos iniciales
- Velocidad y altura inicial: 0 m/s y 0 m.
- Aceleración fase 1: 20,0 m/s².
- Tiempo hasta desacople: 120,0 s.
- Aceleración fase 2: 12,5 m/s².
- Altura de apagado: 160.000,0 m.
- Gravedad: 9,80 m/s².

## Ecuaciones
**Fase 1**
- `v1 = v0 + a1*t1`
- `y1 = y0 + v0*t1 + (a1*t1²)/2`

**Fase 2**
- `v2² = v1² + 2*a2*(h-y1)`
- `t2 = (v2-v1)/a2`

**Falla de motores al llegar a h**
- `Delta h = v2²/(2*g)`
- `hmax = h + Delta h`

**Aceleración en múltiplos de g**
- `a1_g = a1/g`

## Arquitectura
- `main.c`: punto de entrada; contiene `main()`.
- `artemis.h`: estructuras, constantes y prototipos.
- `artemis.c`: cálculos físicos, configuración y menú.
- `validaciones.h` y `validaciones.c`: lectura y validación de datos.
- `Makefile`: compilación automatizada.

Se utilizan estructuras para agrupar parámetros y resultados, un arreglo de dos aceleraciones para representar las fases y punteros para pasar estructuras a las funciones. Las funciones están separadas según su responsabilidad.

## Funciones del simulador
1. Consultar velocidad y altura al desacople.
2. Consultar velocidad al apagar motores y tiempo de la segunda fase.
3. Calcular la altura máxima ante una falla de motores.
4. Expresar la aceleración de la primera fase en múltiplos de gravedad.
5. Mostrar el informe completo.
6. Modificar parámetros y restaurar los valores originales.

Las entradas numéricas se validan por tipo y rango. También se verifica que la altura de la fase 1 sea inferior a la altura objetivo; si no se cumple, se conserva la configuración anterior.

## Compilación
Con GCC y Make:
```bash
make
./artemis
```
En Windows con MinGW:
```bash
gcc -Wall -Wextra -std=c11 -pedantic main.c artemis.c validaciones.c -o artemis.exe -lm
artemis.exe
```

## Caso de prueba con los valores originales
- `v1 = 2.400,00 m/s`
- `y1 = 144.000,00 m`
- `v2 ≈ 2.481,93 m/s`
- `t2 ≈ 6,55 s`
- `Delta h ≈ 314.285,71 m`
- `hmax ≈ 474.285,71 m`
- `a1/g ≈ 2,041 g`

## Uso de IA
Se utilizó ChatGPT como apoyo para interpretar los requisitos, organizar la modularización, revisar la aplicación de las ecuaciones de MRUV y proponer casos de prueba y validaciones. El equipo debe revisar, compilar, probar y comprender el código, registrar los prompts efectivamente utilizados y documentar las modificaciones propias antes de la entrega.

## Completar por el equipo
- Integrantes: 
Pozzi Santiago Martin k1.3
Ojeda Maximiliano k1.3
Parcellier Malcom k1.3
Baez Sosa Marcos Esteba k1.3
Dominguez Fausto k1.3

- URL del repositorio público: 
https://github.com/PozziSanti/Artemis_Escenario_1

- Historial de commits de todos los integrantes.
$ git log --oneline
597460f (HEAD -> main, origin/main) Incorporación del sistema de compilación
fd1593f extencion del codigo
ecc76d1 Estructura inicial del simulador Artemis
- Evidencias de compilación y pruebas.
COMPILACIÓN DE EVIDENCIAS Y PRUEBAS

Simulador de Misiones Artemis – Escenario 1

Universidad: Universidad Tecnológica Nacional – Facultad Regional Resistencia
Proyecto: Simulador de Misiones Artemis
Lenguaje: C
Repositorio: https://github.com/PozziSanti/Artemis_Escenario_1

1. Objetivo de las pruebas

El objetivo de esta sección es documentar las pruebas realizadas sobre el simulador, verificando que los cálculos físicos sean correctos, que las opciones del menú funcionen adecuadamente y que el programa controle los datos ingresados por el usuario.

Se busca comprobar tanto el funcionamiento normal del sistema como su comportamiento ante entradas inválidas.

2. Evidencia de compilación

Prueba 1: Compilación del programa

Se verifica que todos los archivos fuente se compilen correctamente utilizando GCC, sin errores ni advertencias.

Comando utilizado:

gcc -Wall -Wextra -std=c11 -pedantic main.c artemis.c validaciones.c -o artemis.exe -lm

Resultado esperado:

Compilación exitosa.

Generación del ejecutable artemis.exe.

Ausencia de errores de compilación.

Evidencia 1: Captura de la terminal mostrando el comando ejecutado y la compilación exitosa.

[INSERTAR CAPTURA]

3. Pruebas funcionales

Prueba 2: Cálculo de la primera fase

Se selecciona la opción correspondiente al cálculo de velocidad y altura al momento del desprendimiento de los propulsores laterales.

Parámetros:

Velocidad inicial: 0 m/s.

Aceleración: 20 m/s².

Tiempo: 120 segundos.

Resultados esperados:

Magnitud

Resultado

Velocidad final

2400 m/s

Altura alcanzada

144000 m

Evidencia 2: Captura de pantalla mostrando los resultados obtenidos.

[INSERTAR CAPTURA]

Prueba 3: Cálculo de la segunda fase

Se verifica la velocidad alcanzada cuando el cohete llega a los 160.000 metros de altura.

Parámetros:

Velocidad inicial: 2400 m/s.

Aceleración: 12,5 m/s².

Altura objetivo: 160000 m.

Resultados esperados:

Magnitud

Resultado

Velocidad final

2481,93 m/s

Tiempo de segunda fase

6,55 s

Evidencia 3: Captura de pantalla mostrando el cálculo de la segunda fase.

[INSERTAR CAPTURA]

Prueba 4: Simulación de fallo de motores

Se comprueba la altura máxima que alcanza el cohete luego de un fallo de motores a los 160.000 metros, considerando la gravedad terrestre y el movimiento ascendente por inercia.

Parámetros:

Altura inicial: 160000 m.

Velocidad inicial: 2481,93 m/s.

Gravedad: 9,80 m/s².

Resultados esperados:

Magnitud

Resultado

Altura adicional

314285,71 m

Altura máxima

474285,71 m

Evidencia 4: Captura de pantalla mostrando el resultado de la simulación.

[INSERTAR CAPTURA]

Prueba 5: Aceleración expresada en unidades de gravedad

Se verifica la relación entre la aceleración de la primera fase y la gravedad terrestre.

Parámetros:

Aceleración: 20 m/s².

Gravedad: 9,80 m/s².

Resultado esperado:

Magnitud

Resultado

Aceleración relativa

2,041 g

Evidencia 5: Captura de pantalla mostrando el resultado obtenido.

[INSERTAR CAPTURA]

Prueba 6: Informe completo

Se selecciona la opción de visualización del informe completo para comprobar que el sistema pueda mostrar todos los resultados de la simulación en una misma ejecución.

Resultado esperado:

Velocidad y altura al desprendimiento de los SRB.

Velocidad al alcanzar los 160.000 metros.

Tiempo de la segunda fase.

Altura adicional por inercia.

Altura máxima.

Aceleración expresada en unidades de gravedad.

Evidencia 6: Captura del informe completo generado por el programa.

[INSERTAR CAPTURA]

4. Pruebas de validación

Estas pruebas buscan comprobar que el programa controle correctamente los datos ingresados por el usuario.

N.º

Caso de prueba

Resultado esperado

7

Ingresar una opción inexistente en el menú.

El programa informa que la opción no es válida.

8

Ingresar letras en un campo numérico.

El programa rechaza la entrada y solicita un valor válido.

9

Ingresar valores negativos en parámetros que no admiten negativos.

El programa rechaza el valor.

10

Ingresar una altura objetivo inferior a la altura alcanzada en la primera fase.

El programa informa que la altura no es válida.

11

Ingresar valores fuera de los rangos permitidos.

El programa impide continuar con datos inválidos.

Evidencia 7: Captura de las pruebas de ingreso de datos incorrectos y de las respuestas del programa.

[INSERTAR CAPTURA]

5. Prueba de modificación de parámetros

Se verifica que el usuario pueda modificar los parámetros de la simulación y que los resultados se actualicen de acuerdo con los nuevos valores.

Resultado esperado:

El sistema permite modificar los parámetros disponibles.

Los nuevos valores son utilizados en los cálculos posteriores.

Se pueden restaurar los valores originales.

Evidencia 8: Captura mostrando la modificación de un parámetro y los resultados actualizados.

[INSERTAR CAPTURA]

6. Evidencia del control de versiones

Se documenta el desarrollo progresivo del proyecto mediante Git y GitHub.

Se deben incluir capturas que permitan observar:

El repositorio público del proyecto.

Los archivos fuente incorporados.

El historial de commits.

Los mensajes descriptivos de cada commit.

Evidencia 9: Captura del historial de commits de GitHub.

[INSERTAR CAPTURA]

Repositorio:

https://github.com/PozziSanti/Artemis_Escenario_1

7. Conclusión

A través de las pruebas propuestas se busca verificar el correcto funcionamiento del simulador de Misiones Artemis, comprobando la precisión de los cálculos físicos, el funcionamiento de las distintas opciones del menú y la validación de los datos ingresados.

La compilación de evidencias permite documentar el proceso de desarrollo y demostrar el cumplimiento de los requisitos funcionales y técnicos establecidos para el Escenario 1.

Nota: Las pruebas y evidencias deberán completarse con las capturas obtenidas durante la ejecución real del programa.
- Enlace al video grupal de hasta 5 minutos.
https://drive.google.com/file/d/17G7DW6gSwVk8nenaUpW96LNncJrsre2C/view?usp=sharing
