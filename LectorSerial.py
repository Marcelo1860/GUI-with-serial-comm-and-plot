
import sys, serial, threading
from PyQt6  import QtWidgets,uic
from PyQt6.QtWidgets import *
import time
import struct

class arduino_read(QMainWindow):
    def __init__(self,parent=None):
        super(arduino_read,self).__init__(parent)
        uic.loadUi('analogo.ui',self)
        self.show()
        self.pushButton.clicked.connect(lambda: threading.Thread(target = self.conexion).start())

    def conexion(self):
        board = serial.Serial('COM4',baudrate = 9600)
        time.sleep(2)

        while True:
            data1 = board.readline()
            valor_limpio = data1.replace(b'\x00', b'').decode()
            valor_limpio = valor_limpio.strip()
            print(valor_limpio)
            self.lcdNumber.display(valor_limpio)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    dlog = arduino_read()
    dlog.show()
    sys.exit(app.exec())