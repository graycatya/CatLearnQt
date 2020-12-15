#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ToolList_currentRowChanged(int currentRow);

private:
    void InitUi();
    void InitProperty();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
