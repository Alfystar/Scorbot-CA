from PyQt5 import QtCore, QtGui, QtWidgets

from pyUi.ScorbotUI.pyqtLib.UiClass import UiClass

class MyUiQt (UiClass):
    def __init__(self, Windows):
        super().setupUi(Windows)            # genera gli oggetti dell'interfaccia grafica

        """LISTA Setup"""
        self.riferimento1_2_direct.setMaximum(20000)

        """LISTA Eventi"""
        self.Pulsante_invio_pagina_Basics.clicked.connect(self.printCiao)


    def printCiao(self):
        print("ciao da evento")
        print(self.riferimento1_2_direct.value())




