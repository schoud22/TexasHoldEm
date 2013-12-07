#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pbQuitGame_clicked();

    void on_pbNewGame_clicked();

    void on_pbCheck_clicked();

    void on_pbCall_clicked();

    void on_pbFold_clicked();

    void on_pbRaise_clicked();

    void initializeGame();

    void settingUpPlayerCards();

    void showAICards();

    QString getTableCardImage(game gameboard, int cardIndex);

    void newRound(player*, bool);

    QString getPlayerCardImage(player gamePlayer, int cardIndex);

    void settingUpTableCards();

    void AImoves();

    void setPlayerBalance();

    void setComputerBalance();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
