# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '/home/catgray/catgray/code/CatLearnQt/examples/QCatGrayWidgetExamples/CatWidget.ui'
#
# Created by: PyQt5 UI code generator 5.15.6
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_CatWidget(object):
    def setupUi(self, CatWidget):
        CatWidget.setObjectName("CatWidget")
        CatWidget.resize(733, 517)
        self.horizontalLayout = QtWidgets.QHBoxLayout(CatWidget)
        self.horizontalLayout.setContentsMargins(2, 2, 2, 2)
        self.horizontalLayout.setSpacing(2)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.ToolWidget = QtWidgets.QWidget(CatWidget)
        self.ToolWidget.setMinimumSize(QtCore.QSize(60, 0))
        self.ToolWidget.setMaximumSize(QtCore.QSize(60, 16777215))
        self.ToolWidget.setObjectName("ToolWidget")
        self.horizontalLayout.addWidget(self.ToolWidget)
        self.ToolStackedWidget = QtWidgets.QStackedWidget(CatWidget)
        self.ToolStackedWidget.setObjectName("ToolStackedWidget")
        self.horizontalLayout.addWidget(self.ToolStackedWidget)

        self.retranslateUi(CatWidget)
        QtCore.QMetaObject.connectSlotsByName(CatWidget)

    def retranslateUi(self, CatWidget):
        _translate = QtCore.QCoreApplication.translate
        CatWidget.setWindowTitle(_translate("CatWidget", "Form"))
