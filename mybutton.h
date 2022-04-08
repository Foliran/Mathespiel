#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QWidget>
#include <QObject>

class MyButton : public QPushButton
{
Q_OBJECT

public:
    MyButton(int, bool);
    int index;
    bool isActive;
};

#endif // MYBUTTON_H
