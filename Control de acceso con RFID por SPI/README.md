# Control de acceso con lector RFID RC522 y Arduino

## Resumen

Esta práctica muestra cómo comunicar un Arduino con un lector RFID usando el bus SPI. Se armó un sistema de control de acceso con un Arduino UNO y un módulo RC522 que lee el UID (número único) de tarjetas y llaveros RFID.

El programa compara el UID leído con el de una tarjeta autorizada: si coincide, muestra "ACCESO PERMITIDO" en el Monitor serie y enciende un LED durante 2 segundos; si no coincide, muestra "ACCESO DENEGADO" y el LED permanece apagado. El tiempo del LED se controla con `millis()`, de modo que el programa sigue leyendo tarjetas mientras el LED está encendido.

## Objetivos

* Comprender el funcionamiento del bus SPI y el papel de sus líneas (SCK, MOSI, MISO y CS).
* Inicializar el bus SPI y el lector RC522 y verificar que hay comunicación con él.
* Leer el UID de una tarjeta y mostrarlo en el Monitor serie con cada byte separado por un espacio.
* Validar una tarjeta autorizada y controlar un LED sin bloquear el programa.
* Identificar qué pasa cuando falla una línea del bus (desconexión de MISO).

## Materiales

* 1 Arduino UNO
* Arduino IDE
* 1 módulo lector RFID RC522
* 1 tarjeta y 1 llavero RFID
* 1 protoboard
* 1 LED
* 1 resistencia de 220 Ω
* Cables de conexión
* Librerías `SPI` y `MFRC522` (Miguel Balboa, instalada desde el Library Manager) y Monitor serie

## Conexiones

| Pin del lector | Arduino UNO | Función |
|----------------|-------------|---------|
| SDA (SS) | D10 | Chip Select (CS) |
| SCK | D13 | Reloj del bus SPI |
| MOSI | D11 | Datos del Arduino hacia el lector |
| MISO | D12 | Datos del lector hacia el Arduino |
| RST | D9 | Reinicio del lector |
| 3.3V | 3.3V | Alimentación (no usar 5V) |
| GND | GND | Tierra común |
| IRQ | — | Sin conexión |

El LED se conecta al pin D7 a través de la resistencia de 220 Ω, y su pata corta va a GND.

## Diagrama

Este esquema muestra cómo se conectaron el lector RC522, el LED y el Arduino UNO.

![Esquema del circuito](Diagrama/rfid-conexiones-img.png)

[Abrir la carpeta de diagramas](Diagrama)

## Código

El programa está en un solo archivo, que inicializa el lector, lee las tarjetas y controla el LED.

* [Código del control de acceso](codigos/control_acceso_rfid.ino)

## Video de demostración

En el video se ve el sistema funcionando: la lectura del UID en el Monitor serie, el acceso permitido y denegado, el apagado automático del LED a los 2 segundos y la prueba de desconectar MISO.

* [Ver el video de la práctica](videos/)

[Abrir la carpeta de videos](videos)

## Pruebas y resultados

Se leyeron la tarjeta y el llavero y se anotó el UID de cada uno. Se eligió una de las tarjetas como autorizada y se guardó su UID dentro del programa.

* **Tarjeta autorizada:** el LED enciende y se apaga solo a los 2 segundos.
* **Tarjeta no autorizada:** el LED no enciende y se muestra "ACCESO DENEGADO".
* **Tarjeta no autorizada con el LED encendido:** se muestra "ACCESO DENEGADO", lo que demuestra que el programa no se quedó bloqueado esperando gracias al uso de `millis()`.
* **MISO (D12) desconectado:** al reiniciar el Arduino, el programa detecta que no hay comunicación con el lector (el registro de versión devuelve 0x00 o 0xFF) y lo indica en el Monitor serie. Al volver a conectar el cable, el sistema funciona con normalidad.

Esta prueba mostró que MISO es la línea por la que el lector responde al Arduino: sin ella no se puede leer ningún UID.

## Reporte

El reporte explica el objetivo y la descripción de la práctica, el material utilizado, las conexiones, el funcionamiento del código, las pruebas realizadas, las respuestas a las preguntas de la práctica y las conclusiones.

[Abrir el reporte](reporte/Reporte_Practica_RFID.pdf)

## Conclusiones

La práctica permitió comprobar cómo se comunica un Arduino con un dispositivo por SPI: el Arduino (maestro) genera el reloj por SCK, envía datos por MOSI, recibe las respuestas por MISO y elige con qué dispositivo habla mediante CS. Para conectar un segundo lector solo hay que compartir SCK, MOSI y MISO y usar un pin CS distinto para cada uno.

También se reforzó la importancia de usar `millis()` en lugar de `delay()`: así el programa sigue leyendo tarjetas mientras el LED está encendido y no se bloquea. Por último, verificar la comunicación con el lector al arrancar ayuda a detectar a tiempo fallas de cableado, como una línea desconectada.
