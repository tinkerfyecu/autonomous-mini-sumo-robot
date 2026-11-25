/*
  TINKERFY - AUTONOMOUS MINI SUMO
  Firmware v1.0 - Autonomous Navigation
  ESP32 + TB6612FNG + HC-SR04 + TCRT5000

  Tested behavior reported by user:
  - Search for opponents by turning right
  - Attack when an opponent is within 30 cm
  - Reverse and turn when the white boundary is detected

  TB6612 STBY is connected directly to logic supply.
  The HC-SR04 ECHO must be reduced to 3.3 V before reaching ESP32.
*/

// MOTOR A
int AIN1 = 21;
int AIN2 = 22;
int PWMA = 23;

// MOTOR B
int BIN1 = 25;
int BIN2 = 33;
int PWMB = 32;

// SENSOR ULTRASONICO
int TRIG = 18;
int ECHO = 34;

// SENSOR INFRARROJO
int SENSOR_IR = 26;

// CONFIGURACION
int umbralIR = 1750;
int distanciaAtaque = 30;

int velocidadAtaque = 180;
int velocidadGiro = 120;
int velocidadRetroceso = 150;

// VARIABLES
int valorIR = 0;
float distancia = 0;
long duracion = 0;

// MOVIMIENTOS

void detener() {
  ledcWrite(PWMA, 0);
  ledcWrite(PWMB, 0);

  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}

void avanzar() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);

  ledcWrite(PWMA, velocidadAtaque);
  ledcWrite(PWMB, velocidadAtaque);
}

void retroceder() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);

  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);

  ledcWrite(PWMA, velocidadRetroceso);
  ledcWrite(PWMB, velocidadRetroceso);
}

void girarDerecha() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);

  ledcWrite(PWMA, velocidadGiro);
  ledcWrite(PWMB, velocidadGiro);
}

void setup() {
  Serial.begin(115200);

  // MOTORES
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  ledcAttach(PWMA, 1000, 8);
  ledcAttach(PWMB, 1000, 8);

  // ULTRASONICO
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIG, LOW);

  // INFRARROJO
  analogReadResolution(12);

  detener();

  Serial.println("TINKERFY - MINI SUMO");
  Serial.println("INICIANDO...");

  delay(3000);
}

void loop() {
  // 1. VERIFICAR BORDE BLANCO
  valorIR = analogRead(SENSOR_IR);

  if (valorIR < umbralIR) {
    Serial.println("BORDE DETECTADO");

    detener();
    delay(100);

    retroceder();
    delay(600);

    detener();
    delay(100);

    girarDerecha();
    delay(500);

    detener();
    delay(100);

    return;
  }

  // 2. MEDIR DISTANCIA
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duracion = pulseIn(ECHO, HIGH, 30000);

  if (duracion == 0) {
    distancia = -1;
  } else {
    distancia = duracion * 0.0343 / 2;
  }

  // 3. BUSCAR O ATACAR
  if (distancia >= 2 && distancia <= distanciaAtaque) {
    Serial.println("OPONENTE DETECTADO");
    avanzar();
  } else {
    Serial.println("BUSCANDO OPONENTE");
    girarDerecha();
  }

  Serial.print("Distancia: ");
  Serial.println(distancia);

  Serial.print("IR: ");
  Serial.println(valorIR);

  delay(60);
}
