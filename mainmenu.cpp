#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "informationdialogue.h"

MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_pbNewGame_clicked()
{
   this->close();
   InformationDialogue mDialogue;
   mDialogue.setModal(true);
   mDialogue.exec();
}

void MainMenu::on_pbQuit_clicked()
{
    this->close();
}
