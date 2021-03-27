import serial
import numpy as np
import csv
import time

#data = np.zeros((1,18))
tempo = 0.01
arduino = serial.Serial('/dev/ttyUSB0',9600) #porta a ser usada
arduino.reset_input_buffer() #limpa o buffer
arduino.readline() #previnir possivel bug

#nome das colunas
fieldnames = ["Tempo", "Sensor 0", "Sensor 1", "Sensor 2", "Sensor 3", "Sensor 4",
"Sensor 5", "Sensor 6", "Sensor 7", "Sensor 8", "Sensor 9", "Sensor 10", "Sensor 11",
"Sensor 12", "Sensor 13", "Sensor 14", "Sensor 15", "Sensor 16", "Sensor 17"]

#criar um csv para salvar a secao
with open('data.csv', 'w') as csv_file:
    csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
    csv_writer.writeheader()

while True:

# printar os dados dos sensores no terminal
    a = arduino.readline() #pegar todos os dados que chegam do arduino
    b = a.split(b',') #vetor com os bytes de cada sensor
#transformar os bytes em inteiros
    b0 = []
    for x in range(18):
        b0.append(int(b[x]))
#colocar vetor de ints no data
#    b0 = np.array([b0])
#    print(b0)
#        data = np.concatenate((data,b0))

    with open('data.csv', 'a') as csv_file:
        csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)

        info = {
            "Tempo": tempo,
            "Sensor 0": b0[0],
            "Sensor 1": b0[1],
            "Sensor 2": b0[2],
            "Sensor 3": b0[3],
            "Sensor 4": b0[4],
            "Sensor 5": b0[5],
            "Sensor 6": b0[6],
            "Sensor 7": b0[7],
            "Sensor 8": b0[8],
            "Sensor 9": b0[9],
            "Sensor 10": b0[10],
            "Sensor 11": b0[11],
            "Sensor 12": b0[12],
            "Sensor 13": b0[13],
            "Sensor 14": b0[14],
            "Sensor 15": b0[15],
            "Sensor 16": b0[16],
            "Sensor 17": b0[17],
        }

        csv_writer.writerow(info)
        print(tempo, b0)

        tempo += 0.01
    time.sleep(0.01)
