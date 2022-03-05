#ifndef MATHESPIEL_H
#define MATHESPIEL_H

#include <QMainWindow>
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
    void copyButtonClicked();
private:
    std::vector<std::vector<MyButton*>> buttons;
};
#endif // MATHESPIEL_H
