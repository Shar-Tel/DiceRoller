# Dados (Arduino)

Español
-------

Programa para Arduino que simula el lanzamiento de distintos tipos de dados. Está diseñado para funcionar con una pantalla de 4 dígitos de 7 segmentos y tres botones.

Características principales:
- Selección del número de caras del dado (por defecto: 100 caras).
- Botón para lanzar el dado y mostrar el resultado en la pantalla.
- Botón para tirar iniciativa según una variante de Rolemaster: lanza 2d10 y suma los resultados; si alguno de los dados obtiene 9 o 10, se vuelve a lanzar ese dado y se suma la nueva tirada (repetible si vuelve a sacar 9 o 10).



Uso básico:
1. Conectar la pantalla y los botones al Arduino según el esquema de tu proyecto.
2. Subir el programa al Arduino.
3. Usar el botón de selección para elegir el número de caras.
4. Pulsar el botón de lanzar para obtener un resultado aleatorio.
5. Pulsar el botón de iniciativa para la tirada especial de Rolemaster.

Conexiones:
Para la pantalla, recuerda colocar una resistencia (de entre 220Ω y 330Ω) en serie con cada uno de los pines de los segmentos para limitar la corriente y no quemar ni el display ni el Arduino.

Pantalla 5641AS (Display de 4 dígitos)
Control de Dígitos (GND / Cátodos comunes):
    Dígito 1 (Pin 12 del display) ➔ Pin 6 del Arduino.
    Dígito 2 (Pin 9 del display) ➔ Pin 9 del Arduino.
    Dígito 3 (Pin 8 del display) ➔ Pin 10 del Arduino.
    Dígito 4 (Pin 6 del display) ➔ Pin 11 del Arduino.
Control de Segmentos (Ánodos / Forma de los números):
    Segmento A (Pin 11 del display) ➔ Pin 2 del Arduino.
    Segmento B (Pin 7 del display) ➔ Pin 3 del Arduino.
    Segmento C (Pin 4 del display) ➔ Pin 4 del Arduino.
    Segmento D (Pin 2 del display) ➔ Pin 5 del Arduino.
    Segmento E (Pin 1 del display) ➔ Pin A0 del Arduino.
    Segmento F (Pin 10 del display) ➔ Pin 7 del Arduino.
    Segmento G (Pin 5 del display) ➔ Pin 8 del Arduino.
    (El punto decimal o DP, que es el pin 3 del display, no se usa, déjalo sin conectar).

Botones (Pulsadores)
Como el código utiliza INPUT_PULLUP en la configuración inicial, no necesitas añadir resistencias externas. Simplemente conecta un terminal de cada botón al pin correspondiente del Arduino y el otro terminal directamente a GND (tierra).

Botón A (Lanzar dado): Un terminal al Pin 12 ➔ Otro terminal a GND.
Botón B (Cambiar dado): Un terminal al Pin A2 ➔ Otro terminal a GND.
Botón C (Iniciativa): Un terminal al Pin A3 ➔ Otro terminal a GND.

Imagen del dispositivo:
![IMG_20250723_113506](https://github.com/user-attachments/assets/524c102b-7567-4946-8701-4a8f6ecc98ed)

English
-------

Arduino program that simulates rolling different types of dice. It is designed to work with a 4-digit 7-segment display and three buttons.

Main features:
- Select number of faces for the die (default: 100 faces).
- Button to roll the die and show the result on the display.
- Button to roll initiative using a Rolemaster variant: roll 2d10 and sum results; if any die shows 9 or 10, that die is re-rolled and the new roll is added to the total (repeatable if 9 or 10 occurs again).



Basic usage:
1. Wire the display and buttons to the Arduino according to your project's wiring.
2. Upload the sketch to the Arduino.
3. Use the select button to choose the number of faces.
4. Press the roll button to get a random result.
5. Press the initiative button for the special Rolemaster roll.

Connections:
For the display, remember to place a resistor (between 220Ω and 330Ω) in series with each of the segment pins to limit the current and avoid burning out either the display or the Arduino.

5641AS Display (4-Digit Display)
Digit Control (GND / Common Cathodes):
    Digit 1 (Display pin 12) ➔ Arduino pin 6.
    Digit 2 (Display pin 9) ➔ Arduino pin 9.
    Digit 3 (Display pin 8) ➔ Arduino pin 10.
    Digit 4 (Display pin 6) ➔ Arduino pin 11.
    Segment Control (Anodes / Shape of the numbers):
Segment A (Display pin 11) ➔ Arduino pin 2.
    Segment B (Display pin 7) ➔ Arduino pin 3.
    Segment C (Display pin 4) ➔ Arduino pin 4.
    Segment D (Display pin 2) ➔ Arduino pin 5.
    Segment E (Display pin 1) ➔ Arduino pin A0.
    Segment F (Display pin 10) ➔ Arduino pin 7.
    Segment G (Display pin 5) ➔ Arduino pin 8.
    (The decimal point or DP, which is display pin 3, is not used; leave it unconnected).

Buttons (Pushbuttons)
Since the code uses INPUT_PULLUP in the initial configuration, you do not need to add external resistors. Simply connect one terminal of each button to the corresponding Arduino pin, and the other terminal directly to GND (ground).

Button A (Roll dice): One terminal to Pin 12 ➔ Other terminal to GND.
Button B (Change dice): One terminal to Pin A2 ➔ Other terminal to GND.
Button C (Initiative): One terminal to Pin A3 ➔ Other terminal to GND. 

Image of the device:
![IMG_20250723_113506](https://github.com/user-attachments/assets/524c102b-7567-4946-8701-4a8f6ecc98ed)

License
-------
Indica la licencia aquí (p. ej. MIT) o añade más detalles del proyecto según sea necesario.


