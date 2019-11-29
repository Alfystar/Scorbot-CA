//
// Created by alfyhack on 29/11/19.
//

#ifndef PIDCTRLDEMO_COMMONDEFINE_H
#define PIDCTRLDEMO_COMMONDEFINE_H
// Dichiaro le funzioni di interfaccia per inviare fuori i dati
typedef void (*ctrlRefSendFoo)(EncoderMot &);       // Funzione per il controllore che invia fuori i riferimenti
typedef void (*SettingSendFoo)(SettingBoard_C &);   // Funzione che invia alla board le nuove impostazioni
typedef SettingBoard_C &(*SettingGetFoo)(void);    // Funzione che richiede alla board le sue impostazioni
//todo Aggiungere la funzione per personalizzare il controllore

struct extFooCall {
    ctrlRefSendFoo ctrlFunx;
    SettingSendFoo setSendFunx;
    SettingGetFoo setGetFunx;
};
#endif //PIDCTRLDEMO_COMMONDEFINE_H
