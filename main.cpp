#include "mainwindow.h"
//#include <dcmtk/dcmdata/dctk.h>
//#include <dcmtk/dcmimgle/dcmimage.h>
#include <iostream>
#include <Qdebug>
#include <QApplication>
#include <QtWidgets>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv); //QApplication object is created
                               //everything will be inside this object
//    QWidget window;//window object is created
//        window.resize(320, 240);
//        window.setWindowTitle
//            (QApplication::translate("childwidget", "Child widget"));
//        window.show();

//    QPushButton *button = new QPushButton(
//        QApplication::translate("childwidget", "Press me"), &window);
//    button->move(100, 100);
//    button->show();



  MainWindow w;
  w.show();
    return a.exec();
}
