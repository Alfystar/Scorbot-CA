from PyQt5 import QtCore, QtGui, QtWidgets

from pyqtLib.UiClass import UiClass

class MyUiQt (UiClass):
    def __init__(self, Windows):
        super().setupUi(Windows)            # genera gli oggetti dell'interfaccia grafica

        """LISTA Setup"""
        self.riferimento1_direct.setMaximum(20000) # questo, e le seccessive 5 righe, fissano i valori massimi
        self.riferimento1_2_direct.setMaximum(20000) # che posso inserire all'interno degli ecoder
        self.riferimento1_3_direct.setMaximum(20000)
        self.riferimento1_4_direct.setMaximum(20000)
        self.riferimento1_5_direct.setMaximum(20000)
        self.riferimento1_6_direct.setMaximum(20000)

        """LISTA Eventi"""
        self.Pulsante_invio_pagina_Basics.clicked.connect(self.encoderValue) #premendo invio, metto nella lista i passi encoder da aggiungere  quelli qttuali

    def encoderValue(self):

        l = [] # contiene il numero di passi encoder da andare a sommare a quelli attuali

        l.append(self.riferimento1_direct.value())
        l.append(self.riferimento1_2_direct.value())
        l.append(self.riferimento1_3_direct.value())
        l.append(self.riferimento1_4_direct.value())
        l.append(self.riferimento1_5_direct.value())
        l.append(self.riferimento1_6_direct.value())

        for i in range(1, 7):
            print("Increase Encoder", i, "of:", l[i-1])# stampa a schermo la listal









