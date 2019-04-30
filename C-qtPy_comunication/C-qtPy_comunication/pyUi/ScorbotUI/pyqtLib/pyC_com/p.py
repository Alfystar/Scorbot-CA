
from PyQt5 import QtCore, QtGui, QtWidgets

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

