import matplotlib
from PyQt5 import QtWidgets
from PyQt5.QtCore import QObject, Qt, pyqtSignal
from PyQt5.QtWidgets import (QSpinBox, QSlider, QLabel)

matplotlib.use('Qt5Agg')
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as Canvas
from matplotlib.figure import Figure
import numpy

from functools import partial  # per permettere di creare i connect con gli array


class Communicate(QObject):
    updateBW = pyqtSignal(int)


class CurveSelector():
    nPar=4

    def __init__(self,widget,x,y,nPar=4):
        self.widget=widget
        self.x=x
        self.y=y
        self.nPar=nPar

        selettori = CurveSelectotSlide(widget, self.nPar,self.x, self.y,45)
        grafico = PlotCanvas(self.widget, self.nPar)
        selettori.setEventSave(grafico.setKoef)
        grafico.move(self.x, self.y+selettori.heigth+10)



# Matplotlib canvas class to create figure
class PlotCanvas(Canvas):
    k=[]
    DIV = 100
    def __init__(self,parent=None, parameter=4,div=100,width=5, height=4, dpi=100):
        """
        La funzione crea un grafico per la funzione del pedale dell'acceleratore.
        si può vedere il grafico della risposta al variare dell'acceleratore (asse X) e il dato sull'y è il dato modificato
        :param parent:  è il windget su cui verrà visuallizzato il grafico
        :param parameter:   sono i numeri di parametri da contare
        :param width:   larghezza in pollici
        :param height:  altezza in pollici
        :param dpi:     punti per pollice
        """
        fig = Figure(figsize=(width, height), dpi=dpi)              #creo l'oggetto figura
        super().__init__( fig)                                      #canvas è effettivamente l'oggetto da graficare, gli passo l'oggetto su cui lavorare
        self.setParent(parent)                                      #qt funziona a classi collegate, se una si chiudesse o venisse cancellata, allora anche questa si chiuderebbe

        super().setSizePolicy( QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        #super().updateGeometry()
        super().setStyleSheet("background-color:transparent;")

        """definisco il numeri di coefficenti da usare"""
        for i in range(parameter):
            self.k.append(0)
        self.k[0]=1

        self.DIV=div

        self.plot() #funzione di plot

    def plot(self):
        """
        Semplicemente plotta tutto il grafico della risposta per i parametri impostati in k[]
        :return:
        """

        """configurazione dei parametri del grafico"""
        x_value = numpy.linspace(0, 1,100)
        self.figure.clear()                 #pulisco la vecchia linea
        ax = self.figure.add_subplot(111)
        ax.grid(color='black', linestyle='-', linewidth=0.1)
        ax.set_xlim([0, 1])
        ax.set_ylim([-0.2, 1.2])

        tpsMod = [self.funxScalar(x)/self.funxScalar(1) for x in x_value ]
        """per la derivata dai calcoli segue che devo fare così altrimenti in
        alcuni punti può funzionare all'inverso"""
        derTpsMod = [(self.derFunxScalar(x)/self.funxScalar(1)) for x in x_value ]
        toPrintlist=[]

        for i in range(len(tpsMod)):
            if(derTpsMod[i]<0):
                toPrintlist.append(False)
            else:
                toPrintlist.append(True)



        """il successivo blocco non fa altro che dividere in sezioni i punti,
         così da poter printare evidenziando i decrementi"""
        indexList=[]
        idStart = 0
        idEnd = 0
        for i in range(0,len(toPrintlist)-1):
            if(toPrintlist[i]==toPrintlist[i+1]):
                idEnd+=1
            else:
                indexList.append([toPrintlist[idStart],idStart,idEnd+2])
                idStart=idEnd+1
                idEnd=idStart
        indexList.append([toPrintlist[idStart], idStart, len(toPrintlist)])
        #print(indexList)
        """plot parametrico in base alla sezione"""
        for zone in indexList:
            if (zone[0]):
                ax.plot(x_value[zone[1]:zone[2]], tpsMod[zone[1]:zone[2]], 'b-')
            else:
                ax.plot(x_value[zone[1]:zone[2]], tpsMod[zone[1]:zone[2]], 'r-')

        """aggiunta delle linee guida per orientarsi"""
        ax.plot([0, 1], [0, 1], 'g--')
        ax.plot([0,1],[0,0], 'r:')      #retta inferiore p1=(0,0) p2=(1,0)
        ax.plot([0,1],[1,1], 'r:')      #retta superiore p1=(0,1) p2=(1,1)

        """Titoli degli assi"""
        ax.set_title('Risposta TPS Modificata')
        ax.set_xlabel("TPS-read")
        ax.set_ylabel("TPS-trasform")

        self.draw()

    def funxScalar(self,x):
        """
        Funzione di trasferimento modificata non normalizzata, nella sua forma estesa è:
        k1*x+k2*x^2+k3*x^3+..... //tanti quanto è stato detto in parameter
        :param x: coordinata per cui calcolare
        :return:
        """
        val=0
        i=1
        for coef in self.k:
            val+=coef * x**i
            i+=1
        return val

    def derFunxScalar(self,x):
        """
        Derivata della funzione di trasferimento modificata non normalizzata, nella sua forma estesa è:
        k1*x^0*1+k2*x^1*2+k3*x^2*3+..... //tanti quanto è stato detto in parameter
        :param x: coordinata per cui calcolare
        :return:
        """
        val=0
        i=0
        for coef in self.k:
            val+= coef * x**i * (i + 1)
            i+=1
        return val


    def setKoef(self,tripletta):
        """
        Funzione evento che viene invocata quando viene cambiato lo slider corrispondente.
        essa cambia il k in esame e riesegue plot
        :param id:
        :param tripletta: è la tripletta, slider,laber,id da cui leggere tutti i parametri
        :return:
        """
        val=tripletta[0].value()
        #print("evento id={} val={}".format(id,val))
        self.k[tripletta[2]]=val/self.DIV
        self.plot()


class CurveSelectotSlide():

    x_Offset = 30
    y_Offset = 30
    width = 30
    heigth = 150
    n = 4                   #numero selettori
    RANGE_K = 200          #range di interi da raggiungere col cursore
    DIV =100                #valore per cui dividere così da avere la virgola

    def __init__(self,widget,n=4,X=30,Y=30,l=60,h=150,div=100):
        """
        La classe permette di creare una serie di slide verticali una accanto all'altra e di fianco la visualizzazione
        dei parametri k. Permette poi di
        :param widget: è la finestra su cui deve lavorare tutta la classe
        :param n: numero di slide da creare
        :param X: posizione X del gruppo (alto a sinistra)
        :param Y: posizione Y del gruppo (alto a sinistra)
        :param l: larghezza tra gli slider
        :param h: altezza dei singoli slide
        """
        self.widget=widget
        self.x_Offset = X
        self.y_Offset = Y
        self.width = l
        self.heigth = h
        self.n = n
        self.DIV=div

        self.UiSetup()

    def UiSetup(self):
        """
        La funzione disegna nel widget(finestra) desiderata n° slide uno di fianco all'altro tutti parametrici
        e il primo lo inizializza a 1 così da avere una retta
        :return:
        """

        self.unicum=[]
        for i in range(self.n):
            appoggio =[]
            appoggio.append(QSlider(Qt.Vertical, self.widget))       #in 1° pos troviamo lo slider
            appoggio.append(QLabel("current value:", self.widget))   #in 2° pos troviamo il testo
            appoggio.append(i)                                  #in 3° posizione discrimino quale elemento è
            appoggio.append((QSpinBox(self.widget)))
            self.unicum.append(appoggio)

        i=0
        for elem in self.unicum:
            """Istanzio i parametri base degli slide"""
            elem[0].setFocusPolicy(Qt.NoFocus)
            elem[0].setRange(-self.RANGE_K,self.RANGE_K)
            elem[0].setGeometry(self.x_Offset + i * self.width, self.y_Offset, self.width, self.heigth)

            if (i != 0):
                elem[0].setValue(0)
            else:
                elem[0].setValue(1*self.DIV)              #faccio partire il primo slider a 1.0 per avere una retta

            """Istanzio i parametri base dei label per leggere i valori"""
            elem[1].setFocusPolicy(Qt.NoFocus)
            elem[1].setText("current value of K"+str(i)+": "+str(elem[0].value()/self.DIV))
            elem[1].setGeometry(self.x_Offset+self.n*self.width+5, self.y_Offset + 30 * i, 180,30)

            """Istanzio gli SpinBox"""
            elem[3].setRange(-self.RANGE_K,self.RANGE_K)
            elem[3].setSingleStep(1)
            elem[3].setGeometry(self.x_Offset+self.n*self.width+180+5, self.y_Offset + 30 * i,60,30)
            elem[3].setValue(elem[0].value())

            """Creo il collegamento all'evento di cambio dello slide per aggiornare i label"""
            elem[0].valueChanged.connect(partial(self.valuechangeSlider,elem))        #partial permette di passare più parametri, come fossero keyword di attivazione
            elem[3].valueChanged.connect(partial(self.valuechangeSpinBox,elem))
            #elem[0].valueChanged.connect(lambda :(self.valuechange(elem)) )    #a scopo dimostrativo dei problemi di lambda
            i+=1

    def valuechangeSlider(self,i):
        """
        Funzione evento per permettere di cambiare testo e gli spin value quando cambia il valore dello slider
        :param i: indice dello slider da cambiare (serve perchè è un array)
        :return:
        """
        i[1].setText("current value of K"+str(i[2])+": "+str(i[0].value()/self.DIV))
        i[3].setValue(i[0].value())

    def valuechangeSpinBox(self,i):
        """
        Funzione evento per permettere di cambiare testo e gli spin value quando cambia il valore dello slider
        :param i: indice dello slider da cambiare (serve perchè è un array)
        :return:
        """
        i[1].setText("current value of K"+str(i[2])+": "+str(i[0].value()/self.DIV))
        i[0].setValue(i[3].value())

    def setGeometry(self,X,Y,l=30,h=150):
        self.x_Offset = X
        self.y_Offset = Y
        self.width=l
        self.heigth=h

    def getValues(self):
        l=[]
        for i in self.unicum:
            l.append(i[0].value())
        return l

    def setEventSave(self,funxDest):
        """
        Crea gli eventi di cambio degli slide verso la funzione plot:
        Quando i valori cambiano viene chiamata la funzione che cambia il parametro k e ricalcola il grafico
        :param funxDest: funzione che viene eseguita quando c'è l'evento
        :return:
        """
        i=0
        for elem in self.unicum:
            """essendo che la funzione di destinazione va a prendere il valore direttamente dallo slide"""
            elem[0].valueChanged.connect(partial(funxDest,elem)  )      #partial permette di passare più parametri, come fossero keyword di attivazione
            i+=1

#class SubAddButton(Qt)
