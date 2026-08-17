// LANZADOR DE DADOS EN ARDUINO. VERSIÓN 1.0
// Copyright 2026 Ximo León
// Código libre: MIT License.
//
// Este sketch controla un display de 4 dígitos y permite:
// - elegir entre varios tipos de dados (d4, d6, d8, d10, d12, d20 y d100).
// - lanzar una tirada aleatoria del dado seleccionado.
// - simular una tirada de iniciativa con dos d10 y reroll en caso de sacar 9 o 10.

// --- Configuración de los pines del display ---
#define Dig1 6
#define Dig2 9
#define Dig3 10
#define Dig4 11
#define DIGIT_ON LOW
#define DIGIT_OFF HIGH
#define DISPLAY_BRIGHTNESS 5000
boolean duiz = false;  // Marca si el display muestra un cero intermedio.
// Indica si el primer dígito debe quedar en blanco.
boolean hon = false;
#define segA 2
#define segB 3
#define segC 4
#define segD 5
#define segE A0
#define segF 7
#define segG 8
#define longDados 7

// Lista de dados disponibles. El índice elegido se usa para saber
// cuántas caras tiene el dado.
int listaDados[] = {4, 6, 8, 10, 12, 20, 100};
int dadoElegido = 6;  // El número de caras del dado elegido, por defecto d100.
int numero = 0;       // Valor que se va a mostrar en el display.
// Indica si el valor actual es una tirada o una selección.
bool esTirada = true;

// --- Pines de los botones ---
int buttonApin = 12;  // Botón para lanzar el dado.
int buttonBpin = A2;   // Botón para cambiar el tipo de dado. En el prototipo gasto el 0.
int buttonCpin = A3;   // Botón para lanzar iniciativa. En el prototipo gasto el 1.

// Estado anterior de cada botón para detectar cambios de estado.
byte estadoAnteriorA = HIGH;
byte estadoAnteriorB = HIGH;
byte estadoAnteriorC = HIGH;

void setup() {
  // Configura los pines de los segmentos como salidas.
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);

  // Configura los pines de cada dígito como salidas.
  pinMode(Dig1, OUTPUT);
  pinMode(Dig2, OUTPUT);
  pinMode(Dig3, OUTPUT);
  pinMode(Dig4, OUTPUT);

  // Activa el puerto serie para depurar si hace falta.
  Serial.begin(9600);

  // El botón A,B y C usan la resistencia pull-up interna.
  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);
  pinMode(buttonCpin, INPUT_PULLUP);
}

void loop() {
  // Detecta si se ha pulsado cada botón y ejecuta la acción
  // solo una vez por pulsación.

  if (digitalRead(buttonApin) == LOW && estadoAnteriorA == HIGH) {
    estadoAnteriorA = LOW;
    botonA();
  }

  if (digitalRead(buttonApin) == HIGH && estadoAnteriorA == LOW) {
    estadoAnteriorA = HIGH;
  }

  if (digitalRead(buttonBpin) == LOW && estadoAnteriorB == HIGH) {
    estadoAnteriorB = LOW;
    botonB();
  }

  if (digitalRead(buttonBpin) == HIGH && estadoAnteriorB == LOW) {
    estadoAnteriorB = HIGH;
  }

  if (digitalRead(buttonCpin) == LOW && estadoAnteriorC == HIGH) {
    estadoAnteriorC = LOW;
    botonC();
  }

  if (digitalRead(buttonCpin) == HIGH && estadoAnteriorC == LOW) {
    estadoAnteriorC = HIGH;
  }

  dibujo();
}

// Hace una tirada del dado elegido, con varias iteraciones rápidas para dar
// sensación de animación.
void botonA() {
  int espera;
  int iteraciones;

  randomSeed(millis());
  iteraciones = random(1, 20);
  for (int i = 0; i <= iteraciones; i++) {
    randomSeed(analogRead(1));
    espera = random(1, 100);
    delay(espera);

    randomSeed(millis());
    numero = random(1, listaDados[dadoElegido] + 1);
    esTirada = true;
    dibujo();
  }
}

// Cambia el tipo de dado mostrado y actualiza el número.
void botonB() {
  if (dadoElegido < longDados - 1) {
    dadoElegido++;
  } else {
    dadoElegido = 0;
  }

  numero = listaDados[dadoElegido];
  esTirada = false;
  dibujo();
}

// Realiza una tirada de iniciativa: suma dos d10 con reroll en caso de 9 y 10. Si se quiere usar otro tipo de iniciativa, cambiar aquí.
void botonC() {
  numero = tiraD10() + tiraD10();
  esTirada = true;
  dibujo();
}

// Tira un d10. Si sale 9 o 10, se vuelve a tirar y se suma el nuevo valor.
int tiraD10() {
  int resultado = 0;
  int espera;

  randomSeed(analogRead(1));
  espera = random(1, 200);
  delay(espera);

  randomSeed(millis());
  resultado = random(1, 11);  
  if (resultado == 10 || resultado==9) {
    resultado += tiraD10();
  }

  return resultado;
}

// Dibuja un número concreto en una de las cuatro posiciones del display.
void dibujoIndividual(int posicion, int valor) {
  switch (posicion) {
    case 1:
      digitalWrite(Dig1, DIGIT_ON);
      break;
    case 2:
      digitalWrite(Dig2, DIGIT_ON);
      break;
    case 3:
      digitalWrite(Dig3, DIGIT_ON);
      break;
    case 4:
      digitalWrite(Dig4, DIGIT_ON);
      break;
  }

  lightNumber(valor);
  delayMicroseconds(DISPLAY_BRIGHTNESS);

  lightNumber(10);
  digitalWrite(Dig1, DIGIT_OFF);
  digitalWrite(Dig2, DIGIT_OFF);
  digitalWrite(Dig3, DIGIT_OFF);
  digitalWrite(Dig4, DIGIT_OFF);
}

// Dibuja el número actual en el display según el modo actual.
void dibujo() {
  duiz = false;
  hon = false;

  if (numero == 0) {
    dibujoIndividual(1, 11);
    dibujoIndividual(2, 12);
    dibujoIndividual(3, 11);
    dibujoIndividual(4, 0);
    return;
  }

  int figur = numero;

  if (!esTirada) {
    if (figur >= 100) {
      digitalWrite(Dig1, DIGIT_ON);
    } else if (figur >= 10) {
      digitalWrite(Dig2, DIGIT_ON);
    } else {
      digitalWrite(Dig3, DIGIT_ON);
    }
    lightNumber(11);
    delayMicroseconds(DISPLAY_BRIGHTNESS);
  }

  for (int digit = 1; digit < 5; digit++) {
    switch (digit) {
      case 1:
        if (figur > 999) {
          digitalWrite(Dig1, DIGIT_ON);
          lightNumber(figur / 1000);
          figur %= 1000;
          delayMicroseconds(DISPLAY_BRIGHTNESS);

          if (figur < 100) {
            duiz = true;
            if (figur < 10) {
              hon = true;
            }
          } else {
            duiz = false;
          }
        }
        break;

      case 2:
        if (duiz == true) {
          digitalWrite(Dig2, DIGIT_ON);
          lightNumber(0);
          delayMicroseconds(DISPLAY_BRIGHTNESS);
        }
        if (hon == true) {
          break;
        }

        if (figur > 99 && figur < 1000) {
          digitalWrite(Dig2, DIGIT_ON);
          lightNumber(figur / 100);
          figur %= 100;
          delayMicroseconds(DISPLAY_BRIGHTNESS);
          if (figur < 10) {
            hon = true;
          } else {
            hon = false;
          }
        }
        break;

      case 3:
        if (hon == true) {
          digitalWrite(Dig3, DIGIT_ON);
          lightNumber(0);
          delayMicroseconds(DISPLAY_BRIGHTNESS);
          break;
        }

        if (figur > 9 && figur < 100) {
          digitalWrite(Dig3, DIGIT_ON);
          lightNumber(figur / 10);
          figur %= 10;
          delayMicroseconds(DISPLAY_BRIGHTNESS);
        }
        break;

      case 4:
        if (figur < 10) {
          digitalWrite(Dig4, DIGIT_ON);
          lightNumber(figur);
          delayMicroseconds(DISPLAY_BRIGHTNESS);
        }
        break;
    }

    lightNumber(10);
    digitalWrite(Dig1, DIGIT_OFF);
    digitalWrite(Dig2, DIGIT_OFF);
    digitalWrite(Dig3, DIGIT_OFF);
    digitalWrite(Dig4, DIGIT_OFF);
  }
}

// Convierte un valor numérico en la señal correcta de segmentos.
void lightNumber(int numberToDisplay) {
#define SEGMENT_ON HIGH
#define SEGMENT_OFF LOW
  switch (numberToDisplay) {
    case 0:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_OFF);
      break;
    case 1:
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;
    case 2:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 3:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 4:
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 5:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 6:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 7:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;
    case 8:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 9:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 10:
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;
    case 11:  // La letra d.
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 12:  // La letra A.
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;
  }
}
