#include "mathespiel.h"
#include <QWidget>
#include <QDebug>
#include <QVBoxLayout>
#include <QGridLayout>

Mathespiel::Mathespiel(QWidget *parent)
    : QWidget(parent)
    , row(0)
    , column(0)
{
    setupButtons();
    setupUI();
}

Mathespiel::~Mathespiel()
{
}

void Mathespiel::setupButtons()
{
    int count = 1;
    for(int i = 0; i < 27; i++)
    {
        MyButton *newButton = new MyButton(i, true);
        newButton->setFixedSize(30, 30);
        connect(newButton, &MyButton::clicked, this, &Mathespiel::anyButtonClicked);
        if(i < 9)
        {
            newButton->setText(QString::number(i+1));
        }
        else {
            if (i % 2 == 0){
                newButton->setText(QString::number(count++));
            } else {
                newButton->setText(QString::number(1));
            }
        }
        buttons.push_back(newButton);
    }
}

void Mathespiel::setupUI()
{
    gridLayout = new QGridLayout();
    for(int i = 0; i < (int)buttons.size(); i++)
    {
        gridLayout->addWidget(buttons[i], row, column++);
        if((column % 9) == 0) {
            column = 0;
            row++;
        }
    }
    copyButton = new QPushButton("Abschreiben");
    copyButton->setText("Copy!");
    buttonsWidget = new QWidget();
    buttonsWidget->setLayout(gridLayout);
    connect(copyButton, &QPushButton::clicked, this, &Mathespiel::copyButtonClicked);
    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(copyButton);
    mainLayout->addWidget(buttonsWidget);
    setLayout(mainLayout);
    row++;
}

void Mathespiel::copyButtonClicked()
{
    int length = (int)buttons.size();
    for(int i = 0; i < length; i++) {
        if(buttons[i]->isActive)
        {
            MyButton *newButton = new MyButton(length+i, true);
            newButton->setFixedSize(30, 30);
            newButton->setText(buttons[i]->text());
            buttons.push_back(newButton);
            gridLayout->addWidget(newButton, row, column++);
            if(column % 9 == 0){
                row++;
                column = 0;
            }
        }
    }
}

void Mathespiel::anyButtonClicked()
{
    MyButton *btn = qobject_cast<MyButton*>(sender());
    qDebug() << btn->text();
}
