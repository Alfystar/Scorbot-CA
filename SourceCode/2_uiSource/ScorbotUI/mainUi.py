from python_work.myUiClass import *

import sys
from threading import Thread

class InputThread (Thread):
    def __init__(self,ui):
        Thread.__init__(self)
        self.text=""
        self.ui=ui


    def run(self):
        while True:
            #leggi() #riceve e fa il parsing della stringa ricevuta restituendo una lista
            #prova
            #i=invia([0,1,2,3,4,5],"e")
            
            self.leggi() #riceve e fa il self.passi1_direct.text()parsing della stringa ricevuta restituendo una lista

            #i=invia(imp,"i")


    def leggi(self): #legge il messaggio e fa il parsing
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
         self.ui.updateSensor(lista[1:], 0)
     else:
         self.ui.updateSensor(lista[1:], 1)
     return 

 

if __name__ == '__main__':

    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = MyUiQt(MainWindow)
    
    MainWindow.show()

    inTh = InputThread(ui)
    inTh.start()
    app.exec_()


