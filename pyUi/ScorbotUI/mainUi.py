import sys
from PyQt5 import QtCore, QtGui, QtWidgets

from pyUi.ScorbotUI.myUiClass import MyUiQt


if __name__ == '__main__':


    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = MyUiQt(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())