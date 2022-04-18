#include "mathespiel.h"
#include <QWidget>
#include <QDebug>
#include <QVBoxLayout>
#include <QGridLayout>

Mathespiel::Mathespiel(QWidget *parent)
    : QWidget(parent)
    , secondClick(false)
    , row(0)
    , column(0)
{
    setupButtons();
    setupUI();
    lastButton = new MyButton(0, false);
    lastButton->setStyleSheet("background-color: green");
    clickedButton = new MyButton(0, false);
    preLastButton = new MyButton(0, false);
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
        newButton->setStyleSheet("background-color: white");
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
            newButton->setStyleSheet("background-color: white");
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
    clickedButton = qobject_cast<MyButton*>(sender());
    if(preLastButton->isActive) preLastButton->setStyleSheet("background-color: white");
    if(lastButton->isActive) lastButton->setStyleSheet("background-color: green");
    if(clickedButton->isActive) clickedButton->setStyleSheet("background-color: green");

    //checke, ob der Click vom Wert her erlaubt ist erlaubt ist
    if((lastButton->text().toInt() == clickedButton->text().toInt()) || (lastButton->text().toInt() + clickedButton->text().toInt() == 10))
    {
        qDebug() << "One of the cases is true";
        //Dann checke, ob beide aktiv sind
        if((lastButton->isActive && clickedButton->isActive) && (lastButton->index != clickedButton->index))
        {
            qDebug() << "And both buttons are active";
            //Dann checke, ob Position passt
            if(std::abs(lastButton->index - clickedButton->index) == 1)
            {
                qDebug() << "Buttons are 1 apart";
                clickedButton->isActive = false;
                lastButton->isActive = false;
                clickedButton->setStyleSheet("background-color: black");
                lastButton->setStyleSheet("background-color: black");
            }
            //The last two cses doen't work anymore
            else if ((lastButton->index % 9) == (clickedButton->index % 9))
            {
                qDebug() << "Buttons are same column";
                int minimum = std::min(lastButton->index, clickedButton->index);
                int maximum = std::max(lastButton->index, clickedButton->index);
                bool check = true;
                for(int i = minimum; i <= maximum; i+=9)
                {
                    if(buttons[i]->isActive)
                    {
                        check = false;
                    }
                }
                if(check)
                {
                    clickedButton->isActive = false;
                    lastButton->isActive = false;
                    clickedButton->setStyleSheet("background-color: black");
                    lastButton->setStyleSheet("background-color: black");
                }
            }
            else {
                qDebug() << "Check the last case";
                int minimum = std::min(lastButton->index, clickedButton->index);
                int maximum = std::max(lastButton->index, clickedButton->index);
                bool check = true;
                for(int i = minimum; i <= maximum; i++)
                {
                    if(!buttons[i]->isActive)
                    {
                        check = false;
                    }
                }
                if(check)
                {
                    clickedButton->isActive = false;
                    lastButton->isActive = false;
                    clickedButton->setStyleSheet("background-color: black");
                    lastButton->setStyleSheet("background-color: black");
                }

            }
        }
    }
    preLastButton = lastButton;
    lastButton = clickedButton;
    qDebug() << "---------------------------------------------";
}
