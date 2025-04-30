#include <tago.h>
#include <Wire.h>
#include <MPU6050.h>

// Cria uma instância do objeto MPU6050
MPU6050 mpu;

// Variáveis para armazenar os dados do sensor
int16_t ax, ay, az;
int16_t gx, gy, gz;

tago tag("CLARO_2G9F971E",
         "WrZHU48hzz",
         "8cd24288-f0ea-48f7-a8be-f8d50f4048dc");  // ssid, password and tago apikey

void setup() {
  Serial.begin(115200);

  if (!tag.connectWifi()) {
    Serial.println("not connected");
    while (1)
      ;
  }
  Serial.println("Wifi connected");
  delay(1000);

  // Inicializa a comunicação I2C
  Wire.begin(21, 22);  // SDA, SCL

  // Inicializa o MPU6050
  mpu.initialize();

  // Verifica se o MPU6050 está conectado
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 não conectado!");
    while (1)
      ;  // Para o programa se o MPU6050 não estiver conectado
  }

  Serial.println("MPU6050 conectado com sucesso!");
}

void loop() {
  // Lê os dados do sensor
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Imprime os dados no console serial
  Serial.print("Aceleração: ");
  Serial.print("X: ");
  Serial.print(ax);
  Serial.print(" | Y: ");
  Serial.print(ay);
  Serial.print(" | Z: ");
  Serial.println(az);

  Serial.print("Giroscópio: ");
  Serial.print("X: ");
  Serial.print(gx);
  Serial.print(" | Y: ");
  Serial.print(gy);
  Serial.print(" | Z: ");
  Serial.println(gz);

  Serial.println();
  delay(1000);

  // Acelerometro
  tag.sendData("Ax", String(ax));  // To send to tago cloud
  tag.sendData("Ay", String(ay));
  tag.sendData("Az", String(az));

  // Giroscopio
  tag.sendData("Gx", String(gx));
  tag.sendData("Gy", String(gy));
  tag.sendData("Gz", String(gz));
  delay(1000);
}
