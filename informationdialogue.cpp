#include "informationdialogue.h"
#include "ui_informationdialogue.h"
#include "mainwindow.h"

using namespace std;

QString pName;
QString cName;
QString bankRoll;

InformationDialogue::InformationDialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationDialogue)
{
    ui->setupUi(this);
}

InformationDialogue::~InformationDialogue()
{
    delete ui;
}

QString InformationDialogue::getPlayerName()
{
    return pName;
}

QString InformationDialogue::getComputerName()
{
    return cName;
}

string InformationDialogue::getBankRoll()
{
    string playerBalance = bankRoll.toUtf8().constData();
    return playerBalance;
}

void InformationDialogue::on_pbContinue_clicked()
{
    pName = ui->lePlayerName->text();
    cName = ui->leComputerName->text();
    bankRoll = ui->leBankRoll->text();
    this->close();
    setModal(false);
    MainWindow *mMainWindow = new MainWindow;
    mMainWindow->show();
}
