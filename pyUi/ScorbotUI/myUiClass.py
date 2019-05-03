import math

from typing import List

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QLabel

from pyqtLib.UiClass import Ui_UiClass

from pyqtLib.pyC_com.p import *
nMot=6

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
        # manca Ydes nella lista perché dà errore
        self.inVal=[self.Xdes_spin_Box,self.Ydes_spin_box,self.Zdes_spin_Box] #
        self.ax=[self.Xattuale_value,self.Yattuale_value,self.Zattuale_value]
        self.encr3=[self.encrease1_inv,self.encrease2_inv,self.encrease3_inv]
        self.cor3=[self.mA1_inv_v,self.mA2_inv_v,self.mA3_inv_v,self.mA4_inv_v,self.mA5_inv_v,self.mA6_inv_v]

        """Quarta pagina"""
        self.param= [self.alphaValue,self.betaValue,self.gammaValue,self.deltaValue]
        self.structVal=[self.l1Value,self.L2Value,self.L3Value,self.d1Value,self.d5Value,self.bdValue,self.WdValue]
        self.homePos=[self.en1HPVal,self.en2HPVal,self.en3HPVal,self.en4HPVal,self.en5HPVal,self.en6HPVal]
        self.maxValE=[self.maxEn1Val,self.maxEn2Val,self.maxEn3Val,self.maxEn4Val,self.maxEn5Val,self.maxEn6Val]
        self.minValE=[self.minEn1Val,self.minEn2Val,self.minEn3Val,self.minEn4Val,self.minEn5Val,self.minEn6Val]
        self.maxValC=[self.maxCor1Val,self.maxCor2Val,self.maxCor3Val,self.maxCor4Val,self.maxCor5Val,self.maxCor6Val]
   
        self.listaHp=[]
        for i in range(0,len(self.homePos)):
            self.listaHp.append(self.homePos[i].value())


        """LISTA Setup"""
        """default"""
        #self.default()
        
        """Quarta pagina"""
        #definizione valori massimi e minimi
        
        for i in self.param:
            i.setMaximum(10) #il 20000 e' da prendere dalle impostazioni
            i.setMinimum(0.1) #il 20000 e' da prendere dalle impostazioni

        for i in self.structVal:
            i.setMaximum(100)
            i.setMinimum(0)

        for i in self.maxValE:
            i.setMaximum(20000)
            i.setMinimum(-20000)   
        self.maxValE[5].setMinimum(0)   

        for i in self.minValE:
            i.setMaximum(20000)
            i.setMinimum(-20000)  
        self.minValE[5].setMinimum(0)   

        
        for i in self.maxValC:
            i.setMaximum(2)
            i.setMinimum(0)  

        self.default()

        for i in range(0,len(self.homePos)):
            self.homePos[i].setMaximum(self.maxValE[i].value()) #il 20000 e' da prendere dalle impostazioni
            self.homePos[i].setMinimum(self.minValE[i].value()) #il 20000 e' da prendere dalle impostazioni
        
        """Prima pagina"""
        for i in range(0,len(self.encoder1)):
            self.encoder1[i].setMaximum(self.maxValE[i].value()) #il 20000 e' da prendere dalle impostazioni
            self.encoder1[i].setMinimum(self.minValE[i].value()) #il 20000 e' da prendere dalle impostazioni
        
        """Seconda pagina"""
        #definizione valori massimi e minimi
        for i in range(0,len(self.angle)-1):
            self.angle[i].setMaximum(360) #il 20000 e' da prendere dalle impostazioni
        self.angle[5].setMaximum(100)
        
        for i in range(0,len(self.angle)-1):
            self.angle[i].setMinimum(-360) #il 20000 e' da prendere dalle impostazioni
        self.angle[5].setMinimum(0)
        
        """Terza pagina"""
        #definizione valori massimi e minimi
        for i in self.inVal:
          i.setMaximum(int(self.structVal[0].value()+self.structVal[1].value()+self.structVal[2].value())) #il 20000 e' da prendere dalle impostazioni
          i.setMinimum(-int(self.structVal[0].value()+self.structVal[1].value()+self.structVal[2].value())) #il 20000 e' da prendere dalle impostazioni

        """LISTA Eventi"""
        # premendo invio, metto nella lista i passi encoder da aggiungere  quelli attuali
        self.Pulsante_invio_pagina_Basics.clicked.connect(self.encoderValue)  #prima pagina
        self.PulsanteInvioPAginaAdvance.clicked.connect((self.angleValue))
        self.PulsanteInvioPAgina_Inverse.clicked.connect((self.inverseValue))
        self.Home.clicked.connect(self.setup1)
        self.reset.clicked.connect(self.default)
        
    def default(self):
        self.Gomitoalto.setChecked(True)
        lista_p=[0.1,0.2,0.3,0.4]#MISURARE
        for i in range(0,len(self.param)):
            self.param[i].setValue(lista_p[i])
        
        lista_rob=[3,22,22,35,14,45,0]
        for i in range(0,len(self.structVal)):
            self.structVal[i].setValue(lista_rob[i])
            
        for i in range(0,len(self.maxValE)):
            self.maxValE[i].setValue(20000)
        self.maxValE[5].setValue(5740)

        for i in range(0,len(self.minValE)):
            self.minValE[i].setValue(-20000)
        self.minValE[5].setValue(0)

        for i in range(0,len(self.maxValC)):
            self.maxValC[i].setValue(2)

        for i in self.homePos:
            i.setValue(0)
        
    
    def converti_in_e(self,lista):
        lista_e=[]
        lista_e.append(int(-int(lista[0])/self.param[0].value()))
        lista_e.append(int(-int(lista[1])/self.param[1].value()))
        lista_e.append(int((int(lista[1])+int(lista[2]))/self.param[1].value()))
        lista_e.append(int(0.5*((int(lista[1])+int(lista[2])+int(lista[3]))/self.param[2].value()+lista[4]/self.param[3].value())))
        lista_e.append(int(0.5*(int(lista[4])/self.param[3].value()-(int(lista[1])+int(lista[2])+int(lista[3]))/self.param[2].value())))
        lista_e.append(int(self.maxValE[5].value()*int(lista[5])/100))
        return lista_e

    def converti_in_a(self,lista):
        lista_a=[]        
        lista_a.append(-self.param[0].value()*int(lista[0])) 
        lista_a.append(-self.param[1].value()*int(lista[1])) 
        lista_a.append(self.param[1].value()*(int(lista[1])+int(lista[2]))) 
        lista_a.append(-self.param[1].value()*int(lista[2])+self.param[2].value()*(int(lista[3])-int(lista[4]))) 
        lista_a.append(self.param[3].value()*(int(lista[3])+int(lista[4])))
        lista_a.append(round(int(lista[5])*100/self.maxValE[5].value(),3))
        return lista_a

    def cin_dir(self,lista):
      l1 = self.structVal[0].value()
      l2 = self.structVal[1].value()
      l3 = self.structVal[2].value()
      d1 = self.structVal[3].value()
      d5 = self.structVal[4].value()
      betad=self.structVal[5].value()
      omegad=self.structVal[6].value()
      ax=[]
      t1r=math.radians(lista[0])
      t2r=math.radians(lista[1])
      t3r=math.radians(lista[2])
      t4r=math.radians(lista[3])
      t5r=math.radians(lista[4])
      xpolso=math.cos(t1r)*(l1+l2*math.cos(t2r)+l3*math.cos(t2r+t3r))
      ypolso=math.sin(t1r)*(l1+l2*math.cos(t2r)+l3*math.cos(t2r+t3r))
      zpolso=d1-l2*math.sin(t2r)-l3*math.sin(t2r+t3r)
      ax.append(xpolso-math.cos(t1r)*d5*math.sin(t2r+t3r+t4r))
      ax.append(ypolso-math.sin(t1r)*d5*math.sin(t2r+t3r+t4r))
      ax.append(zpolso-d5*math.cos(t2r+t3r+t4r))
      return ax

    def cin_inv(self,lista):
       l1 = self.structVal[0].value()
       l2 = self.structVal[1].value()
       l3 = self.structVal[2].value()
       d1 = self.structVal[3].value()
       d5 = self.structVal[4].value()
       betad=self.structVal[5].value()
       omegad=self.structVal[6].value()
       bdr= math.radians(betad)
       theta1 = math.degrees(math.atan2(lista[1],lista[0]))
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
       lista_a=[theta1,theta2,theta3,theta4,theta5,self.angle[5].value()]
       
       return lista_a
   


    def inserisci(self,lista,tipo):
     if tipo==0:#aggiungere impostazioni
       #pagina 1
       for i in range(0,len(self.listaHp)):
          lista[i]=int(lista[i])-self.listaHp[i]

       for i in range(0,len(self.setup)):
          self.setup[i].setText(str(lista[i]))
          self.encr[i].setText(str(int(self.encoder1[i].value()-int(self.setup[i].text()))))
       #cor pagina 1,2,3
       for i in range(0,len(self.cor)):
          self.cor[i].setText(str(lista[i+nMot]))
          self.cor2[i].setText(str(lista[i+nMot])) 
          self.cor3[i].setText(str(lista[i+nMot])) 

       lista_a=self.converti_in_a(lista)#lista deve essere una lista di encoder
       #pagina 2
       for i in range(0,len(self.theta)):
           self.theta[i].setText(str(round(lista_a[i],3))) 
           self.encr1[i].setText(str(round(self.angle[i].value()-float(self.theta[i].text()),3)))
       
       #pagina 3
       lista_xyz=self.cin_dir(lista_a)
       for i in range(0,len(self.ax)):
           self.ax[i].setText(str(round(lista_xyz[i],3)))
           self.encr3[i].setText(str(round(self.inVal[i].value()-float(self.ax[i].text()),3)))
            
     else:   
        for i in range(0,len(self.maxValE)):
           self.maxValE[i].setValue(int(lista[i]))
        
        for i in range(0,len(self.minValE)):
           self.minValE[i].setValue(int(lista[i+nMot]))
        
        for i in range(0,len(self.maxValC)):
           self.maxValC[i].setValue(int(lista[i+2*nMot]))
        
        """Quarta pagina"""
        for i in range(0,len(self.homePos)):
            self.homePos[i].setMaximum(self.maxValE[i].value()) #il 20000 e' da prendere dalle impostazioni
            self.homePos[i].setMinimum(self.minValE[i].value()) #il 20000 e' da prendere dalle impostazioni
        
        """Prima pagina"""
        for i in range(0,len(self.encoder1)):
            self.encoder1[i].setMaximum(self.maxValE[i].value()) #il 20000 e' da prendere dalle impostazioni
            self.encoder1[i].setMinimum(self.minValE[i].value()) #il 20000 e' da prendere dalle impostazioni
        
        """Terza pagina"""
        #definizione valori massimi e minimi
        for i in self.inVal:
          i.setMaximum(int(self.structVal[0].value()+self.structVal[1].value()+self.structVal[2].value())) #il 20000 e' da prendere dalle impostazioni
          i.setMinimum(-int(self.structVal[0].value()+self.structVal[1].value()+self.structVal[2].value())) #il 20000 e' da prendere dalle impostazioni
        




    def encoderValue(self):
      lista=[]
      for i in range(0,len(self.encoder1)):
        lista.append(self.encoder1[i].value())
      lista_a=self.converti_in_a(lista)
      for i in range(0,len(self.angle)):
           self.angle[i].setValue(lista_a[i])
      lista_xyz=self.cin_dir(lista_a) 
      for i in range(0,len(self.inVal)):
           self.inVal[i].setValue(lista_xyz[i])
      for i in range(0,len(self.listaHp)):
          lista[i]=lista[i]+self.listaHp[i]
          
          if lista[i]>self.maxValE[i].value():
              lista[i]=self.maxValE[i].value()
          if lista[i]<self.minValE[i].value():
              lista[i]=self.minValE[i].value()
      
      for i in range(0,len(self.setup)):
          self.encr[i].setText(str(int(self.encoder1[i].value()-int(self.setup[i].text()))))
      for i in range(0,len(self.theta)):
           self.encr1[i].setText(str(round(self.angle[i].value()-float(self.theta[i].text()),3)))
      for i in range(0,len(self.ax)):
           self.encr3[i].setText(str(round(self.inVal[i].value()-float(self.ax[i].text()),3)))
         
      invia(lista,"e")
      
      #ERRORE sulla percentuale perche' vuole un intero     

    def angleValue(self):
        lista=[]
        for i in self.angle:
            lista.append(i.value())
        lista_e=self.converti_in_e(lista)#lista deve essere una lista di angoli    
        for i in range(0,len(self.encoder1)):
            self.encoder1[i].setValue(lista_e[i])
        lista_xyz=self.cin_dir(lista) 
        for i in range(0,len(self.inVal)):
           self.inVal[i].setValue(lista_xyz[i]) 
        for i in range(0,len(self.listaHp)):
          lista_e[i]=lista_e[i]+self.listaHp[i]
          if lista_e[i]>self.maxValE[i].value():
              lista_e[i]=self.maxValE[i].value()
          if lista_e[i]<self.minValE[i].value():
              lista_e[i]=self.minValE[i].value()
        for i in range(0,len(self.setup)):
          self.encr[i].setText(str(int(self.encoder1[i].value()-int(self.setup[i].text()))))
        for i in range(0,len(self.theta)):
           self.encr1[i].setText(str(round(self.angle[i].value()-float(self.theta[i].text()),3)))
        for i in range(0,len(self.ax)):
           self.encr3[i].setText(str(round(self.inVal[i].value()-float(self.ax[i].text()),3)))
        
        invia(lista_e,"e")
       
    def inverseValue(self):
       lista=[]
       for i in range(0,len(self.inVal)):
          lista.append(self.inVal[i].value())
          self.encr3[i].setText(str(lista[i]))
        
    # operazioni matematiche per ricavare i theta
    # l1, l2, l3, d1 e betad vanno misurati ed impostati
    #AGGIUNGERE l1,l2 ecc alle impostazioni
       lista_a=self.cin_inv(lista)
       for i in range(0,len(self.angle)-1):
            self.angle[i].setValue(lista_a[i])
           
       lista_e=self.converti_in_e(lista_a)
       for i in range(0,len(self.encoder1)):
            self.encoder1[i].setValue(lista_e[i])
       for i in range(0,len(self.listaHp)):
          lista_e[i]=lista_e[i]+self.listaHp[i]
          
          if lista_e[i]>self.maxValE[i].value():
              lista_e[i]=self.maxValE[i].value()
          if lista_e[i]<self.minValE[i].value():
              lista_e[i]=self.minValE[i].value()
       
       for i in range(0,len(self.setup)):
          self.encr[i].setText(str(int(self.encoder1[i].value()-int(self.setup[i].text()))))
       for i in range(0,len(self.theta)):
           self.encr1[i].setText(str(round(self.angle[i].value()-float(self.theta[i].text()),3)))
       for i in range(0,len(self.ax)):
           self.encr3[i].setText(str(round(self.inVal[i].value()-float(self.ax[i].text()),3)))
        
       invia(lista_e,"e")

    def setup1(self):
        for i in range(0,len(self.homePos)):
            self.homePos[i].setMaximum(self.maxValE[i].value()) #il 20000 e' da prendere dalle impostazioni
            self.homePos[i].setMinimum(self.minValE[i].value()) #il 20000 e' da prendere dalle impostazioni
        
        """Prima pagina"""
        for i in range(0,len(self.encoder1)):
            self.encoder1[i].setMaximum(self.maxValE[i].value()) #il 20000 e' da prendere dalle impostazioni
            self.encoder1[i].setMinimum(self.minValE[i].value()) #il 20000 e' da prendere dalle impostazioni
        
        """Terza pagina"""
        #definizione valori massimi e minimi
        for i in self.inVal:
          i.setMaximum(int(self.structVal[0].value()+self.structVal[1].value()+self.structVal[2].value())) #il 20000 e' da prendere dalle impostazioni
          i.setMinimum(-int(self.structVal[0].value()+self.structVal[1].value()+self.structVal[2].value())) #il 20000 e' da prendere dalle impostazioni
        
        self.listaHp=[]
        for i in self.homePos:
            self.listaHp.append(i.value())
        lista=[]
        for i in self.maxValE:
            lista.append(i.value())
        
        for i in self.minValE:
            lista.append(i.value())

        for i in self.maxValC:
            lista.append(i.value())

        invia(lista,"i") 
   