#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QWidget>

class MyButton : public QPushButton
{
public:
    MyButton(int, int, bool);
    int x;
    int y;
    bool isActive;
};

#endif // MYBUTTON_H
