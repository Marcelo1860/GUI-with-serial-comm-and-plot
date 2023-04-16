import serial
import time

arduino = serial.Serial('COM4',9600)
time.sleep(2)

# Leer los datos del puerto serie
while True:
    try:
        data = arduino.readline().decode('ascii').strip()
        print(data)
    except KeyboardInterrupt:
        break

# Cerrar el puerto serie
arduino.close()
"""
dato_leido = arduino.readline().decode('ascii').strip()
print(dato_leido)
arduino.close()
"""