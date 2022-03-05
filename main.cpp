#include "mathespiel.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mathespiel w;
    w.show();
    a.setStyle(QStyleFactory::create("Fusion"));
    return a.exec();
}
