import sys, time
from timeit import default_timer

from PyQt5 import uic, QtWidgets

 
#Graphics
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas 
from matplotlib.figure import Figure 
import matplotlib.pyplot as plt 

from datetime import datetime 
import serial
import numpy as np
import xlwt


#Inicializa las ventanas
qtCreatorFile = "grafico.ui" 
Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile) 


# #Define variable
i = 0

led_state = True

y = []
x = []

# tiempo = []
tiempo = 0

# creamos el fichero excel y csv
wb = xlwt.Workbook()
# añadimos hoja
ws = wb.add_sheet('Datos sensor')
# escribimos encabezados
ws.write(0,0,'Tiempo')
ws.write(0,1,'Tensión')



# Abrimos el puerto del arduino a 9600
# ser = serial.Serial('/dev/ttyACM0',9600)
ser = serial.Serial('COM4',9600)
ser.close()
ser.open()

class MyApp(QtWidgets.QMainWindow, Ui_MainWindow): 


    def update(self):

        global i, tiempo
        t_inicio = default_timer()


   
        data = ser.readline()
        data = data.replace(b'\x00', b'')
        time.sleep(0.02)

        


        x.append(tiempo)

        y.append(float(data.decode()))

        self.ax.clear()
        self.ax.grid()
        self.ax.plot(x, y)
    

        self.ax.set(xlabel='Tiempo (s)', ylabel='Tensión (Volts)',
        title='Gráfica')
        self.ax.legend('1')
        self.ax.set_ylim([-1, 2])


        self.ax.figure.canvas.draw()
        i += 1
        print(default_timer() - t_inicio+.09)
        tiempo += round(default_timer() - t_inicio +.09 ,4)
        
      

    def ledon(self):

        global led_state
        if led_state:
            #bit_zero = b'\x00' 
            #ser.write(bit_zero)
            ser.write(b'S 7;')
            #ser.write(b'\n')
            #ser.write(b'\r')
            led_state = False
            self.apagado.setText('Encendido')
            self.led.setStyleSheet("background-color: green")
        else:
            #bit_zero = b'\x00' 
            #ser.write(bit_zero)
            ser.write(b'R 7;')
            #ser.write(b'\n')
            #ser.write(b'\r')
            led_state = True
            self.apagado.setText('Apagado')
            self.led.setStyleSheet("background-color: black")

    def open(self):
        ser.reset_input_buffer()
        #Begin to graph
        self.timer = self.plotWidge.new_timer(100, [(self.update, (), {})])
        self.timer.start()


    
    def stop(self):
        ser.reset_input_buffer()
        self.timer.stop()

    



    def __init__(self):

        QtWidgets.QMainWindow.__init__(self) 
        Ui_MainWindow.__init__(self) 
        self.setupUi(self) 
        self.inicio.clicked.connect(self.open)
        self.parar.clicked.connect(self.stop)
        self.apagado.clicked.connect(self.ledon)

        self.show()


        #Graficar
        self.plotWidge = FigureCanvas(Figure(figsize=(5, 3)))
        self.grafico.addWidget(self.plotWidge)
        self.ax = self.plotWidge.figure.subplots()
        self.ax.plot([], [])
        





if __name__ == "__main__": 

    app = QtWidgets.QApplication(sys.argv) 
    window = MyApp() 
    app.exec()


for n in range(len(y)):
  ws.write(n+1, 0, x[n])
  ws.write(n+1, 1, y[n])


# grabo Fichero ecel.
wb.save('Datos.xls')