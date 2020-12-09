#include<SoftwareSerial.h>

// vetor de dados
int *data = malloc(5 * sizeof(int));


//iniciar bluetooth
SoftwareSerial BTserial(10, 11); // RX | TX

//Teste de velocidade
int comeco;
int fim;
int tempo;


void setup() {
  Serial.begin(9600);
  BTserial.begin(9600);

}

void loop() {
  comeco = millis();
  for(int i=0; i < 5; i++){
    data[i] = data[i] + 1;
  }
  //BTserial.print(data);
  Serial.print("%d", data[0]);  

}
