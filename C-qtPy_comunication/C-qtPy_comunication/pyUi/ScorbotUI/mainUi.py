import sys
import logo
from PyQt5 import QtCore, QtGui, QtWidgets

from myUiClass import MyUiQt


import sys
import signal
from threading import Thread
mex=[]
imp=[]
class InputThread (Thread):
    def __init__(self, ui):
        Thread.__init__(self)
        self.text=""
        self.ui = ui

    def run(self):
        while True:
            leggi() #riceve e fa il parsing della stringa ricevuta restituendo una lista
            #prova
            #i=invia(mex,"e")
            #leggi() #riceve e fa il parsing della stringa ricevuta restituendo una lista
            #i=invia(imp,"i")


if __name__ == '__main__':

    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = MyUiQt(MainWindow)

    inTh = InputThread(ui)
    inTh.start()
    app.exec_()

    MainWindow.show()



    sys.exit(app.exec_())

    