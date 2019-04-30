
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
imp=[]
class InputThread (Thread):
    def __init__(self, ui):
        Thread.__init__(self)
        self.text=""
        self.ui = ui

    def run(self):
        while True:
            leggi() #riceve e fa il parsing della stringa ricevuta restituendo una lista
            #prova
            i=invia(mex,"e")
            leggi() #riceve e fa il parsing della stringa ricevuta restituendo una lista
            #prova
            i=invia(imp,"i")
            
            
            


def invia(mes_list,tipo):
 #messaggio e' la stringa da inviare,tipo deve essere="e" o ="i"
 #restituisce -1 se ho fallito l' invio,1 altrimenti
  messaggio=""
  messaggio=messaggio + str(tipo)
  for i in range(0,len(mes_list)):
    messaggio=messaggio + "|" + str(mes_list[i])
  messaggio=messaggio + "|\n"
        

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

    if (lista[0]=='e'):
      global mex
      mex=lista[1:]
    else:
      global imp
      imp=lista[1:]             
    return 


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