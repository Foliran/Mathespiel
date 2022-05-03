#include "mathespiel.h"
#include <QWidget>
#include <QDebug>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QStyleFactory>
#include <QSpacerItem>

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
    gridLayout->setSizeConstraint(QLayout::SetFixedSize);
    row--;
    copyButton = new QPushButton("Abschreiben");
    copyButton->setText("Copy!");
    buttonsWidget = new QWidget();
    buttonsWidget->setLayout(gridLayout);
    connect(copyButton, &QPushButton::clicked, this, &Mathespiel::copyButtonClicked);
    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(copyButton);
    mainLayout->addWidget(buttonsWidget);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainLayout);
    row++;
}

void Mathespiel::copyButtonClicked()
{
    int length = (int)buttons.size();
    int newIndex = length;
    if(checkForPairs())
    {
        QMessageBox *msg = new QMessageBox();
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->setStandardButtons(QMessageBox::Ok);
        msg->setText("<p align='center'>Es sind noch Paare übrig!<br>");
        msg->setStyle(QStyleFactory::create("Fusion"));
        msg->show();
    }
    else
    {
        for(int i = 0; i < length; i++) {
            if(buttons[i]->isActive)
            {
                MyButton *newButton = new MyButton(newIndex++, true);
                newButton->setFixedSize(30, 30);
                newButton->setText(buttons[i]->text());
                newButton->setStyleSheet("background-color: white");
                connect(newButton, &QPushButton::clicked, this, &Mathespiel::anyButtonClicked);
                buttons.push_back(newButton);
                gridLayout->addWidget(newButton, row, column++);
                if(column % 9 == 0){
                    row++;
                    column = 0;
                }
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
        //Checke, ob es verschiedene Buttons sind
        //Dann checke, ob beide aktiv sind
        if(!(clickedButton->index == lastButton->index))
        {
            if((lastButton->isActive && clickedButton->isActive))
            {
                //Dann checke, ob Position passt
                if(std::abs(lastButton->index - clickedButton->index) == 1)
                {
                    clickedButton->isActive = false;
                    lastButton->isActive = false;
                    clickedButton->setStyleSheet("background-color: black");
                    lastButton->setStyleSheet("background-color: black");
                }
                else if ((lastButton->index % 9) == (clickedButton->index % 9))
                {
                    bool check = true;
                    if(std::abs(lastButton->index / 9 - clickedButton->index / 9) != 1)
                    {
                        int minimum = std::min(lastButton->index, clickedButton->index);
                        int maximum = std::max(lastButton->index, clickedButton->index);
                        for(int i = minimum+9; i <= maximum-9; i+=9)
                        {
                            if(buttons[i]->isActive)
                            {
                                check = false;
                            }
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
                    int minimum = std::min(lastButton->index, clickedButton->index);
                    int maximum = std::max(lastButton->index, clickedButton->index);
                    bool check = true;
                    for(int i = minimum+1; i <= maximum-1; i++)
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
            }
        }
    }
    preLastButton = lastButton;
    lastButton = clickedButton;
    checkForDeletableButtons();
}

void Mathespiel::checkForDeletableButtons() {
    int checkStart = 0;
    int checksum = 0;
    while((checkStart+8) < (int)buttons.size())
    {
        for(int i = checkStart; i < (checkStart+9); i++)
        {
            if(!buttons[i]->isActive) checksum++;
        }
        if(checksum == 9)
        {
            for(auto i: buttons)
            {
                i->hide();
            }
            buttons.erase(buttons.begin()+checkStart, buttons.begin()+checkStart+9);
            QGridLayout *newGrid = new QGridLayout();
            row = 0, column = 0;
            for(int i = 0; i < (int)buttons.size(); i++)
            {

                newGrid->addWidget(buttons[i], row, column++);
                if((column % 9) == 0) {
                    column = 0;
                    row++;
                }
                buttons[i]->index = i;
                buttons[i]->setVisible(true);
            }
            newGrid->setSizeConstraint(QLayout::SetFixedSize);
            QWidget *newButtonsWidget = new QWidget();
            newButtonsWidget->setLayout(newGrid);
            mainLayout->removeWidget(buttonsWidget);
            buttonsWidget = newButtonsWidget;
            mainLayout->addWidget(newButtonsWidget);
            mainLayout->setSizeConstraint(QLayout::SetFixedSize);
            gridLayout = newGrid;
        }
        checksum = 0;
        checkStart++;
    }
}

bool Mathespiel::checkForPairs() {
    bool pairsLeft = false;
    for(int i = 0; i < (int)(buttons.size()-1); i++)
    {
        if(buttons[i]->isActive && buttons[i+1]->isActive)
        {
            if((buttons[i]->text().toInt() == buttons[i+1]->text().toInt()) || (buttons[i]->text().toInt() + buttons[i+1]->text().toInt() == 10))
            {
                pairsLeft = true;
            }
        }
    }
    for(int i = 0; i < ((int)buttons.size()-9); i++)
    {
        int y = i;
        while((y < (int)buttons.size() - 9) && buttons[y]->isActive)
        {
            y += 9;
        }
        bool test = true;
        for(int j = i; j <= y; j+=9)
        {
            if(buttons[i]->isActive) test = false;
        }
        if(buttons[i]->isActive && buttons[y]->isActive && test)
        {
            if((buttons[i]->text().toInt() == buttons[y]->text().toInt()) || ((buttons[i]->text().toInt() + buttons[y]->text().toInt()) == 10))
            {
                pairsLeft = true;
            }
        }
    }
    return pairsLeft;
}
