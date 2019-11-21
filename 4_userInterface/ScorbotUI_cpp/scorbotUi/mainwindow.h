#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DataTransfert_AllInclude.h>
#include <iostream>

/// Qt lib
#include <QMainWindow>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>
#include <QRadioButton>

namespace Ui {
    class MainWindow;
}
using namespace DataPrimitive;
using namespace DataManipolation;

class MainWindow : public QMainWindow {
Q_OBJECT  //Macro di Qt che importa tutti i metodi virtuali necessari, senza doverli scrvere a mano

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void testPrint();
private:
    Ui::MainWindow *ui;
    /// Riferimenti da inviare
    //Diretta en
    QSpinBox *enRef[nMot];
    //Diretta angolata
    QDoubleSpinBox *thetaRef[nMot - 1];
    QSlider *pinzaRef;
    //Inversa
    QDoubleSpinBox *pDes[3];
    QDoubleSpinBox *pOri[2];
    QSlider *pinzaInv;
    QRadioButton *gomito[2];

    /// Data send
    QPushButton *sendRef;

    ///Robot Setup

};

#endif // MAINWINDOW_H
