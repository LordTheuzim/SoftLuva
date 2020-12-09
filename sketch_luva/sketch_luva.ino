//Bibliotecas
#include<Wire.h>
#include<SoftwareSerial.h>

//Pinos
const int flexPin = A0;      // Pin connected to voltage divider output

//MPU
const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ, GyX, GyY, GyZ, Tmp;

int16_t sensores[16];

//Bluetooth
SoftwareSerial BTserial(10, 11); // RX | TX

//Constante Teste
int comeco;
int fim;
int tempo;

void setup() {
  Serial.begin(9600);
  bluetoothSerial.begin(9600);

  Wire.begin(); //Inicia a comunicação I2C
  Wire.beginTransmission(MPU_addr); //Começa a transmissao de dados para o sensor
  Wire.write(0x6B); // registrador PWR_MGMT_1
  Wire.write(0); // Manda 0 e "acorda" o MPU 6050
  Wire.endTransmission(true);

  pinMode(flexPin, INPUT);
}

void loop() {
  comeco = millis();

  //Leitura pinos
  sensores[6] = analogRead(flexPin);

  //Leitura MPU
  Wire.beginTransmission(MPU_addr); //Começa a transmissao de dados para o sensor
  Wire.write(0x3B); // registrador dos dados medidos (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // 
  sensores[0] = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  sensores[1] = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  sensores[2] = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  sensores[3] = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  sensores[4] = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  sensores[5] = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  //Printar valores dos sensores
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  Serial.print("Flexor 1 = "); Serial.println(ADCflex);

  fim = millis();
  tempo = fim - comeco;
  //BTserial.print(sensores);
}
