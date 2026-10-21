[README (1).md](https://github.com/user-attachments/files/33751461/README.1.md)

# Driver de software para un relevador con Arduino

## Resumen

Esta práctica de Sistemas Programables consiste en controlar dos actuadores mediante una misma clase en C++ llamada `Relevador`. El sistema utiliza un Arduino UNO R4 WiFi, un motorreductor conectado a un puente H L298N y un LED conectado con lógica activa en bajo.

El motor se activa con un nivel `HIGH`, mientras que el LED se enciende con `LOW`. La clase se encarga de traducir las órdenes de encendido y apagado al nivel que corresponde en cada caso. Así, el programa principal puede trabajar con las mismas instrucciones para ambos dispositivos sin manejar directamente los pines.

El control se realiza desde el Monitor Serie. Para evitar cambios demasiado rápidos, cada objeto aplica un intervalo mínimo de 1000 ms entre conmutaciones. La medición del tiempo se hace con `millis()`, sin utilizar `delay()`.

## Objetivos

* Representar el funcionamiento de un actuador mediante una clase con atributos privados y métodos públicos.
* Comprender la diferencia entre un dispositivo activo en alto y uno activo en bajo.
* Controlar el motor y el LED con órdenes enviadas desde el Monitor Serie.
* Mantener un tiempo mínimo de un segundo entre cambios de estado, sin detener la recepción de comandos.
* Inicializar ambos actuadores apagados y revisar su comportamiento al reiniciar el Arduino.
* Reconocer la separación entre la señal de control del Arduino y la alimentación de potencia del motor.

## Materiales

* 1 Arduino UNO R4 WiFi y cable USB-C.
* 1 módulo puente H L298N.
* 1 motorreductor DC tipo TT de 3 a 6 V.
* 2 pilas 18650 con portapilas en serie, con voltaje nominal aproximado de 7.4 V.
* 1 LED.
* 1 resistencia en serie con el LED; la guía indica 220 Ω.
* 1 protoboard.
* Cables jumper macho-macho y macho-hembra.
* Arduino IDE y Monitor Serie.

El valor de la resistencia debe revisarse según la placa y el LED utilizados. En el UNO R4 WiFi, la combinación de 5 V, un LED con caída cercana a 2 V y 220 Ω puede superar los 8 mA por pin indicados en la guía. Conviene revisar con el docente un valor mayor, como 680 Ω, y registrar el componente instalado realmente.

## Conexiones

| Componente o terminal | Conexión | Función |
|---|---|---|
| D7 del Arduino | IN1 del L298N | Señal de control del motor, activa en alto. |
| IN2 del L298N | GND | Mantiene fija la segunda entrada del canal. |
| Terminales del motor | OUT1 y OUT2 del L298N | Salidas de potencia hacia el motor. |
| Positivo del portapilas | Entrada +12V del L298N | Alimentación de potencia del módulo. |
| Negativo del portapilas | GND del L298N | Retorno de la fuente del motor. |
| GND del Arduino | GND del L298N | Referencia común para las señales. |
| 5V del Arduino | Ánodo del LED, pata larga | Alimentación del LED. |
| Cátodo del LED | Resistencia en serie y después D6 | Control del LED, activo en bajo. |
| ENA del L298N | Jumper colocado según la guía | Habilita el canal utilizado. |
| 5V-EN del L298N | Según la guía y revisión del módulo | Configuración de alimentación lógica. |
| Terminal +5V del L298N | Sin conexión al Arduino | Evita unir las salidas de alimentación. |

El motor recibe energía del portapilas a través del L298N; no se alimenta desde el pin de 5 V del Arduino. Antes de energizar se deben revisar la polaridad, la tierra común y la tensión que recibe el motor. El nombre de la entrada `+12V` del módulo no significa que en esta práctica deban aplicarse 12 V.

El LED se conecta entre 5 V y D6, con la resistencia en serie. Cuando D6 está en `LOW`, la corriente circula desde 5 V hacia el pin y el LED enciende. Cuando D6 está en `HIGH`, el LED se apaga.

## Diagrama

El proyecto contempla un diagrama de estados y un esquema de conexiones. El primero muestra los estados **APAGADO** y **ENCENDIDO**, el estado inicial y la condición de un segundo para aceptar una transición. El segundo permite identificar las conexiones entre el Arduino, la etapa de potencia, el motor y el LED.

Para una simulación adaptada con UNO R3 y L293D, se conservan D7 y D6 y la lógica del programa. Esa adaptación debe identificarse por separado del montaje físico con UNO R4 WiFi y L298N, ya que las conexiones de los dos controladores de motor son distintas.

[Abrir la carpeta de diagramas](diagrama/)

## Código

El programa está organizado en un solo archivo `.ino`. La clase `Relevador` guarda el pin, el tipo de activación, el estado lógico y el momento del último cambio. Sus métodos principales son:

* `iniciar()`: configura la salida y deja el actuador apagado.
* `encender()`: solicita el encendido y comprueba el tiempo mínimo.
* `apagar()`: solicita el apagado con la misma regla de tiempo.
* `estaEncendido()`: devuelve el estado lógico almacenado.
* `faltaMs()`: informa cuántos milisegundos faltan para permitir otra conmutación.

Se crean dos objetos de la misma clase:

```cpp
Relevador motor(7, false); // Activo en alto.
Relevador led(6, true);    // Activo en bajo.
```

Cada objeto controla su propio tiempo. Si una orden llega demasiado pronto, se rechaza sin modificar el pin. Si se solicita el estado que el actuador ya tiene, la orden se acepta sin conmutar ni reiniciar el contador. La primera conmutación también espera un segundo desde la inicialización.

En `setup()` se inicializan los actuadores antes de abrir la comunicación serie. Las llamadas a `digitalWrite()` quedan dentro de la clase, mientras que `loop()` se dedica a leer los comandos disponibles.

[Abrir la carpeta del código fuente](codigo/)

### Comandos del Monitor Serie

Configurar el Monitor Serie a **9600 baudios**, seleccionar **Nueva línea** y enviar una orden por línea. El programa también admite terminaciones con retorno de carro y convierte las letras recibidas a mayúsculas.

| Comando | Acción |
|---|---|
| `M1` | Encender el motor. |
| `M0` | Apagar el motor. |
| `L1` | Encender el LED. |
| `L0` | Apagar el LED. |
| `E` | Mostrar el estado del motor y del LED. |

## Video de demostración

La demostración permite mostrar el montaje y relacionar las órdenes del Monitor Serie con la respuesta de los actuadores. También sirve para documentar el rechazo de cambios demasiado rápidos y el comportamiento del sistema después de presionar RESET.

[Abrir la carpeta del video](video/)

## Pruebas y resultados

Las siguientes pruebas permiten comparar el funcionamiento del circuito con los requisitos de la práctica. Los resultados observados y sus evidencias se documentan en el reporte.

| Prueba | Comportamiento esperado |
|---|---|
| Inicio del programa | El motor y el LED quedan apagados al ejecutar `iniciar()`. |
| Órdenes `M1` y `M0` | El motor cambia de estado cuando se cumple el intervalo mínimo. |
| Órdenes `L1` y `L0` | El LED enciende con `LOW` y se apaga con `HIGH`. |
| `M1` seguido de `M0` antes de un segundo | Se rechaza el apagado y se mantiene el motor encendido. |
| Nueva orden de apagado después del intervalo | Se acepta el cambio y el motor se apaga. |
| Repetir una orden del estado actual | No se produce otra conmutación ni se reinicia el contador. |
| RESET con el motor encendido | Ambos actuadores quedan apagados cuando se ejecuta la inicialización. |
| Configurar el LED como activo en alto por error | La respuesta física del LED queda invertida respecto del estado lógico. |

El estado consultado por software representa la orden aplicada, no una medición física del actuador. Además, el apagado durante la inicialización no garantiza por sí solo el nivel de los pines antes de que empiece el programa; ese periodo depende también del circuito.

## Reporte

El reporte desarrolla el objetivo, el fundamento de la práctica, los materiales, las conexiones, el diseño de la clase y el funcionamiento del código. También reúne la fotografía del montaje físico, las evidencias de las pruebas, los resultados observados, las respuestas a las preguntas de reflexión y las conclusiones.

[Abrir la carpeta del reporte](reporte/)

## Conclusiones

Esta práctica ayuda a entender cómo aplicar la programación orientada a objetos al control de un dispositivo. Al concentrar la lógica en una clase, las órdenes conservan el mismo significado aunque el motor y el LED necesiten niveles eléctricos diferentes para encenderse.

La restricción de tiempo queda dentro de cada objeto, por lo que no hace falta repetirla cada vez que se controla una salida. El uso de `millis()` permite seguir recibiendo comandos mientras transcurre ese intervalo. También resulta necesario distinguir entre el estado que guarda el programa y lo que ocurre realmente en el circuito: el código debe acompañarse de conexiones correctas y pruebas que confirmen el comportamiento de los actuadores.
