//Definiciones de los pines de entrada/botones
#define cdIn 2
#define auxIn 3
#define phonoIn 4
#define tapeIn 5
#define tunnerIn 6
#define muteIn 7

//Definiciones de los pines de salida
#define cdOut 8
#define auxOut 9
#define phonoOut 10
#define tapeOut 11
#define tunnerOut 12

typedef enum {
  cd,
  aux,
  phono,
  tape,
  tunner,
  mute
} keys_e;


void Init(void);

keys_e getKey (void);


const uint8_t entradas [] = {cdIn, auxIn, phonoIn, tapeIn, tunnerIn};
const uint8_t salidas  [] = {cdOut, auxOut, phonoOut, tapeOut, tunnerOut};

uint8_t sizeIn = sizeof(entradas);
uint8_t sizeOut = sizeof(salidas);


keys_e key;
keys_e oldKey;


void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  Init();
}

void loop() {
  // put your main code here, to run repeatedly:

  key = getKey();

  if (key != oldKey ) {

    if (key != mute) {

      for (int i = 0; i <= sizeOut; i++) {
        if (i == key) {
          digitalWrite(salidas[i], HIGH);
        }
        else {
          digitalWrite(salidas[i], LOW);
        }
      }

    }

    else {

      for (int i = 0; i <= sizeOut; i++) {
        digitalWrite(salidas[i], LOW);
      }

    }

  }

  oldKey = key;
}

void Init (void) {

  //Configuramos las entradas y activamos las resistencias pull up
  for (uint8_t i = 0; i <= sizeIn - 1; i++) {
    Serial.print("Seconfigura la entrada numero "); Serial.print(i); Serial.print(" en el pin "); Serial.println(entradas[i]);
    pinMode(entradas[i], INPUT_PULLUP);
  }

  //Configuramos las salidas y las ponemos en estado logico 0
  for (uint8_t i = 0; i <= sizeOut - 1; i++) {
    Serial.print("Seconfigura la salida numero "); Serial.print(i); Serial.print(" en el pin "); Serial.println(salidas[i]);
    pinMode(salidas[i], OUTPUT);
    digitalWrite(salidas[i], LOW);
  }
}

keys_e getKey (void) {

  bool cdKey     = !digitalRead(cdIn);
  bool auxKey    = !digitalRead(auxIn);
  bool phonoKey  = !digitalRead(phonoIn);
  bool tapeKey   = !digitalRead(tapeIn);
  bool tunnerKey = !digitalRead(tunnerIn);

  //Check for only one key pressed and return
  if (cdKey && !( auxKey | phonoKey | tapeKey | tunnerKey)) {
    Serial.println("CD");
    while (cdKey) {
      cdKey = digitalRead(cdIn);
    }
    return cd;
  }

  if ( auxKey && !( cdKey | phonoKey | tapeKey | tunnerKey)) {
    Serial.println("AUX");
    while (auxKey) {
      auxKey = digitalRead(auxIn);
    }
    return aux;
  }

  if ( phonoKey && !( cdKey | auxKey | tapeKey | tunnerKey)) {
    Serial.println("PHONO");
    while (phonoKey) {
      phonoKey = digitalRead(phonoIn);
    }
    return phono;
  }

  if ( tapeKey && !( cdKey | auxKey | phonoKey | tunnerKey)) {
    Serial.println("TAPE");
    while (tapeKey) {
      tapeKey = digitalRead(tapeIn);
    }
    return tape;
  }

  if ( tunnerKey && !( cdKey | auxKey | phonoKey | tapeKey)) {
    Serial.println("TUNNER");
    while (tunnerKey) {
      tapeKey = digitalRead(tunnerIn);
    }
    return tunner;
  }


}

