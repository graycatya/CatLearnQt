# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '/home/catgray/catgray/code/CatLearnQt/examples/QCatGrayWidgetExamples/CatDrawingBoard.ui'
#
# Created by: PyQt5 UI code generator 5.15.6
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_CatDrawingBoard(object):
    def setupUi(self, CatDrawingBoard):
        CatDrawingBoard.setObjectName("CatDrawingBoard")
        CatDrawingBoard.resize(723, 453)
        self.verticalLayout = QtWidgets.QVBoxLayout(CatDrawingBoard)
        self.verticalLayout.setContentsMargins(2, 2, 2, 2)
        self.verticalLayout.setSpacing(2)
        self.verticalLayout.setObjectName("verticalLayout")
        self.GraphicsTopToolWidget = QtWidgets.QWidget(CatDrawingBoard)
        self.GraphicsTopToolWidget.setMinimumSize(QtCore.QSize(0, 35))
        self.GraphicsTopToolWidget.setObjectName("GraphicsTopToolWidget")
        self.verticalLayout.addWidget(self.GraphicsTopToolWidget)
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setContentsMargins(0, -1, -1, -1)
        self.horizontalLayout.setSpacing(2)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.GraphicsToolWidget = QtWidgets.QWidget(CatDrawingBoard)
        self.GraphicsToolWidget.setMinimumSize(QtCore.QSize(60, 0))
        self.GraphicsToolWidget.setMaximumSize(QtCore.QSize(60, 16777215))
        self.GraphicsToolWidget.setObjectName("GraphicsToolWidget")
        self.horizontalLayout.addWidget(self.GraphicsToolWidget)
        self.GraphicsStacked = QtWidgets.QStackedWidget(CatDrawingBoard)
        self.GraphicsStacked.setObjectName("GraphicsStacked")
        self.horizontalLayout.addWidget(self.GraphicsStacked)
        self.verticalLayout.addLayout(self.horizontalLayout)

        self.retranslateUi(CatDrawingBoard)
        QtCore.QMetaObject.connectSlotsByName(CatDrawingBoard)

    def retranslateUi(self, CatDrawingBoard):
        _translate = QtCore.QCoreApplication.translate
        CatDrawingBoard.setWindowTitle(_translate("CatDrawingBoard", "Form"))