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
        self.encoder1 = [self.riferimento1_direct, self.riferimento1_2_direct, self.riferimento1_3_direct,self.riferimento1_4_direct, self.riferimento1_5_direct, self.riferimento1_6_direct]
        self.setup = [self.passi1_direct,self.passi1_2_direct, self.passi1_3_direct, self.passi1_4_direct, self.passi1_5_direct,self.passi1_6_direct]
        self.encr = [self.encrease_value1,self.encrease_value2, self.encrease_value3, self.encrease_value4,self.encrease_value5,self.encrease_value6]
        self.param= [self.alphaValue,self.betaValue,self.gammaValue,self.deltaValue]

        """Seconda pagina"""
        #lista che contiene i pulsanti della seconda pagina
        self.angle=[self.AngleDir_1,self.AngleDir_2,self.AngleDir_3,self.AngleDir_4,self.AngleDir_5,self.AngleDir_6]
        self.theta=[self.tetaDir_1value,self.tetaDir_2value,self.tetaDir_3value,self.tetaDir_4value,self.tetaDir_5value,self.tetaDir_6value]
        self.encr1=[self.encrease_value1_2,self.encrease_value2_2,self.encrease_value3_2,self.encrease_value4_2,self.encrease_value5_2,self.encrease_value6_2]

        """Terza pagina"""
        # manca Ydes nella lista perché dà errore
        self.inVal=[self.Xdes_spin_Box,self.Ydes_spin_box,self.Zdes_spin_Box] #

        """LISTA Setup"""

        """Prima pagina"""
        for i in self.encoder1:
            i.setMaximum(20000) #il 20000 e' da prendere dalle impostazioni
        
        for i in self.encoder1:
            i.setMinimum(-20000) #il 20000 e' da prendere dalle impostazioni
        
        """Seconda pagina"""
        #definizione valori massimi e minimi
        for i in self.angle:
          i.setMaximum(20000) #il 20000 e' da prendere dalle impostazioni
        
        for i in self.angle:
          i.setMinimum(-20000) #il 20000 e' da prendere dalle impostazioni
        
        for i in self.param:
          i.setMaximum(10) #il 20000 e' da prendere dalle impostazioni
        
        for i in self.param:
          i.setMinimum(0.1) #il 20000 e' da prendere dalle impostazioni
        


        """Terza pagina"""
        #definizione valori massimi e minimi
        for i in self.inVal:
          i.setMaximum(20000) #il 20000 e' da prendere dalle impostazioni
        
        for i in self.inVal:
          i.setMinimum(-20000) #il 20000 e' da prendere dalle impostazioni
        


        """LISTA Eventi"""
        # premendo invio, metto nella lista i passi encoder da aggiungere  quelli attuali
        self.Pulsante_invio_pagina_Basics.clicked.connect(self.encoderValue)  #prima pagina
        self.PulsanteInvioPAginaAdvance.clicked.connect((self.angleValue))
        self.PulsanteInvioPAginaAdvance.clicked.connect((self.parametersValue))
        self.PulsanteInvioPAgina_Inverse.clicked.connect((self.inverseValue))

    def inserisci(self,lista,tipo):
     if tipo==0:
       for i in range(0,len(self.setup)):
          self.setup[i].setText(str(lista[i]))
    
     """ aggiungere per le impostazioni
     else:
       for i in range(0,len(self.setup)):
          self.setup[i].setText(str(lista[i]))
     """
 
    def encoderValue(self): 
      lista=[]
      for i in range(0,len(self.encoder1)):
        lista.append(self.encoder1[i].value())
      invia(lista,"e")


      
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