# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '/home/catgray/catgray/code/CatLearnQt/examples/QCatGrayWidgetExamples/WidgetTools/TableViewTool.ui'
#
# Created by: PyQt5 UI code generator 5.15.6
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_TableViewTool(object):
    def setupUi(self, TableViewTool):
        TableViewTool.setObjectName("TableViewTool")
        TableViewTool.resize(791, 607)
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(TableViewTool)
        self.verticalLayout_2.setContentsMargins(30, 30, 30, 30)
        self.verticalLayout_2.setSpacing(0)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.verticalLayout = QtWidgets.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.TableView = CatTableViewTool(TableViewTool)
        self.TableView.setObjectName("TableView")
        self.verticalLayout.addWidget(self.TableView)
        self.BottomWidget = QtWidgets.QWidget(TableViewTool)
        self.BottomWidget.setMaximumSize(QtCore.QSize(16777215, 50))
        self.BottomWidget.setObjectName("BottomWidget")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.BottomWidget)
        self.horizontalLayout.setObjectName("horizontalLayout")
        spacerItem = QtWidgets.QSpacerItem(20, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem)
        self.Paging = QCatGrayPagingNavigation(self.BottomWidget)
        self.Paging.setObjectName("Paging")
        self.horizontalLayout.addWidget(self.Paging)
        spacerItem1 = QtWidgets.QSpacerItem(20, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem1)
        self.verticalLayout.addWidget(self.BottomWidget)
        self.verticalLayout_2.addLayout(self.verticalLayout)

        self.retranslateUi(TableViewTool)
        QtCore.QMetaObject.connectSlotsByName(TableViewTool)

    def retranslateUi(self, TableViewTool):
        _translate = QtCore.QCoreApplication.translate
        TableViewTool.setWindowTitle(_translate("TableViewTool", "Form"))
from CatTableViewTools.CatTableViewTool import CatTableViewTool
from QCatGrayPagingNavigation import QCatGrayPagingNavigation
