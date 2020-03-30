#!/usr/bin/env python3

import sys
from CurveSelectot import *
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import *

if __name__ == '__main__':
    app = QApplication(sys.argv)
    mainWidget = QMainWindow()

    curve = CurveSelector(mainWidget, 10, 10, 5)
    mainWidget.setGeometry(10, 10, 600, 600)
    mainWidget.setWindowTitle("Trottle Board Debug")
    mainWidget.setWindowIcon(QIcon("STV.ico"))
    mainWidget.show()

    sys.exit(app.exec())





