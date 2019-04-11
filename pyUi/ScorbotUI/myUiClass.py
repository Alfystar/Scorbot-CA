from PyQt5 import QtCore, QtGui, QtWidgets

from pyqtLib.UiClass import UiClass

class MyUiQt (UiClass):
    def __init__(self, Windows):
        super().setupUi(Windows)
        print("ciao")
        self.passi1_2_direct.setText("22")
        self.Pulsante_invio_pagina_Basics.clicked.connect(self.printCiao)


    def printCiao(self):
        print("ciao da evento")



