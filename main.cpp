#include "mathespiel.h"
#include <iostream>
#include <QApplication>
#include <QStyleFactory>
#include <vector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mathespiel w;
    w.show();
    a.setStyle(QStyleFactory::create("Fusion"));
    return a.exec();
}
