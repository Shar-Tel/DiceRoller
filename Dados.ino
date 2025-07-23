// LANZADOR DE DADOS EN ARDUINO. VERSIÓN 1.0
//Por Ximo León

#define Dig1 6
#define Dig2 9
#define Dig3 10
#define Dig4 11
#define DIGIT_ON LOW
#define DIGIT_OFF HIGH
#define DISPLAY_BRIGHTNESS 5000
boolean duiz = false;
boolean hon = false;
#define segA 2
#define segB 3
#define segC 4
#define segD 5
#define segE A0
#define segF 7
#define segG 8
#define longDados 7

int listaDados[] = {4, 6, 8, 10, 12, 20, 100};
int dadoElegido = 6; //El número de caras del dado elegido, por defecto el de 100
int numero = 0;
bool esTirada = true;
int buttonApin = 12;
int buttonBpin = 0;
int buttonCpin = 1;
byte estadoAnteriorA = HIGH;
byte estadoAnteriorB = HIGH;
byte estadoAnteriorC = HIGH;

void setup()
{
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(Dig1, OUTPUT);
  pinMode(Dig2, OUTPUT);
  pinMode(Dig3, OUTPUT);
  pinMode(Dig4, OUTPUT);
  Serial.begin(9600);
  pinMode(buttonApin, INPUT_PULLUP);

}

void loop()
{

  //APRETAMOS EL BOTÓN A
  if (digitalRead(buttonApin) == LOW && estadoAnteriorA == HIGH)
  {
    estadoAnteriorA = LOW;
    botonA();
  }

  //SOLTAMOS EL BOTÓN A
  if (digitalRead(buttonApin) == HIGH && estadoAnteriorA == LOW)
  {
    estadoAnteriorA = HIGH;
  }

  //APRETAMOS EL BOTÓN B
  if (digitalRead(buttonBpin) == LOW && estadoAnteriorB == HIGH)
  {
    estadoAnteriorB = LOW;
    botonB();
  }
  //SOLTAMOS EL BOTÓN B
  if (digitalRead(buttonBpin) == HIGH && estadoAnteriorB == LOW)
  {
    estadoAnteriorB = HIGH;
  }
  //APRETAMOS EL BOTÓN C
  if (digitalRead(buttonCpin) == LOW && estadoAnteriorC == HIGH)
  {
    estadoAnteriorC = LOW;
    botonC();
  }
  //SOLTAMOS EL BOTÓN C
  if (digitalRead(buttonCpin) == HIGH && estadoAnteriorC == LOW)
  {
    estadoAnteriorC = HIGH;
  }
  dibujo();
  //   delay(5);
}


//Hace una tirada de dados
void botonA()
{
  int espera, iteraciones;
  randomSeed(millis());
  iteraciones = random(1, 20); //Hace un número aleatorio de tiradas y se queda con la última
    for ( int i = 0; i <= iteraciones; i++) {
      randomSeed(analogRead(1)); //Espera un tiempo aleatorio antes de cada tirada para que no coincidan los milisegundos
      espera = random(1, 100);
      delay(espera);
      randomSeed(millis()); //Esto parece que va mejor como semilla, pero sólo si funciona con botón
      numero = random(1, listaDados[dadoElegido] + 1);
      esTirada = true;
      //   Serial.println(numero);
      dibujo();
    }
}


//Cambia el tipo de dados elegido
void botonB()
{
  if (dadoElegido < longDados - 1)
  {
    dadoElegido++;
  }
  else {
    dadoElegido = 0;
  }
  //  Serial.println(dadoElegido);
  numero = listaDados[dadoElegido];
  esTirada = false;
  dibujo();
}

//Tira inicitiva. El resultado es sumar 2d10, pero si alguno saca 10, se tira otro dado y se suma a la iniciativa.
void botonC()
{
  //     Serial.println("Empiezo");
  numero = tiraD10() + tiraD10();
  esTirada = true;
  //      Serial.print("el resultado total es:");
  //   Serial.println(numero);
  dibujo();
}

//Tira 1d10. Si el resultado es 10 se vuelve a tirar y se suma al resultado que devuelve.s
int tiraD10()
{
  int resultado = 0;
  int espera;
  //Le pongo primero una espera aleatoria basada en leer un pin para que no haga todos los randoms en el mismo milisegundo
  randomSeed(analogRead(1));
  espera = random(1, 200);
  delay(espera);
  randomSeed(millis());
  resultado = random(1, 11);
  //   Serial.println(resultado);
  if (resultado == 10)
  {
    resultado += tiraD10();
  }
  return resultado;
}

//Dibuja un número en la posición que le digas
void dibujoIndividual(int posicion, int valor)
{
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
  //Turn off all digits
  digitalWrite(Dig1, DIGIT_OFF);
  digitalWrite(Dig2, DIGIT_OFF);
  digitalWrite(Dig3, DIGIT_OFF);
  digitalWrite(Dig4, DIGIT_OFF);
}

void dibujo() {

  duiz = false;
  hon = false;


  if (numero == 0)
  {
    dibujoIndividual(1, 11);
    dibujoIndividual(2, 12);
    dibujoIndividual(3, 11);
    dibujoIndividual(4, 0);
  }
  else {

    int figur = numero;
    //Si no es una tirada lleva d delante
    if (!esTirada) {
      //Según el número la d va en una posición
      if (figur >= 100)
      {
        digitalWrite(Dig1, DIGIT_ON);
      }
      else if (figur >= 10)
      {
        digitalWrite(Dig2, DIGIT_ON);
      }
      else
      {
        digitalWrite(Dig3, DIGIT_ON);
      }
      lightNumber(11);
      delayMicroseconds(DISPLAY_BRIGHTNESS);
    }
    //Dibujo el número
    for (int digit = 1 ; digit < 5 ; digit++) { //for loop to place the number in the right digit
      switch (digit) {
        case 1:
          if (figur > 999) {
            digitalWrite(Dig1, DIGIT_ON);
            lightNumber(figur / 1000); // for example 2511 / 1000 = 2
            figur %= 1000; // new value of figur = 511 figur = figur %1000

            delayMicroseconds(DISPLAY_BRIGHTNESS);
            if (figur < 100) {
              duiz = true;
              if (figur < 10) {
                hon = true;

              }

            } else duiz = false;
          }

          break;
        case 2:
          if (duiz == true) {
            digitalWrite(Dig2, DIGIT_ON);
            lightNumber(0);
            delayMicroseconds(DISPLAY_BRIGHTNESS);

          } if (hon == true) {
            break;
          }

          if (figur > 99 && figur < 1000) {
            digitalWrite(Dig2, DIGIT_ON);
            lightNumber(figur / 100);
            figur %= 100;
            delayMicroseconds(DISPLAY_BRIGHTNESS);
            if (figur < 10) {
              hon = true;

            } else hon = false;
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

            break;
          }
      }

      //Turn off all segments
      lightNumber(10);
      //Turn off all digits
      digitalWrite(Dig1, DIGIT_OFF);
      digitalWrite(Dig2, DIGIT_OFF);
      digitalWrite(Dig3, DIGIT_OFF);
      digitalWrite(Dig4, DIGIT_OFF);

    }

  }
}



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
    case 11: //El 11 será la d
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      break;
    case 12: //El 12 será la A
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
