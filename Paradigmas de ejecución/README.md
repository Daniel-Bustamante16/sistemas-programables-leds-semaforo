# delay() vs millis(): Temporización en Arduino

## Resumen

Esta práctica compara dos maneras de medir el tiempo en Arduino: la función `delay()` y la función `millis()`. Para ello se controlaron tres LEDs (rojo, amarillo y verde) con una placa Arduino UNO R4 WiFi.

El mismo circuito se programó dos veces. En la primera versión se usa `delay()`, que detiene el programa mientras espera. En la segunda se usa `millis()`, con la que el programa sigue corriendo sin pausas mientras se cumple cada intervalo.

## Objetivos

* Distinguir la temporización bloqueante de la no bloqueante.
* Controlar tres LEDs con `delay()`.
* Lograr el mismo control con `millis()`.
* Reconocer las ventajas y las limitaciones de cada método.
* Preparar el terreno para atender eventos externos sin detener el programa.

## Materiales

* Arduino UNO R4 WiFi
* Arduino IDE
* Protoboard
* LED rojo, LED amarillo y LED verde
* Resistencias limitadoras de corriente (220 – 330 Ω)
* Cables jumper

## Conexiones

| Pin | Componente |
|-----|------------|
| D2 | LED rojo |
| D3 | LED amarillo |
| D4 | LED verde |

Cada LED lleva una resistencia en serie y su cátodo va a GND. La secuencia es: verde 8 s, amarillo 2 s y rojo 6 s.

## Diagrama

Este esquema muestra cómo se conectaron los tres LEDs.

![Esquema del circuito](Diagrama/delay-millisimg.png)

[Abrir la carpeta de diagramas](diagramas)

## Código

Hay dos programas, uno con `delay()` y otro con `millis()`, y ambos repiten la misma secuencia de tiempos (verde 8 s, amarillo 2 s, rojo 6 s).

* [Código con delay()](codigos/delay.ino)
* [Código con millis()](codigos/milis.ino)

## Video de demostración

En el video se ve el circuito funcionando con las dos versiones y se aprecia la diferencia de comportamiento entre `delay()` y `millis()`.

* [Ver el video de millis()](https://youtube.com/shorts/SLzMT97ppjg?si=EJtjsvkn1-rs28xF)
* [Ver el video de delay()](https://youtube.com/shorts/1iwWOfG87Y0?feature=share)

[Abrir la carpeta de videos](videos)

## Pruebas y resultados

Las dos versiones encendieron los LEDs en el orden correcto y con los tiempos programados.

Con `delay()`, el programa se queda totalmente detenido durante cada pausa y no puede atender ninguna otra tarea. Con `millis()`, en cambio, el programa sigue funcionando todo el tiempo: en cada vuelta de `loop()` compara el tiempo transcurrido y queda libre para realizar otras operaciones.

Esta comparación mostró en la práctica por qué `millis()` es la mejor opción cuando el sistema debe reaccionar a eventos externos, como botones o sensores.

## Reporte

El reporte explica el funcionamiento de ambas versiones, presenta el análisis comparativo entre `delay()` y `millis()` y recoge las conclusiones de la práctica.

[Abrir el reporte](reporte/Reporte_delay_millis.pdf)

## Conclusiones

La práctica permitió contrastar de manera directa dos formas de manejar el tiempo en Arduino. `delay()` es fácil de implementar, pero bloquea por completo la ejecución del programa. `millis()` exige una lógica algo más elaborada (variables de estado y comparación de tiempos), pero a cambio el programa permanece siempre activo y puede responder a otros eventos.

Con esto se dejaron las bases para construir sistemas más complejos, como máquinas de estados finitos con entradas externas, donde el uso de `millis()` es indispensable.
