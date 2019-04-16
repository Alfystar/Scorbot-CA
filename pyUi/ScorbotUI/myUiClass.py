from typing import List

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QLabel

from pyqtLib.UiClass import UiClass

#from p.py import * # risolvere il problema di import 

class MyUiQt (UiClass):

    def __init__(self, Windows):
        super().setupUi(Windows)   # genera gli oggetti dell'interfaccia grafica

        """Definizione delle liste di pagina"""

        # la seguente lista contiene tutti i pulsanti Encoder della prima pagina
        self.encoder1 = [self.riferimento1_direct.value(), self.riferimento1_2_direct.value(), self.riferimento1_3_direct.value(),self.riferimento1_4_direct.value(), self.riferimento1_5_direct.value(), self.riferimento1_6_direct.value()]
        self.setup = [int(self.passi1_direct.text()),int(self.passi1_2_direct.text()), int(self.passi1_3_direct.text()), int(self.passi1_4_direct.text()), int(self.passi1_5_direct.text()), int(self.passi1_6_direct.text())]

        """LISTA Setup"""
        self.riferimento1_direct.setMaximum(20000) # questo, e le seccessive 5 righe, fissano i valori massimi
        self.riferimento1_2_direct.setMaximum(20000) # che posso inserire all'interno degli ecoder
        self.riferimento1_3_direct.setMaximum(20000)
        self.riferimento1_4_direct.setMaximum(20000)
        self.riferimento1_5_direct.setMaximum(20000)
        self.riferimento1_6_direct.setMaximum(20000)


        self.riferimento1_direct.setMinimum(-20000) # questo, e le seccessive 5 righe, fissano i valori minimi
        self.riferimento1_2_direct.setMinimum(-20000) # che posso inserire all'interno degli ecoder
        self.riferimento1_3_direct.setMinimum(-20000)
        self.riferimento1_4_direct.setMinimum(-20000)
        self.riferimento1_5_direct.setMinimum(-20000)
        self.riferimento1_6_direct.setMinimum(-20000)

        """LISTA Eventi"""

        self.Pulsante_invio_pagina_Basics.clicked.connect(self.encoderValue) #premendo invio, metto nella lista i passi encoder da aggiungere  quelli qttuali

    def encoderValue(self):


        self.encoder1[0] = self.riferimento1_direct.value()
        self.encoder1[1] = self.riferimento1_2_direct.value()
        self.encoder1[2] = self.riferimento1_3_direct.value()
        self.encoder1[3] = self.riferimento1_4_direct.value()
        self.encoder1[4] = self.riferimento1_5_direct.value()
        self.encoder1[5] = self.riferimento1_6_direct.value()


       #funzione compini messaggio che manda la lista dei valori degli encoder a Francesco

        #invia_e(self.encoder)  # funzione da passare a Francesco
        #invia_imp(lista) # lista impostazioni della pagina di setup



        self.passi1_direct.setText(str(self.encoder1[0]))
        self.passi1_2_direct.setText(str(self.encoder1[1]))
        self.passi1_3_direct.setText(str(self.encoder1[2]))
        self.passi1_4_direct.setText(str(self.encoder1[3]))
        self.passi1_5_direct.setText(str(self.encoder1[4]))
        self.passi1_6_direct.setText(str(self.encoder1[5]))

        encrease = []  #la variabile encrease mi permette di stampare l'incremento effettivo di ogni encoder

        encrease.append(self.encoder1[0] - self.setup[0])
        encrease.append(self.encoder1[1] - self.setup[1])
        encrease.append(self.encoder1[2] - self.setup[2])
        encrease.append(self.encoder1[3] - self.setup[3])
        encrease.append(self.encoder1[4] - self.setup[4])
        encrease.append(self.encoder1[5] - self.setup[5])

        self.setup[0] = int(self.passi1_direct.text())
        self.setup[1] = int(self.passi1_2_direct.text())
        self.setup[2] = int(self.passi1_3_direct.text())
        self.setup[3] = int(self.passi1_4_direct.text())
        self.setup[4] = int(self.passi1_5_direct.text())
        self.setup[5] = int(self.passi1_6_direct.text())



        for i in range(1, 7):           #nel seguente for, c'è un if per determinare e è stato fatto un decremento o un incremento del valore dell'encoder
            if encrease[i-1] >= 0 :
                print("set Encoder ", i, "on:", self.encoder1[i-1],"current encrease:", encrease[i-1]) # stampa a schermo la lista l

            else:

                print("set Encoder ", i, "on:", self.encoder1[i - 1], "current decrease:", encrease[i - 1])










