#define BLYNK_TEMPLATE_ID "TMPL2NLwOW1Q1"
#define BLYNK_TEMPLATE_NAME "Control Brazo 2"
#define BLYNK_AUTH_TOKEN  "iZv2ey2yfg8iOvuL1_b8y8pX1s52apmY"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

// Pines
#define PIN_BASE 16
#define PIN_HOMBRO 17
#define PIN_CODO 18
#define PIN_GARRA 4

// Posición inicial del brazo
#define INICIO_B 90
#define INICIO_H 60
#define INICIO_C 0
#define INICIO_G 0

// Límites de movimiento
#define MAX_BASE 180
#define MIN_BASE 0
#define MAX_HOMBRO 100
#define MIN_HOMBRO 15
#define MAX_CODO 180
#define MIN_CODO 0
#define MAX_GARRA 40
#define MIN_GARRA 0

char ssid[] = "ETRR Free";
char pass[] = "";

// Servos
Servo baseServo;
Servo hombroServo;
Servo codoServo;
Servo garraServo;


bool habilitacion = false;

void setup() {
    Serial.begin(115200);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

    baseServo.attach(PIN_BASE);
    hombroServo.attach(PIN_HOMBRO);
    codoServo.attach(PIN_CODO);
    garraServo.attach(PIN_GARRA);

  
    baseServo.write(INICIO_B);
    hombroServo.write(INICIO_H);
    codoServo.write(INICIO_C);
    garraServo.write(INICIO_G);

    delay(1500);  // tiempo para que el brazo llegue bien
    habilitacion = true;  // ahora sí se habilita el control
}

void loop() {
    Blynk.run();
}


BLYNK_CONNECTED() {
    Blynk.virtualWrite(V0, INICIO_B);
    Blynk.virtualWrite(V1, INICIO_H);
    Blynk.virtualWrite(V2, INICIO_C);
    Blynk.virtualWrite(V3, INICIO_G);
}

// BASE
BLYNK_WRITE(V0) {
    if (!habilitacion) return;

    int angle = param.asInt();
    angle = constrain(angle, MIN_BASE, MAX_BASE);
    baseServo.write(angle);
}

// HOMBRO
BLYNK_WRITE(V1) {
    if (!habilitacion) return;

    int angle = param.asInt();
    angle = constrain(angle, MIN_HOMBRO, MAX_HOMBRO);
    hombroServo.write(angle);
}

// CODO
BLYNK_WRITE(V2) {
    if (!habilitacion) return;

    int angle = param.asInt();
    angle = constrain(angle, MIN_CODO, MAX_CODO);
    codoServo.write(angle);
}

// GARRA
BLYNK_WRITE(V3) {
    if (!habilitacion) return;

    int angle = param.asInt();
    angle = constrain(angle, MIN_GARRA, MAX_GARRA);
    garraServo.write(angle);
}
