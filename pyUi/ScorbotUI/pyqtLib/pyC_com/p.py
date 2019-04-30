
import os,sys
import signal
mex=[]
imp=[]
from PyQt5 import QtCore, QtGui, QtWidgets

def invia(mes_list,tipo):
 #messaggio e' la stringa da inviare,tipo deve essere="e" o ="i"
 #restituisce -1 se ho fallito l' invio,1 altrimenti
  messaggio=""
  messaggio=messaggio + str(tipo)
  for i in range(0,len(mes_list)):
    messaggio=messaggio + "|" + str(mes_list[i])
  messaggio=messaggio + "|\n"
  canale_r,canale_w=os.pipe()
  canale_r=sys.stdin 
  canale_w=sys.stdout
  cor=canale_w.write(messaggio)
  sys.stdout.flush()
  #cor=sys.stdout.write(messaggio) #cor indica i byte inviati ora
  if(cor<0):
     return -1
  pas=cor #pas tiene traccia di tutti i byte del messaggio inviati

  while(messaggio[pas-1]!='\n'): 
   cor=canale_w.write(messaggio)
   #cor=sys.stdout.write(messaggio[pas:])
   if(cor<0):
     return -1
   pas=pas+cor
  return 1

