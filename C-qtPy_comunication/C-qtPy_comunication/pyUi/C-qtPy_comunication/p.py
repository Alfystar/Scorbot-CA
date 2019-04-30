
from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(397, 93)
        self.gridLayout = QtWidgets.QGridLayout(Form)
        self.gridLayout.setObjectName("gridLayout")
        self.label = QtWidgets.QLabel(Form)
        self.label.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.label.setAlignment(QtCore.Qt.AlignCenter)
        self.label.setObjectName("label")
        self.gridLayout.addWidget(self.label, 0, 0, 1, 1)
        self.lineEdit = QtWidgets.QLineEdit(Form)
        self.lineEdit.setEnabled(True)
        self.lineEdit.setReadOnly(True)
        self.lineEdit.setObjectName("lineEdit")
        self.gridLayout.addWidget(self.lineEdit, 1, 0, 1, 1)
        self.lineEdit.setText("Ciao mondo")


        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.label.setText(_translate("Form", "From Terminal read"))


import sys
import signal
from threading import Thread
mex=[]

class InputThread (Thread):
    def __init__(self, ui):
        Thread.__init__(self)
        self.text=""
        self.ui = ui

    def run(self):
        while True:
            mex=leggi() #riceve e fa il parsing della stringa ricevuta restituendo una lista
            #prova
            buffer=componi_messaggio(mex)
            i=invia(buffer)
            
            

def componi_messaggio(mes_list):
  #mes_list e' una lista cosi' fatta: [e1,e2,e3,e4,e5,e6,c1,c2,c3,c4,c5,c6,imp]
  #restituisce la stringa da inviare secondo il formato  
    messaggio=""
    messaggio=messaggio + str(mes_list[0])
    for i in range(1,14):
      messaggio=messaggio + "|" + str(mes_list[i])
    messaggio=messaggio + "|\n"
        
    return messaggio


def invia(messaggio):
 #messaggio e' la stringa da inviare
 #restituisce -1 se ho fallito l' invio,1 altrimenti
 cor=sys.stdout.write(messaggio) #cor indica i byte inviati ora
 if(cor<0):
     return -1
 pas=cor #pas tiene traccia di tutti i byte del messaggio inviati

 while(messaggio[pas-1]!='\n'): 
   cor=sys.stdout.write(messaggio[pas:])
   if(cor<0):
     return -1
   pas=pas+cor
 return 1

def leggi(): #legge il messaggio e fa il parsing
  #restituisce la lista dei dati
    pas=0
    messaggio = input()
    lista=[]
    testo=""
    for i in range (0,len(messaggio)):
         if (i == len(messaggio)-1):
             testo = testo + messaggio[i]
             lista.append(testo) 
         if messaggio[i]=='|':
           lista.append(testo)
           testo=""
         else:
           testo=testo + messaggio[i]      
    return lista


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    Form = QtWidgets.QWidget()
    ui = Ui_Form()
    ui.setupUi(Form)
    Form.show()

    inTh = InputThread(ui)
    inTh.start()
    app.exec_()
    
      
    #signal.pause()