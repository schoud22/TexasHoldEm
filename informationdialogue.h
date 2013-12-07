#ifndef INFORMATIONDIALOGUE_H
#define INFORMATIONDIALOGUE_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <string>
using namespace std;

namespace Ui {
class InformationDialogue;
}

class InformationDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit InformationDialogue(QWidget *parent = 0);
    QString getPlayerName();
    QString getComputerName();
    string getBankRoll();
    ~InformationDialogue();

private slots:
    void on_pbContinue_clicked();    

private:
    Ui::InformationDialogue *ui;
};

#endif // INFORMATIONDIALOGUE_H
