#ifndef MATHESPIEL_H
#define MATHESPIEL_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include "mybutton.h"
#include <vector>

class Mathespiel : public QWidget
{
    Q_OBJECT

public:
    Mathespiel(QWidget *parent = nullptr);
    ~Mathespiel();
    void setupUI();
    void setupButtons();

private:
    std::vector<MyButton*> buttons;
    QVBoxLayout* mainLayout;
    QWidget* buttonsWidget;
    QGridLayout* gridLayout;
    QPushButton *copyButton;
    MyButton *lastButton;
    MyButton *clickedButton;
    MyButton *preLastButton;
    bool secondClick;
    int row, column;

public slots:
    void copyButtonClicked();
    void anyButtonClicked();
};
#endif // MATHESPIEL_H
