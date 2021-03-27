//Bibliotecas
#include<Wire.h>
#include<SoftwareSerial.h>

//Pinos de saida analogica

const int fsrAnalogPin0 = A7; //dedao
const int fsrAnalogPin1 = A1; //ponta indicador
const int fsrAnalogPin2 = A2; // meio indicador
const int fsrAnalogPin3 = A6; // trapezio
const int fsrAnalogPin4 = A3; // ponta dedo feio
const int mux = A0; // multiplexador

//Pinos de controle Multiplexador D2 Ate D5
const int muxCtrlS0 = 2; 
const int muxCtrlS1 = 3; 
const int muxCtrlS2 = 4;
const int muxCtrlS3 = 5; //nao vou precisar mudar

//Saida dos pinos
int16_t sensorReading[18];
int16_t Tmp;

//MPU
const int MPU_addr = 0x68;

// Tempo
unsigned long comeco = 0;

void setup() {
  Serial.begin(9600);
//  bluetoothSerial.begin(9600);

//inicializacao dos pinos de controle
  pinMode(muxCtrlS0, OUTPUT);
  pinMode(muxCtrlS1, OUTPUT);
  pinMode(muxCtrlS2, OUTPUT);
  pinMode(muxCtrlS3, OUTPUT);
  
//inicializacao dos valores de controle
  digitalWrite(muxCtrlS0, LOW);
  digitalWrite(muxCtrlS1, LOW);
  digitalWrite(muxCtrlS2, LOW);
  digitalWrite(muxCtrlS3, LOW); //nao muda

  Wire.begin(); //Inicia a comunicação I2C
  Wire.beginTransmission(MPU_addr); //Começa a transmissao de dados para o sensor
  Wire.write(0x6B); // registrador PWR_MGMT_1
  Wire.write(0); // Manda 0 e "acorda" o MPU 6050
  Wire.endTransmission(true);

}

void loop() {
//  comeco = millis();
//  Serial.print(comeco);
//  Serial.print("\t");
  
  // Leitura de FSR
    sensorReading[0] = analogRead(fsrAnalogPin0);
    sensorReading[1] = analogRead(fsrAnalogPin1);
    sensorReading[2]= analogRead(fsrAnalogPin2);
    sensorReading[3] = analogRead(fsrAnalogPin3);
    sensorReading[4] = analogRead(fsrAnalogPin4);
    
  //Leitura Utilizando o mux 0000 ate 0110
  
  sensorReading[5] = analogRead(mux); //0000
 
  digitalWrite(muxCtrlS0, HIGH); 
  sensorReading[6] = analogRead(mux); //0001
  
  digitalWrite(muxCtrlS0, LOW);
  digitalWrite(muxCtrlS1, HIGH);
  sensorReading[7] = analogRead(mux); //0010
  
  digitalWrite(muxCtrlS0, HIGH);
  sensorReading[8] = analogRead(mux); //0011

  digitalWrite(muxCtrlS0, LOW);
  digitalWrite(muxCtrlS1, LOW);
  digitalWrite(muxCtrlS2, HIGH);
  sensorReading[9] = analogRead(mux); //0100

  digitalWrite(muxCtrlS0, HIGH);
  sensorReading[10] = analogRead(mux); //0101

  digitalWrite(muxCtrlS0, LOW);
  digitalWrite(muxCtrlS1, HIGH);
  sensorReading[11] = analogRead(mux); //0110

  digitalWrite(muxCtrlS2, LOW);
  digitalWrite(muxCtrlS1, LOW); //0000
  
  //Leitura MPU
  Wire.beginTransmission(MPU_addr); //Começa a transmissao de dados para o sensor
  Wire.write(0x3B); // registrador dos dados medidos (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);
  
  sensorReading[12] = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  sensorReading[13] = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  sensorReading[14] = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  sensorReading[15] = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  sensorReading[16] = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  sensorReading[17] = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)


    for(int i = 0; i < 18; i++){

    Serial.print(sensorReading[i]);
    Serial.print(",");
  }
  Serial.println();

//  Serial.println(sensorReading[8]);

  //BTserial.print(sensores);
}
