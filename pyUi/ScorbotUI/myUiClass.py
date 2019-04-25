import math
from typing import List

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QLabel

from pyqtLib.UiClass import Ui_UiClass

from pyqtLib.pyC_com.p import *


class MyUiQt (Ui_UiClass):

    def __init__(self, Windows):
        super().setupUi(Windows)   # genera gli oggetti dell'interfaccia grafica

        """DEFINIZIONE DELLE LISTE DI PAGINA"""

        """Prima pagina"""
        # la seguente lista contiene tutti i pulsanti Encoder della prima pagina
        self.encoder1 = [self.riferimento1_direct.value(), self.riferimento1_2_direct.value(), self.riferimento1_3_direct.value(),self.riferimento1_4_direct.value(), self.riferimento1_5_direct.value(), self.riferimento1_6_direct.value()]
        self.setup = [int(self.passi1_direct.text()),int(self.passi1_2_direct.text()), int(self.passi1_3_direct.text()), int(self.passi1_4_direct.text()), int(self.passi1_5_direct.text()), int(self.passi1_6_direct.text())]
        self.encr = [int(self.encrease_value1.text()),int(self.encrease_value2.text()), int(self.encrease_value3.text()), int(self.encrease_value4.text()), int(self.encrease_value5.text()), int(self.encrease_value6.text()) ]
        self.param= [self.alphaValue.value(),self.betaValue.value(),self.gammaValue.value(),self.deltaValue.value()]

        """Seconda pagina"""
        #lista che contiene i pulsanti della seconda pagina
        self.angle=[self.AngleDir_1.value(),self.AngleDir_2.value(),self.AngleDir_3.value(),self.AngleDir_4.value(),self.AngleDir_5.value(),self.AngleDir_6.value()]
        self.theta=[int(self.tetaDir_1value.text()),int(self.tetaDir_2value.text()),int(self.tetaDir_3value.text()),int(self.tetaDir_4value.text()),int(self.tetaDir_5value.text()),int(self.tetaDir_6value.text())]
        self.encr1=[int(self.encrease_value1_2.text()),int(self.encrease_value2_2.text()),int(self.encrease_value3_2.text()),int(self.encrease_value4_2.text()),int(self.encrease_value5_2.text()),int(self.encrease_value6_2.text())]

        """Terza pagina"""
        # manca Ydes nella lista perché dà errore
        self.inVal=[self.Xdes_spin_Box.value(),self.Ydes_spin_box.value(),self.Zdes_spin_Box.value()] #

        """LISTA Setup"""

        """Prima pagina"""

        self.riferimento1_direct.setMaximum(20000) # questo, e le seccessive 5 righe, fissano i valori massimi
        self.riferimento1_2_direct.setMaximum(20000) # che posso inserire all'interno degli encoder
        self.riferimento1_3_direct.setMaximum(20000)
        self.riferimento1_4_direct.setMaximum(20000)
        self.riferimento1_5_direct.setMaximum(20000)
        self.riferimento1_6_direct.setMaximum(20000)



        self.riferimento1_direct.setMinimum(-20000) # questo, e le seccessive 5 righe, fissano i valori minimi
        self.riferimento1_2_direct.setMinimum(-20000) # che posso inserire all'interno degli encoder
        self.riferimento1_3_direct.setMinimum(-20000)
        self.riferimento1_4_direct.setMinimum(-20000)
        self.riferimento1_5_direct.setMinimum(-20000)
        self.riferimento1_6_direct.setMinimum(-20000)

        """Seconda pagina"""
        #definizione valori massimi e minimi
        self.AngleDir_1.setMaximum(20000)
        self.AngleDir_2.setMaximum(20000)
        self.AngleDir_3.setMaximum(20000)
        self.AngleDir_4.setMaximum(20000)
        self.AngleDir_5.setMaximum(20000)
        self.AngleDir_6.setMaximum(20000)

        self.AngleDir_1.setMinimum(-20000)
        self.AngleDir_2.setMinimum(-20000)
        self.AngleDir_3.setMinimum(-20000)
        self.AngleDir_4.setMinimum(-20000)
        self.AngleDir_5.setMinimum(-20000)
        self.AngleDir_6.setMinimum(-20000)

        self.alphaValue.setMaximum(10) #valori massimi e minimi dei parametri impostati a caso, impostarli in modo corretto
        self.betaValue.setMaximum(10)
        self.gammaValue.setMaximum(10)
        self.deltaValue.setMaximum(10)

        self.alphaValue.setMinimum(0)
        self.betaValue.setMinimum(0)
        self.gammaValue.setMinimum(0)
        self.deltaValue.setMinimum(0)


        """Terza pagina"""
        #definizione valori massimi e minimi
        self.Xdes_spin_Box.setMaximum(2000)
        self.Ydes_spin_box.setMaximum(2000)
        self.Zdes_spin_Box.setMaximum(2000)

        self.Xdes_spin_Box.setMinimum(-2000)
        self.Ydes_spin_box.setMinimum(-2000)  # dà errore quindi per far si che il programma giri impostarlo come commento
        self.Zdes_spin_Box.setMinimum(-2000)


        """LISTA Eventi"""
        # premendo invio, metto nella lista i passi encoder da aggiungere  quelli attuali
        self.Pulsante_invio_pagina_Basics.clicked.connect(self.encoderValue)  #prima pagina
        self.PulsanteInvioPAginaAdvance.clicked.connect((self.angleValue))
        self.PulsanteInvioPAginaAdvance.clicked.connect((self.parametersValue))
        self.PulsanteInvioPAgina_Inverse.clicked.connect((self.inverseValue))


    def encoderValue(self):


        self.encoder1[0] = self.riferimento1_direct.value()
        self.encoder1[1] = self.riferimento1_2_direct.value()
        self.encoder1[2] = self.riferimento1_3_direct.value()
        self.encoder1[3] = self.riferimento1_4_direct.value()
        self.encoder1[4] = self.riferimento1_5_direct.value()
        self.encoder1[5] = self.riferimento1_6_direct.value()


       #funzione compini messaggio che manda la lista dei valori degli encoder a Francesco

        #invia_e(self.encoder)    # funzione da passare a Francesco
        #invia_imp(lista)         # lista impostazioni della pagina di setup



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


        self.encrease_value1.setText(str(encrease[0]))
        self.encrease_value2.setText(str(encrease[1]))
        self.encrease_value3.setText(str(encrease[2]))
        self.encrease_value4.setText(str(encrease[3]))
        self.encrease_value5.setText(str(encrease[4]))
        self.encrease_value6.setText(str(encrease[5]))



        self.setup[0] = int(self.passi1_direct.text())
        self.setup[1] = int(self.passi1_2_direct.text())
        self.setup[2] = int(self.passi1_3_direct.text())
        self.setup[3] = int(self.passi1_4_direct.text())
        self.setup[4] = int(self.passi1_5_direct.text())
        self.setup[5] = int(self.passi1_6_direct.text())


    def angleValue(self):
        self.angle[0] = self.AngleDir_1.value()
        self.angle[1] = self.AngleDir_2.value()
        self.angle[2] = self.AngleDir_3.value()
        self.angle[3] = self.AngleDir_4.value()
        self.angle[4] = self.AngleDir_5.value()
        self.angle[5] = self.AngleDir_6.value()

        self.tetaDir_1value.setText(str(self.angle[0]))
        self.tetaDir_2value.setText(str(self.angle[1]))
        self.tetaDir_3value.setText(str(self.angle[2]))
        self.tetaDir_4value.setText(str(self.angle[3]))
        self.tetaDir_5value.setText(str(self.angle[4]))
        self.tetaDir_6value.setText(str(self.angle[5]))

        encrease1= [] #la variabile encrease mi permette di stampare l'incremento effettivo di ogni encoder

        encrease1.append(self.angle[0] - self.theta[0])
        encrease1.append(self.angle[1] - self.theta[1])
        encrease1.append(self.angle[2] - self.theta[2])
        encrease1.append(self.angle[3] - self.theta[3])
        encrease1.append(self.angle[4] - self.theta[4])
        encrease1.append(self.angle[5] - self.theta[5])

        self.encrease_value1_2.setText(str(encrease1[0]))
        self.encrease_value2_2.setText(str(encrease1[1]))
        self.encrease_value3_2.setText(str(encrease1[2]))
        self.encrease_value4_2.setText(str(encrease1[3]))
        self.encrease_value5_2.setText(str(encrease1[4]))
        self.encrease_value6_2.setText(str(encrease1[5]))

        self.theta[0] = int(self.tetaDir_1value.text())
        self.theta[1] = int(self.tetaDir_2value.text())
        self.theta[2] = int(self.tetaDir_3value.text())
        self.theta[3] = int(self.tetaDir_4value.text())
        self.theta[4] = int(self.tetaDir_5value.text())
        self.theta[5] = int(self.tetaDir_6value.text())


    def parametersValue(self):

        self.param[0]= self.alphaValue.value()
        self.param[1] = self.betaValue.value()
        self.param[2] = self.gammaValue.value()
        self.param[3] = self.deltaValue.value()



    def inverseValue(self):

        self.inVal[0]=self.Xdes_spin_Box.value()
        self.inVal[1] = self.Ydes_spin_box.value()
        self.inVal[1] = self.Zdes_spin_Box.value()

        # operazioni matematiche per ricavare i theta.
        # l1, l2, l3, d1 e betad vanno misurati ed impostati
        l1=3
        l2= 22
        l3=22
        d1=11
        betad=1
        omegad=10
        theta1 = math.atan2(self.inVal[1], self.inVal[0])
        A1 = self.inVal[0] * math.cos(theta1) + self.inVal[1] * math.sin(theta1) - l1
        A2 = d1 - self.inVal[2]  #  per far si che il programma giri mettere inVal[1]
        A3 = (A1 * A1) + (A2 * A2) - (l2 * l2) - (l3 * l3)
        A4 = 2 * l2 * l3
        A5 = A3 / A4
        theta3 = math.acos(A5)
        A6 = l2 + l3 * math.cos(theta3) * A2 - l3 * math.sin(theta3) * A1
        A7 = (l2 + l3 * math.cos(theta3)) * A1 + l3 * math.sin(theta3) * A2
        theta2 = math.atan2(A6, A7)
        theta4 = betad - theta2 - theta3 - 90
        theta5=omegad


        self.teta1_inverse_value.setText(str(theta1))
        self.teta2_inverse_value.setText(str(theta2))
        self.teta3_inverse_value.setText(str(theta3))
        self.teta4_inverse_value.setText(str(theta4))
        self.teta5_invers_value.setText(str(theta5)) # dà lo stesso errore di Ydes quindi  per far si che il programma giri impostarlo come commento




