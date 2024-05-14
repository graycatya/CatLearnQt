#ifndef CATQCUSTOMPLOTTOOLS_H
#define CATQCUSTOMPLOTTOOLS_H

#include <QWidget>
#include <QHash>

class QPushButton;
class QCatGrayListingOptions;

namespace Ui {
class CatQcustomplotTools;
}

class CatQcustomplotTools : public QWidget
{
    Q_OBJECT

public:
    explicit CatQcustomplotTools(QWidget *parent = nullptr);
    ~CatQcustomplotTools();

private:
    void InitUi();
    void InitProperty();
    void InitConnect();

    void UpdateStyle();

    void InitChartsTool();
    void InitChartWidgets();

private slots:
    void On_ToolButtons(int);

private:
    Ui::CatQcustomplotTools *ui;
    QCatGrayListingOptions *m_pToolListiongOptions;
    QHash<QString, QPushButton*> m_pToolButtons;
};

#endif // CATQCUSTOMPLOTTOOLS_H
