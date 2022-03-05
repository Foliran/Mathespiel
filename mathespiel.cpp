#include "mathespiel.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>

Mathespiel::Mathespiel(QWidget *parent)
    : QWidget(parent)
{
    setupButtons();
    setupUI();
}

Mathespiel::~Mathespiel()
{
}

void Mathespiel::setupButtons()
{
    buttons.resize(3, std::vector<MyButton*>(9));
    int count = 1;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            buttons[i][j] = new MyButton(i, j, true);
            buttons[i][j]->setFixedSize(50, 50);
            if (i == 0)
            {
                buttons[i][j]->setText(QString::number(j+1));
            }
            else
            {
                if((i + j) % 2 == 1)
                {
                    buttons[i][j]->setText(QString::number(1));
                }
                else
                {
                    buttons[i][j]->setText(QString::number(count++));
                }
            }
        }
    }
}

void Mathespiel::setupUI()
{
    QPushButton *copyButton = new QPushButton("Abschreiben");
    QGridLayout *gridLayout = new QGridLayout();
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            gridLayout->addWidget(buttons[i][j], i, j);
        }
    }
    QWidget *buttonsWidget = new QWidget();
    buttonsWidget->setLayout(gridLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(buttonsWidget);
    mainLayout->addWidget(copyButton);
    setLayout(mainLayout);
}
