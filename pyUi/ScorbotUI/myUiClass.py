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
        self.cor=[self.ma1_value,self.ma2_value,self.ma3_value,self.ma4_value,self.ma5_value,self.ma6_value]


        """Seconda pagina"""
        #lista che contiene i pulsanti della seconda pagina
        self.angle=[self.AngleDir_1,self.AngleDir_2,self.AngleDir_3,self.AngleDir_4,self.AngleDir_5,self.AngleDir_6]
        self.theta=[self.tetaDir_1value,self.tetaDir_2value,self.tetaDir_3value,self.tetaDir_4value,self.tetaDir_5value,self.tetaDir_6value]
        self.encr1=[self.encrease_value1_2,self.encrease_value2_2,self.encrease_value3_2,self.encrease_value4_2,self.encrease_value5_2,self.encrease_value6_2]
        self.cor2=[self.ma1_value1_direct,self.ma2_value2_direct,self.ma3_value3_direct,self.ma4_value4_direct,self.ma5_value5_direct,self.ma6_value6_direct]


        """Terza pagina"""

        self.inVal=[self.Xdes_spin_Box,self.Ydes_spin_box,self.Zdes_spin_Box] #
        self.ax=[]
        self.encr3=[]
        self.cor3=[]

        """Le prossime 6 righe sono nuove"""
        """Quarta pagina"""
        self.param= [self.alphaValue,self.betaValue,self.gammaValue,self.deltaValue]
        self.structVal=[self.l1Value,self.L2Value,self.L3Value,self.d1Value,self.d5Value]
        self.homePos=[self.en1HPVal,self.en2HPVal,self.en3HPVal,self.en4HPVal,self.en5HPVal,self.en6HPVal]
        self.maxValE=[self.maxEn1Val,self.maxEn2Val,self.maxEn3Val,self.maxEn4Val,self.maxEn5Val,self.maxEn6Val]
        self.minValE=[self.minEn1Val,self.minEn2Val,self.minEn3Val,self.minEn4Val,self.minEn5Val,self.minEn6Val]
        self.maxValC=[self.maxCor1Val,self.maxCor2Val,self.maxCor3Val,self.maxCor4Val,self.maxCor5Val,self.maxCor6Val]


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

        for i in self.angle:
            i.setValue(1)


        for i in self.theta:
            i.setText(str(1))

        """Terza pagina"""
        #definizione valori massimi e minimi
        for i in self.inVal:
          i.setMaximum(20000) #il 20000 e' da prendere dalle impostazioni

        for i in self.inVal:
          i.setMinimum(-20000) #il 20000 e' da prendere dalle impostazioni


        """Quarta pagina"""
        #definizione valori massimi e minimi
        
        for i in self.param:
            i.setMaximum(10) #il 20000 e' da prendere dalle impostazioni
        
        for i in self.param:
            i.setMinimum(0.1) #il 20000 e' da prendere dalle impostazioni

        for i in self.param:
          i.setValue(1) #il 20000 e' da prendere dalle impostazioni


        """Le prossime righe sono nuove"""

        for i in self.structVal:
            i.setMaximum(100)

        for i in self.structVal:
            i.setMinimum(0)

        for i in self.maxValE:
            i.setMaximum(20000)

        for i in self.maxValE:
            i.setMinimum(-20000)


        for i in self.minValE:
            i.setMaximum(20000)

        for i in self.minValE:
            i.setMinimum(-20000)


        for i in range(0,6):
            a=self.maxValE[i].value()
            b=self.minValE[i].value()
            self.homePos[i].setMaximum(a)
            self.homePos[i].setMinimum(b)


        """LISTA Eventi"""
        # premendo invio, metto nella lista i passi encoder da aggiungere  quelli attuali
        self.Pulsante_invio_pagina_Basics.clicked.connect(self.encoderValue)  #prima pagina
        self.PulsanteInvioPAginaAdvance.clicked.connect(self.angleValue)
        self.PulsanteInvioPAgina_Inverse.clicked.connect(self.inverseValue)

        """nuova riga"""
        self.Home.clicked.connect(self.setup1)
        
    def converti_in_e(self,lista):
        lista_e=[]
        lista_e.append(int(-int(lista[0])/self.param[0].value()))
        lista_e.append(int(-int(lista[1])/self.param[1].value()))
        lista_e.append(int((int(lista[1])+int(lista[2]))/self.param[1].value()))
        lista_e.append(int(0.5*((int(lista[1])+int(lista[2])+int(lista[3]))/self.param[2].value()+lista[4]/self.param[3].value())))
        lista_e.append(int(0.5*(int(lista[4])/self.param[3].value()-(int(lista[1])+int(lista[2])+int(lista[3]))/self.param[2].value())))
        lista_e.append(int(5740*int(lista[5])/100))
        return lista_e

    def converti_in_a(self,lista):
        lista_a=[]        
        lista_a.append(-self.param[0].value()*int(lista[0])) 
        lista_a.append(-self.param[1].value()*int(lista[1])) 
        lista_a.append(self.param[1].value()*(int(lista[1])+int(lista[2]))) 
        lista_a.append(-self.param[1].value()*int(lista[2])+self.param[2].value()*(int(lista[3])-int(lista[4]))) 
        lista_a.append(self.param[3].value()*(int(lista[3])+int(lista[4])))
        lista_a.append(round(int(lista[5])*100/5740,3))
        return lista_a

    def inserisci(self,lista,tipo):
     if tipo==0:#aggiungere impostazioni
       #pagina 1
       for i in range(0,len(self.setup)):
          self.setup[i].setText(str(lista[i]))
          self.encr[i].setText(str(int(self.encoder1[i].value()-int(self.setup[i].text()))))
       #cor pagina 1,2,3
       for i in range(0,len(self.cor)):
          self.cor[i].setText(str(lista[i+6]))
          self.cor2[i].setText(str(lista[i+6])) 

       lista_a=self.converti_in_a(lista)#lista deve essere una lista di encoder
       #pagina 2
       for i in range(0,len(self.theta)):
           self.theta[i].setText(str(lista_a[i])) 
           self.encr1[i].setText(str(self.angle[i].value()-float(self.theta[i].text())))
     #else:   #esempio
        #for i in range(0,len(self.setup)):
         #   self.setup[i].setText(str(lista[i]))
         #   self.encr[i].setText(str(int(self.encoder1[i].value()-int(self.setup[i].text()))))
       
        




    def encoderValue(self):
      lista=[]
      for i in range(0,len(self.encoder1)):
        lista.append(self.encoder1[i].value())
      invia(lista,"e")
      lista_a=self.converti_in_a(lista)
      for i in range(0,len(self.angle)):
           self.angle[i].setValue(lista_a[i]) 
      #ERRORE sulla percentuale perche' vuole un intero     

    def angleValue(self):
        lista=[]
        for i in self.angle:
            lista.append(i.value())
        lista_e=self.converti_in_e(lista)#lista deve essere una lista di angoli    
        for i in range(0,len(self.encoder1)):
            self.encoder1[i].setValue(lista_e[i])
        invia(lista_e,"e")
        #todo controllo valori minimi 

    def inverseValue(self):
      lista=[]
      for i in range(0,len(self.inval)):
        lista[i]=self.inVal[i].value()
        
    # operazioni matematiche per ricavare i theta
    # l1, l2, l3, d1 e betad vanno misurati ed impostati
    #AGGIUNGERE l1,l2 ecc alle impostazioni
        l1 = 3
        l2 = 22
        l3 = 22
        d1 = 35
        d5 = 14
        betad=45
        omegad=0

        bdr= math.radians(betad)
        theta1 = math.degrees(math.atan2(lista[1], lista[0]))
        theta1r= math.radians(theta1)
        A1= lista[0]* (math.cos(theta1r)) +lista[1]*(math.sin(theta1r)) -d5*(math.cos(bdr)) -l1
        A2 = d1 - lista[2] -d5*(math.sin(bdr))
        A3 = (A1*A1) + (A2*A2) - (l2*l2) - (l3*l3)
        A4 = 2 * l2 * l3
        A5 = A3 / A4
        theta3 = math.acos(A5)


        if self.Gomitobasso.isChecked() == True:
            theta3=math.degrees( -1* abs(theta3))
            theta3r1 = math.radians(theta3)
            A7 = (l2 + l3 * math.cos(theta3r1)) * A1 + l3 * math.sin(theta3r1) * A2
            A6 = (l2 + l3 * math.cos(theta3r1)) * A2 - l3 * math.sin(theta3r1) * A1
            theta2 = math.degrees(math.atan2(A6, A7))
            theta4 = betad - theta2 - theta3 - 90
            theta5 = omegad
        else:
            theta3 = abs(math.degrees(math.acos(A5)))
            theta3r = math.radians(theta3)
            A6 = (l2 + l3 * math.cos(theta3r))* A2 - l3 * math.sin(theta3r) * A1
            A7 = (l2 + l3 * math.cos(theta3r)) * A1 + l3 * math.sin(theta3r) * A2
            theta2 = math.degrees(math.atan2(A6, A7))
            theta4 = betad - theta2 - theta3 - 90
            theta5 = omegad
        
        lista_e=self.converti_in_e(theta1,theta2,theta3,theta4,theta5,self.angle[5].value())
        invia(lista_e,"e")


    """nuove righe"""
    def setup1(self):
        lista=[]
        for i in self.structVal:
            lista.append(i.value())

        listaHp=[]
        for i in self.homePos:
            listaHp.append(i.value())

        listaMaxV=[]
        for i in self.maxValE:
            listaMaxV.append(i.value())

        listaMinV=[]
        for i in self.minValE:
            listaMinV.append(i.value())


        listaPar=[]
        for i in self.param:
            listaMinV.append(i.value())




