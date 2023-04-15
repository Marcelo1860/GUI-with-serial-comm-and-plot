import tkinter as tk
from tkinter import ttk
from serial.tools import list_ports
import serial

# Crea una instancia de la clase Tk de tkinter
root = tk.Tk()
root.geometry("400x300") # Define el tamaño de la ventana

# Define una función para leer datos desde el puerto serie
def read_data():
    ser = serial.Serial(port.get(), 9600)
    ser.timeout = 1 # Agrega el timeout de 1 segundo
    while True:
        data = ser.readline().decode('ascii')
        label.config(text=data)

# Crea un Label en la ventana
label = tk.Label(root, font=("Arial", 20))
label.pack()

# Crea un Frame para los controles de puerto serie
frame = ttk.Frame(root)
frame.pack()

# Crea una lista de los puertos disponibles
ports = [port.device for port in list_ports.comports()]

# Crea un Combobox para seleccionar el puerto COM
port = ttk.Combobox(frame, values=ports)
port.pack(side=tk.LEFT)

# Crea un botón para actualizar la lista de puertos disponibles
button_refresh = ttk.Button(frame, text="Actualizar")
button_refresh.pack(side=tk.LEFT)

# Define la función para actualizar la lista de puertos disponibles
def refresh_ports():
    ports = [port.device for port in list_ports.comports()]
    port['values'] = ports

# Asocia la función de actualización al botón de actualizar
button_refresh.config(command=refresh_ports)

# Crea un botón para iniciar la lectura de datos
button = ttk.Button(root, text="Iniciar", command=read_data)
button.pack()

# Inicia el loop principal de tkinter
root.mainloop()