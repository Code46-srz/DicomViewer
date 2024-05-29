#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QAction>
#include "canvasview.h"
#include <QGridLayout>

QT_BEGIN_NAMESPACE
//namespace Ui { class MainWindow; }// defines Ui::MainWindow class
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT //macro used to implement signals and slots

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QAction *oAct;
    void setMenu();
    void open();
    void test();



private:
   // Ui::MainWindow *ui;
    CanvasView *canvas;
    QGridLayout *layout;

};
#endif // MAINWINDOW_H
