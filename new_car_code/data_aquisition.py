import serial 
import csv

arduino_port = "COM3"
baud = 9600
fileName = "analog-data.csv"

ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port:" + arduino_port)
file = open(fileName, "a")
print("Created file")
print_labels = False
line = 0 #start at 0 because our header is 0 (not real data)
sensor_data = [] #store data

while line < 500:
    getData=ser.readline()
    dataString = getData.decode('utf-8')
    data=dataString[0:][:-2]
    #print(data)

    readings = data.split(",")
    #print(readings)

    sensor_data.append(readings)
    print(sensor_data)
    line += 1

with open(fileName, 'w', encoding='UTF8', newline='') as f:
    writer = csv.writer(f)
    writer.writerows(sensor_data)

print("Data collection complete!")
file.close()


with open(fileName, "r") as r:
    line = r.readlines()
    
    length = len(line)
    last = len(line) - 1
    for i in range(length):
        current = int(line[i][0:2])
        if i == last:
            after = current
        else:
            after = int(line[i + 1][0:2])
                
        if current - after >= 10:
            print(line[i][4:])
            break
