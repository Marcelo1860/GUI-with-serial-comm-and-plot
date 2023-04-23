import serial
import time
# Configurar el puerto serie
ser = serial.Serial('COM4', 9600)
time.sleep(2)

# Leer los datos del puerto serie
while True:
    try:
        data = ser.readline().decode('ascii').strip()
        print(data)
    except KeyboardInterrupt:
        break

# Cerrar el puerto serie
ser.close()