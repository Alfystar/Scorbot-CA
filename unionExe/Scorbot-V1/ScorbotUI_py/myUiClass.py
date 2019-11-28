import math

from typing import List

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QLabel

from pyqtLib.UiClass import Ui_UiClass

from pyqtLib.pyC_com.p import *

nMot = 6
Vref = 1.1

import configparser


class MyUiQt(Ui_UiClass):

    def __init__(self, Windows):
        super().setupUi(Windows)  # genera gli oggetti dell'interfaccia grafica

        """DEFINIZIONE DELLE LISTE DI PAGINA"""

        """Prima pagina"""
        # la seguente lista contiene tutti gli spinBox Encoder della prima pagina
        self.encoder1 = [self.riferimento1_direct, self.riferimento1_2_direct, self.riferimento1_3_direct,
                         self.riferimento1_4_direct, self.riferimento1_5_direct, self.riferimento1_6_direct]
        # la seguente lista contiene tutte Qlabel Encoder attuali della prima pagina
        self.setup = [self.passi1_direct, self.passi1_2_direct, self.passi1_3_direct, self.passi1_4_direct,
                      self.passi1_5_direct, self.passi1_6_direct]
        # la seguente lista contiene tutte le Qlabel incremento(errore=y-r) della prima pagina
        self.encr = [self.encrease_value1, self.encrease_value2, self.encrease_value3, self.encrease_value4,
                     self.encrease_value5, self.encrease_value6]
        # la seguente lista contiene tutte le Qlabel delle correnti della prima pagina
        self.cor = [self.ma1_value, self.ma2_value, self.ma3_value, self.ma4_value, self.ma5_value, self.ma6_value]

        """Seconda pagina"""
        # lista che contiene gli spinBox degli Angoli della seconda pagina
        self.angle = [self.AngleDir_1, self.AngleDir_2, self.AngleDir_3, self.AngleDir_4, self.AngleDir_5,
                      self.AngleDir_6]
        # la seguente lista contiene tutte le Qlabel degli angoli attuali della seconda pagina
        self.theta = [self.tetaDir_1value, self.tetaDir_2value, self.tetaDir_3value, self.tetaDir_4value,
                      self.tetaDir_5value, self.tetaDir_6value]
        # la seguente lista contiene tutte le Qlabel dell' incremento(tetaErrore=thetay-thetar) degli angoli della seconda pagina
        self.encr1 = [self.encrease_value1_2, self.encrease_value2_2, self.encrease_value3_2, self.encrease_value4_2,
                      self.encrease_value5_2, self.encrease_value6_2]
        # lista oggetti Qlabel correnti motori
        self.cor2 = [self.ma1_value1_direct, self.ma2_value2_direct, self.ma3_value3_direct, self.ma4_value4_direct,
                     self.ma5_value5_direct, self.ma6_value6_direct]

        """Terza pagina"""
        # lista oggetti spinBox x,y,z des
        self.inVal = [self.Xdes_spin_Box, self.Ydes_spin_box, self.Zdes_spin_Box]
        # lista oggetti Qlabel x,y,z attuali
        self.ax = [self.Xattuale_value, self.Yattuale_value, self.Zattuale_value]
        # lista oggetti Qlabel incremento(errore=posDes-posAttuale)
        self.encr3 = [self.encrease1_inv, self.encrease2_inv, self.encrease3_inv]
        # lista oggetti Qlabel correnti motori
        self.cor3 = [self.mA1_inv_v, self.mA2_inv_v, self.mA3_inv_v, self.mA4_inv_v, self.mA5_inv_v, self.mA6_inv_v]

        """Quarta pagina"""
        # lista oggetti spinBox dei parametri costanti degli encoder
        self.param = [self.alphaValue, self.betaValue, self.gammaValue, self.deltaValue]
        # lista oggetti spinBox dei parametri costanti della struttura del robot
        self.structVal = [self.l1Value, self.L2Value, self.L3Value, self.d1Value, self.d5Value, self.bdValue,
                          self.WdValue]
        # lista oggetti spinBox degli encoder per la home "falsa"
        self.homePos = [self.en1HPVal, self.en2HPVal, self.en3HPVal, self.en4HPVal, self.en5HPVal, self.en6HPVal]
        # lista oggetti spinBox dei valori massimi degli encoder
        self.maxValE = [self.maxEn1Val, self.maxEn2Val, self.maxEn3Val, self.maxEn4Val, self.maxEn5Val, self.maxEn6Val]
        # lista oggetti spinBox dei valori minimi degli encoder
        self.minValE = [self.minEn1Val, self.minEn2Val, self.minEn3Val, self.minEn4Val, self.minEn5Val, self.minEn6Val]
        # lista oggetti spinBox dei valori massimi delle correnti
        self.maxValC = [self.maxCor1Val, self.maxCor2Val, self.maxCor3Val, self.maxCor4Val, self.maxCor5Val,
                        self.maxCor6Val]

        self.listaHp = []  # lista per modificare la mappatura della home falsa in quella dell'hardware
        for i in range(0, len(self.homePos)):
            self.listaHp.append(self.homePos[i].value())

        """LISTA Setup"""

        """Quarta pagina"""
        # definizione valori massimi e minimi inseribili nella spinBox

        for i in self.param:
            i.setMaximum(10)  # il 20000 e' da prendere dalle impostazioni
            i.setMinimum(0.1)  # il 20000 e' da prendere dalle impostazioni

        for i in self.structVal:
            i.setMaximum(100)
            i.setMinimum(0)

        for i in self.maxValE:
            i.setMaximum(50000)
            i.setMinimum(-50000)
        self.maxValE[5].setMinimum(
            0)  # il sesto encoder parte da 0 ed e' espresso in percentuale nel set dell' angolo(cinematica diretta)

        for i in self.minValE:
            i.setMaximum(50000)
            i.setMinimum(-50000)
        self.minValE[5].setMinimum(
            0)  # il sesto encoder parte da 0 ed e' espresso in percentuale nel set dell' angolo(cinematica diretta)

        for i in self.maxValC:
            i.setMaximum(5000)
            i.setMinimum(0)

        self.default()  # funzione per il settaggio dei parametri della quarta schermata(salvati su file)

        # settaggio valori max e min per le spinBox della prima,seconda,terza pagina e per la home nella quarta
        for i in range(0, len(self.homePos)):
            self.homePos[i].setMaximum(self.maxValE[i].value())
            self.homePos[i].setMinimum(self.minValE[i].value())

        """Prima pagina"""
        for i in range(0, len(self.encoder1)):
            self.encoder1[i].setMaximum(self.maxValE[i].value())
            self.encoder1[i].setMinimum(self.minValE[i].value())

        """Seconda pagina"""
        # definizione valori massimi e minimi
        for i in range(0, len(self.angle) - 1):
            self.angle[i].setMaximum(360)
        self.angle[5].setMaximum(100)  # e' una percentuale

        for i in range(0, len(self.angle) - 1):
            self.angle[i].setMinimum(-360)
        self.angle[5].setMinimum(0)  # e' una percentuale

        """Terza pagina"""
        # definizione valori massimi e minimi
        for i in self.inVal:
            i.setMaximum(int(self.structVal[0].value() + self.structVal[1].value() + self.structVal[2].value()))
            i.setMinimum(-int(self.structVal[0].value() + self.structVal[1].value() + self.structVal[2].value()))

        """LISTA Eventi"""
        # pulsante prima pagina
        self.Pulsante_invio_pagina_Basics.clicked.connect(self.encoderValue)
        # pulsante seconda pagina
        self.PulsanteInvioPAginaAdvance.clicked.connect((self.angleValue))
        # pulsante terza pagina
        self.PulsanteInvioPAgina_Inverse.clicked.connect((self.inverseValue))
        # pulsante quarta pagina (set impostazioni)
        self.Home.clicked.connect(self.setup1)
        # pulsante quarta pagina (reset impostazioni)
        self.reset.clicked.connect(self.reset_i)

    def default(self):  # setta le impostazioni della quarta pagina tramite i valori definiti nel file config.py
        self.Gomitoalto.setChecked(True)

        config = configparser.ConfigParser()
        config.read('config.ini')

        self.homePos[0].setValue(int(config['DEFAULT']['h1']))
        self.homePos[1].setValue(int(config['DEFAULT']['h2']))
        self.homePos[2].setValue(int(config['DEFAULT']['h3']))
        self.homePos[3].setValue(int(config['DEFAULT']['h4']))
        self.homePos[4].setValue(int(config['DEFAULT']['h5']))
        self.homePos[5].setValue(int(config['DEFAULT']['h6']))

        self.maxValE[0].setValue(int(config['DEFAULT']['enM1']))
        self.maxValE[1].setValue(int(config['DEFAULT']['enM2']))
        self.maxValE[2].setValue(int(config['DEFAULT']['enM3']))
        self.maxValE[3].setValue(int(config['DEFAULT']['enM4']))
        self.maxValE[4].setValue(int(config['DEFAULT']['enM5']))
        self.maxValE[5].setValue(int(config['DEFAULT']['enM6']))

        self.minValE[0].setValue(int(config['DEFAULT']['em1']))
        self.minValE[1].setValue(int(config['DEFAULT']['em2']))
        self.minValE[2].setValue(int(config['DEFAULT']['em3']))
        self.minValE[3].setValue(int(config['DEFAULT']['em4']))
        self.minValE[4].setValue(int(config['DEFAULT']['em5']))
        self.minValE[5].setValue(int(config['DEFAULT']['em6']))

        self.maxValC[0].setValue(int(config['DEFAULT']['eC1']))
        self.maxValC[1].setValue(int(config['DEFAULT']['eC2']))
        self.maxValC[2].setValue(int(config['DEFAULT']['eC3']))
        self.maxValC[3].setValue(int(config['DEFAULT']['eC4']))
        self.maxValC[4].setValue(int(config['DEFAULT']['eC5']))
        self.maxValC[5].setValue(int(config['DEFAULT']['eC6']))

        self.structVal[0].setValue(float(config['DEFAULT']['l1']))
        self.structVal[1].setValue(float(config['DEFAULT']['l2']))
        self.structVal[2].setValue(float(config['DEFAULT']['l3']))
        self.structVal[3].setValue(float(config['DEFAULT']['d1']))
        self.structVal[4].setValue(float(config['DEFAULT']['d5']))
        self.structVal[5].setValue(float(config['DEFAULT']['Bd']))
        self.structVal[6].setValue(float(config['DEFAULT']['Wd']))

        self.param[0].setValue(float(config['DEFAULT']['alfa']))
        self.param[1].setValue(float(config['DEFAULT']['beta']))
        self.param[2].setValue(float(config['DEFAULT']['gamma']))
        self.param[3].setValue(float(config['DEFAULT']['delta']))

    def converti_in_e(self,
                      lista):  # prende in ingresso una lista di angoli e ritorna una lista di encoder tramite l' uso dei parametri alfa,beta,gamma e delta definiti in self.param
        lista_e = []
        lista_e.append(int(-int(lista[0]) / self.param[0].value()))
        lista_e.append(int(-int(lista[1]) / self.param[1].value()))
        lista_e.append(int((int(lista[1]) + int(lista[2])) / self.param[1].value()))
        lista_e.append(int(0.5 * (
                    (int(lista[1]) + int(lista[2]) + int(lista[3])) / self.param[2].value() + lista[4] / self.param[
                3].value())))
        lista_e.append(int(0.5 * (
                    int(lista[4]) / self.param[3].value() - (int(lista[1]) + int(lista[2]) + int(lista[3])) /
                    self.param[2].value())))
        lista_e.append(int(self.maxValE[5].value() * int(lista[5]) / 100))  # e' una percentuale
        return lista_e

    def converti_in_a(self,
                      lista):  # prende in ingresso una lista di encoder e ritorna una lista di angoli tramite l' uso dei parametri alfa,beta,gamma e delta definiti in self.param
        lista_a = []
        lista_a.append(-self.param[0].value() * int(lista[0]))
        lista_a.append(-self.param[1].value() * int(lista[1]))
        lista_a.append(self.param[1].value() * (int(lista[1]) + int(lista[2])))
        lista_a.append(-self.param[1].value() * int(lista[2]) + self.param[2].value() * (int(lista[3]) - int(lista[4])))
        lista_a.append(self.param[3].value() * (int(lista[3]) + int(lista[4])))
        lista_a.append(round(int(lista[5]) * 100 / self.maxValE[5].value(), 3))
        return lista_a

    def cin_dir(self,
                lista):  # cinematica diretta. Prende in ingresso una lista di angoli espressi in gradi e restituisce una lista con x,y,z della pinza
        # valori del robot
        l1 = self.structVal[0].value()
        l2 = self.structVal[1].value()
        l3 = self.structVal[2].value()
        d1 = self.structVal[3].value()
        d5 = self.structVal[4].value()
        betad = self.structVal[5].value()
        omegad = self.structVal[6].value()

        ax = []
        # conversione degli angoli in radianti
        t1r = math.radians(lista[0])
        t2r = math.radians(lista[1])
        t3r = math.radians(lista[2])
        t4r = math.radians(lista[3])
        t5r = math.radians(lista[4])
        # calcolo della posizione del polso
        xpolso = math.cos(t1r) * (l1 + l2 * math.cos(t2r) + l3 * math.cos(t2r + t3r))
        ypolso = math.sin(t1r) * (l1 + l2 * math.cos(t2r) + l3 * math.cos(t2r + t3r))
        zpolso = d1 - l2 * math.sin(t2r) - l3 * math.sin(t2r + t3r)
        # calcolo della posizione della pinza(inserita direttamente nella lista)
        ax.append(xpolso - math.cos(t1r) * d5 * math.sin(t2r + t3r + t4r))
        ax.append(ypolso - math.sin(t1r) * d5 * math.sin(t2r + t3r + t4r))
        ax.append(zpolso - d5 * math.cos(t2r + t3r + t4r))
        return ax

    def cin_inv(self,
                lista):  # cinematica inversa. Prende una lista di x,y,z e restituisce una lista di angoli espressa in gradi
        # parametri robot
        l1 = self.structVal[0].value()
        l2 = self.structVal[1].value()
        l3 = self.structVal[2].value()
        d1 = self.structVal[3].value()
        d5 = self.structVal[4].value()
        betad = self.structVal[5].value()
        omegad = self.structVal[6].value()
        bdr = math.radians(betad)
        # calcolo dei theta
        theta1 = math.degrees(math.atan2(lista[1], lista[0]))
        theta1r = math.radians(theta1)
        A1 = lista[0] * (math.cos(theta1r)) + lista[1] * (math.sin(theta1r)) - d5 * (math.cos(bdr)) - l1
        A2 = d1 - lista[2] - d5 * (math.sin(bdr))
        A3 = (A1 * A1) + (A2 * A2) - (l2 * l2) - (l3 * l3)
        A4 = 2 * l2 * l3
        A5 = A3 / A4
        theta3 = math.acos(A5)

        # controllo gomito alto,gomito basso
        if self.Gomitobasso.isChecked() == True:
            theta3 = math.degrees(-1 * abs(theta3))
            theta3r1 = math.radians(theta3)
            A7 = (l2 + l3 * math.cos(theta3r1)) * A1 + l3 * math.sin(theta3r1) * A2
            A6 = (l2 + l3 * math.cos(theta3r1)) * A2 - l3 * math.sin(theta3r1) * A1
            theta2 = math.degrees(math.atan2(A6, A7))
            theta4 = betad - theta2 - theta3 - 90
            theta5 = omegad
        else:
            theta3 = abs(math.degrees(math.acos(A5)))
            theta3r = math.radians(theta3)
            A6 = (l2 + l3 * math.cos(theta3r)) * A2 - l3 * math.sin(theta3r) * A1
            A7 = (l2 + l3 * math.cos(theta3r)) * A1 + l3 * math.sin(theta3r) * A2
            theta2 = math.degrees(math.atan2(A6, A7))
            theta4 = betad - theta2 - theta3 - 90
            theta5 = omegad
        lista_a = [theta1, theta2, theta3, theta4, theta5, self.angle[5].value()]

        return lista_a

    def inserisci(self, lista,
                  tipo):  # funzione di inserimento dati nelle Qlabel della prima,seconda e terza pagina(se tipo='0') o di dati nella quarta pagina(se tipo='1')
        # lista contiene i dati da inserire ed e' [encode,correnti] se tipo='0' oppure [maxE,minE,maxC] se tipo='1'
        # tipo e' una variabile che esprime se il messaggio ricevuto riguarda un messaggio di dati o di impostazioni

        if tipo == 0:  # se ho un messaggi di dati([encoder,correnti])
            # pagina 1
            for i in range(0, len(self.listaHp)):  # mappatura encoder hardware con encoder per la home falsa
                lista[i] = int(lista[i]) - self.listaHp[i]

            for i in range(0, len(self.setup)):  # inserimento degli encoder attuali e calcolo dell' incremento(errore)
                self.setup[i].setText(str(lista[i]))
                self.encr[i].setText(str(int(self.encoder1[i].value() - int(self.setup[i].text()))))
            # cor pagina 1,2,3

            for i in range(0, len(self.cor)):  # conversione da ADC in corrente
                lista[i + nMot] = (int(lista[i + nMot]) * Vref) / (1024 * 0.185 * 1000)
            for i in range(0, len(self.cor)):  # inserimento correnti
                self.cor[i].setText(str(lista[i + nMot]))
                self.cor2[i].setText(str(lista[i + nMot]))
                self.cor3[i].setText(str(lista[i + nMot]))

            lista_a = self.converti_in_a(lista)
            # pagina 2
            for i in range(0, len(self.theta)):  # inserimento degli angoli attuali e calcolo dell' incremento(errore)
                self.theta[i].setText(str(round(lista_a[i], 3)))
                self.encr1[i].setText(str(round(self.angle[i].value() - float(self.theta[i].text()), 3)))

            # pagina 3
            lista_xyz = self.cin_dir(lista_a)
            for i in range(0, len(
                    self.ax)):  # inserimento della posizione della pinza attuale e calcolo dell' incremento(errore)
                self.ax[i].setText(str(round(lista_xyz[i], 3)))
                self.encr3[i].setText(str(round(self.inVal[i].value() - float(self.ax[i].text()), 3)))

        else:  # se ho un messaggio di impostazioni
            for i in range(0, len(self.maxValE)):
                self.maxValE[i].setValue(int(lista[i]))

            for i in range(0, len(self.cor)):  # conversione da ADC in corrente
                lista[i + 2 * nMot] = (int(lista[i + 2 * nMot]) * Vref) / (1024 * 0.185 * 8 * 1000)

            for i in range(0, len(self.minValE)):
                self.minValE[i].setValue(int(lista[i + nMot]))

            for i in range(0, len(self.maxValC)):
                self.maxValC[i].setValue(int(lista[i + 2 * nMot]))
            # aggiornamento valori massimi e minimi per la prima e terza pagina(la seconda ha gli angoli e max e min non cambiano) e per la home nella quarta
            """Quarta pagina"""
            for i in range(0, len(self.homePos)):
                self.homePos[i].setMaximum(self.maxValE[i].value())
                self.homePos[i].setMinimum(self.minValE[i].value())

            """Prima pagina"""
            for i in range(0, len(self.encoder1)):
                self.encoder1[i].setMaximum(self.maxValE[i].value())
                self.encoder1[i].setMinimum(self.minValE[i].value())

            """Terza pagina"""
            for i in self.inVal:  # max=l1+l2+l3,min=-(l1+l2+l3)
                i.setMaximum(int(self.structVal[0].value() + self.structVal[1].value() + self.structVal[
                    2].value()))  # il 20000 e' da prendere dalle impostazioni
                i.setMinimum(-int(self.structVal[0].value() + self.structVal[1].value() + self.structVal[
                    2].value()))  # il 20000 e' da prendere dalle impostazioni
            self.connect_db()  # salvo le nuove impostazioni su file

    def encoderValue(self):  # funzione pulsante prima pagina
        lista = []
        for i in range(0, len(self.encoder1)):  # prendo i valori degli encoder
            lista.append(self.encoder1[i].value())
        lista_a = self.converti_in_a(lista)  # li converto in angoli
        for i in range(0, len(self.angle)):  # aggiorno i valori nella seconda pagina
            self.angle[i].setValue(lista_a[i])
        lista_xyz = self.cin_dir(lista_a)  # li converto in posizione
        for i in range(0, len(self.inVal)):  # aggiorno i valori nella terza pagina
            self.inVal[i].setValue(lista_xyz[i])
        # mappo i valori degli encoder della home falsa in encoder per l' hardware
        for i in range(0, len(self.listaHp)):
            lista[i] = lista[i] + self.listaHp[i]
            # controllo se i valori sono piu' alti o piu' bassi dei valori max e min rispettivi inviabili
            if lista[i] > self.maxValE[i].value():
                lista[i] = self.maxValE[i].value()
            if lista[i] < self.minValE[i].value():
                lista[i] = self.minValE[i].value()
        # calcolo del nuovo incremento per le tre pagine
        for i in range(0, len(self.setup)):
            self.encr[i].setText(str(int(self.encoder1[i].value() - int(self.setup[i].text()))))
        for i in range(0, len(self.theta)):
            self.encr1[i].setText(str(round(self.angle[i].value() - float(self.theta[i].text()), 3)))
        for i in range(0, len(self.ax)):
            self.encr3[i].setText(str(round(self.inVal[i].value() - float(self.ax[i].text()), 3)))
        # invio i dati
        invia(lista, "e")

    def angleValue(self):  # funzione pulsante seconda pagina
        lista = []
        for i in self.angle:  # prendo i valori degli angoli
            lista.append(i.value())
        lista_e = self.converti_in_e(lista)  # li converto in encoder
        for i in range(0, len(self.encoder1)):  # aggiorno i valori nella prima pagina
            self.encoder1[i].setValue(lista_e[i])
        lista_xyz = self.cin_dir(lista)  # li converto in posizione
        for i in range(0, len(self.inVal)):  # aggiorno i valori nella terza pagina
            self.inVal[i].setValue(lista_xyz[i])
        # mappo i valori degli encoder della home falsa in encoder per l' hardware
        for i in range(0, len(self.listaHp)):
            lista_e[i] = lista_e[i] + self.listaHp[i]
            if lista_e[i] > self.maxValE[i].value():
                lista_e[i] = self.maxValE[i].value()
            if lista_e[i] < self.minValE[i].value():
                lista_e[i] = self.minValE[i].value()

        for i in range(0, len(self.setup)):
            self.encr[i].setText(str(int(self.encoder1[i].value() - int(self.setup[i].text()))))
        for i in range(0, len(self.theta)):
            self.encr1[i].setText(str(round(self.angle[i].value() - float(self.theta[i].text()), 3)))
        for i in range(0, len(self.ax)):
            self.encr3[i].setText(str(round(self.inVal[i].value() - float(self.ax[i].text()), 3)))

        invia(lista_e, "e")

    def inverseValue(self):  # funzione pulsante terza pagina
        lista = []
        for i in range(0, len(self.inVal)):  # prendo i valori della posizione della pinza
            lista.append(self.inVal[i].value())
            self.encr3[i].setText(str(lista[i]))
        lista_a = self.cin_inv(lista)  # li converto in angoli
        for i in range(0, len(self.angle) - 1):  # aggiorno i valori nella seconda pagina
            self.angle[i].setValue(lista_a[i])

        lista_e = self.converti_in_e(lista_a)  # li converto in encoder
        for i in range(0, len(self.encoder1)):  # aggiorno i valori nella prima pagina
            self.encoder1[i].setValue(lista_e[i])

        for i in range(0, len(self.listaHp)):
            lista_e[i] = lista_e[i] + self.listaHp[i]

            if lista_e[i] > self.maxValE[i].value():
                lista_e[i] = self.maxValE[i].value()
            if lista_e[i] < self.minValE[i].value():
                lista_e[i] = self.minValE[i].value()

        for i in range(0, len(self.setup)):
            self.encr[i].setText(str(int(self.encoder1[i].value() - int(self.setup[i].text()))))
        for i in range(0, len(self.theta)):
            self.encr1[i].setText(str(round(self.angle[i].value() - float(self.theta[i].text()), 3)))
        for i in range(0, len(self.ax)):
            self.encr3[i].setText(str(round(self.inVal[i].value() - float(self.ax[i].text()), 3)))

        invia(lista_e, "e")

    def setup1(self):  # funzione pulsante home quarta pagina
        # aggiornamento valori massimi e minimi per la prima e terza pagina(la seconda ha gli angoli e max e min non cambiano) e per la home nella quarta

        for i in range(0, len(self.homePos)):
            self.homePos[i].setMaximum(self.maxValE[i].value())
            self.homePos[i].setMinimum(self.minValE[i].value())

        """Prima pagina"""
        for i in range(0, len(self.encoder1)):
            self.encoder1[i].setMaximum(self.maxValE[i].value())  # il 20000 e' da prendere dalle impostazioni
            self.encoder1[i].setMinimum(self.minValE[i].value())  # il 20000 e' da prendere dalle impostazioni

        """Terza pagina"""
        # definizione valori massimi e minimi
        for i in self.inVal:
            i.setMaximum(int(self.structVal[0].value() + self.structVal[1].value() + self.structVal[
                2].value()))  # il 20000 e' da prendere dalle impostazioni
            i.setMinimum(-int(self.structVal[0].value() + self.structVal[1].value() + self.structVal[
                2].value()))  # il 20000 e' da prendere dalle impostazioni
        # aggiornamento della lista della nuova home falsa per la mappatura per la home hardware
        self.listaHp = []
        for i in self.homePos:
            self.listaHp.append(i.value())
            # invio le nuove impostazioni
        lista = []
        for i in self.maxValE:
            lista.append(i.value())

        for i in self.minValE:
            lista.append(i.value())

        for i in self.maxValC:
            lista.append(int((i.value() * 8 * 1024 * 0.185) / (Vref * 1000)))

        self.connect_db()  # salvo le nuove impostazioni
        invia(lista, "i")

    def connect_db(self):  # funzione per salvare su file le nuove impostazioni
        config = configparser.ConfigParser()
        config['DEFAULT'] = {'h1': self.homePos[0].value(),
                             'h2': self.homePos[1].value(),
                             'h3': self.homePos[2].value(),
                             'h4': self.homePos[3].value(),
                             'h5': self.homePos[4].value(),
                             'h6': self.homePos[5].value(),
                             'enM1': self.maxValE[0].value(),
                             'enM2': self.maxValE[1].value(),
                             'enM3': self.maxValE[2].value(),
                             'enM4': self.maxValE[3].value(),
                             'enM5': self.maxValE[4].value(),
                             'enM6': self.maxValE[5].value(),
                             'em1': self.minValE[0].value(),
                             'em2': self.minValE[1].value(),
                             'em3': self.minValE[2].value(),
                             'em4': self.minValE[3].value(),
                             'em5': self.minValE[4].value(),
                             'em6': self.minValE[5].value(),
                             'eC1': self.maxValC[0].value(),
                             'eC2': self.maxValC[1].value(),
                             'eC3': self.maxValC[2].value(),
                             'eC4': self.maxValC[3].value(),
                             'eC5': self.maxValC[4].value(),
                             'eC6': self.maxValC[5].value(),

                             'l1': self.structVal[0].value(),
                             'l2': self.structVal[1].value(),
                             'l3': self.structVal[2].value(),
                             'd1': self.structVal[3].value(),
                             'd5': self.structVal[4].value(),
                             'Bd': self.structVal[5].value(),
                             'Wd': self.structVal[6].value(),
                             'alfa': self.param[0].value(),
                             'beta': self.param[1].value(),
                             'gamma': self.param[2].value(),
                             'delta': self.param[3].value(),
                             }
        with open('config.ini', 'w') as configfile:
            config.write(configfile)

    def reset_i(self):  # setta le impostazioni della quarta pagina tramite i valori definiti nel file config_init.py
        self.Gomitoalto.setChecked(True)

        config = configparser.ConfigParser()
        config.read('.config_init.ini')

        self.homePos[0].setValue(int(config['DEFAULT']['h1']))
        self.homePos[1].setValue(int(config['DEFAULT']['h2']))
        self.homePos[2].setValue(int(config['DEFAULT']['h3']))
        self.homePos[3].setValue(int(config['DEFAULT']['h4']))
        self.homePos[4].setValue(int(config['DEFAULT']['h5']))
        self.homePos[5].setValue(int(config['DEFAULT']['h6']))

        self.maxValE[0].setValue(int(config['DEFAULT']['enM1']))
        self.maxValE[1].setValue(int(config['DEFAULT']['enM2']))
        self.maxValE[2].setValue(int(config['DEFAULT']['enM3']))
        self.maxValE[3].setValue(int(config['DEFAULT']['enM4']))
        self.maxValE[4].setValue(int(config['DEFAULT']['enM5']))
        self.maxValE[5].setValue(int(config['DEFAULT']['enM6']))

        self.minValE[0].setValue(int(config['DEFAULT']['em1']))
        self.minValE[1].setValue(int(config['DEFAULT']['em2']))
        self.minValE[2].setValue(int(config['DEFAULT']['em3']))
        self.minValE[3].setValue(int(config['DEFAULT']['em4']))
        self.minValE[4].setValue(int(config['DEFAULT']['em5']))
        self.minValE[5].setValue(int(config['DEFAULT']['em6']))

        self.maxValC[0].setValue(int(config['DEFAULT']['eC1']))
        self.maxValC[1].setValue(int(config['DEFAULT']['eC2']))
        self.maxValC[2].setValue(int(config['DEFAULT']['eC3']))
        self.maxValC[3].setValue(int(config['DEFAULT']['eC4']))
        self.maxValC[4].setValue(int(config['DEFAULT']['eC5']))
        self.maxValC[5].setValue(int(config['DEFAULT']['eC6']))

        self.structVal[0].setValue(float(config['DEFAULT']['l1']))
        self.structVal[1].setValue(float(config['DEFAULT']['l2']))
        self.structVal[2].setValue(float(config['DEFAULT']['l3']))
        self.structVal[3].setValue(float(config['DEFAULT']['d1']))
        self.structVal[4].setValue(float(config['DEFAULT']['d5']))
        self.structVal[5].setValue(float(config['DEFAULT']['Bd']))
        self.structVal[6].setValue(float(config['DEFAULT']['Wd']))

        self.param[0].setValue(float(config['DEFAULT']['alfa']))
        self.param[1].setValue(float(config['DEFAULT']['beta']))
        self.param[2].setValue(float(config['DEFAULT']['gamma']))
        self.param[3].setValue(float(config['DEFAULT']['delta']))
        # aggiornamento della lista della nuova home falsa per la mappatura per la home hardware
        self.listaHp = []
        for i in self.homePos:
            self.listaHp.append(i.value())
        lista = []
        for i in self.maxValE:
            lista.append(i.value())

        for i in self.minValE:
            lista.append(i.value())

        for i in self.maxValC:
            lista.append(int((i.value() * 8 * 1024 * 0.185) / (Vref * 1000)))
        self.connect_db()  # salvo le nuove impostazioni
        invia(lista, "i")
        invia(['home'], "a")  # ricerca home hardware
