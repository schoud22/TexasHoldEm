#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "carddeck.h"
#include "player.h"
#include "card.h"
#include "game.h"
#include "informationdialogue.h"
#include "mainmenu.h"
#include <QDir>
#include <QDebug>

using namespace std;

game gameBoard;
player human;
player AI;
QString playerName;
int level;
int betValue = 10;
bool playerTurn = false;
string turnOption;
QTextCursor AIcursor;
QTextCursor PlayerCursor;
QString AICard1;
QString AICard2;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeGame();
}

void MainWindow::initializeGame(){
    /*
    qDebug() << QCoreApplication::applicationDirPath();
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Sahil/QTWorkspace/CS340Project/images/Poker Soundtrack trim.mp3"));
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));
    player->setVolume(50);
    player->play();
    */

    level = 0;
    ui->teAIMoves->clear();
    ui->tePlayerMoves->clear();
    AIcursor = ui->teAIMoves->textCursor();
    PlayerCursor = ui->tePlayerMoves->textCursor();
    //Creating the Player and AI, along with the gameboard
    human = player(true);
    AI = player (false);

    //Start the Game
    gameBoard = game(&human, &AI);
    gameBoard.setUpBlinds(&human, &AI);
    AICard1 = getPlayerCardImage(AI, 0);
    AICard2 = getPlayerCardImage(AI, 1);

    //Grabbing the name of the user and computer along with the balance
    InformationDialogue newDialog;
    QString playerName = newDialog.getPlayerName();
    QString computerName = newDialog.getComputerName();
    QString AIBalance = QString::number(AI.getChips());
    QString PlayerBalance = QString::number(human.getChips());

    //Setting up the display board
    ui->lePlayerName->setText(playerName);
    ui->leAIName->setText(computerName);
    ui->leAIBalance->setText(AIBalance);
    ui->lePlayerBalance->setText(PlayerBalance);

    settingUpPlayerCards();
    ui->lePotBalance->setText(QString::number(gameBoard.getPot()));

    setPlayerBalance();
    setComputerBalance();
    //playerTurn = false;
    AImoves();
}

void MainWindow::settingUpTableCards(){
    //Set up the Table cards
    if(level == 0)
    {
        ui->gvTableCard1->setStyleSheet(getTableCardImage(gameBoard, 0));
        ui->gvTableCard2->setStyleSheet(getTableCardImage(gameBoard, 1));
        ui->gvTableCard3->setStyleSheet(getTableCardImage(gameBoard, 2));
        ui->gvTableCard4->setStyleSheet(getTableCardImage(gameBoard, 3));
        ui->gvTableCard5->setStyleSheet(getTableCardImage(gameBoard, 4));
        level++;

    }
    else if(level == 1){
        gameBoard.flop();
        ui->gvTableCard1->setStyleSheet(getTableCardImage(gameBoard, 0));
        ui->gvTableCard2->setStyleSheet(getTableCardImage(gameBoard, 1));
        ui->gvTableCard3->setStyleSheet(getTableCardImage(gameBoard, 2));
        level++;
    }
    else if(level == 2){
        gameBoard.getNextCard();
        ui->gvTableCard4->setStyleSheet(getTableCardImage(gameBoard, 3));
        level++;
    }
    else if(level == 3){
        gameBoard.getNextCard();
        ui->gvTableCard5->setStyleSheet(getTableCardImage(gameBoard, 4));
        level++;
    }
    else
    {
        gameBoard.giveCards(&human, &AI);
        long double humanVal = gameBoard.winningHand(human.getHand());
        long double AIVal = gameBoard.winningHand(AI.getHand());
        cout << "human val   " << humanVal << endl;
        cout << "AI val   " << AIVal << endl;
        if(humanVal == AIVal){
           showAICards();
           QMessageBox::information(this, "Draw", "IT WAS A DRAW!", QMessageBox::Ok);
           newRound(NULL, true);
        }
        else if(humanVal > AIVal){
            showAICards();
            QMessageBox::information(this, "WINNER!", "YOU WIN!", QMessageBox::Ok);
            newRound(&human, false);            
        }
        else{
            showAICards();
            QMessageBox::information(this, "LOSER", "YOU LOSE!", QMessageBox::Ok);
            newRound(&AI, false);            
        }
    }
}

void MainWindow::showAICards(){
    //Show AI Cards
    ui->gvAICard1->setStyleSheet(AICard1);
    ui->gvAICard2->setStyleSheet(AICard2);
}

void MainWindow::settingUpPlayerCards()
{
    //Set up player cards
    ui->gvPlayerCard1->setStyleSheet(getPlayerCardImage(human, 0));
    ui->gvPlayerCard2->setStyleSheet(getPlayerCardImage(human, 1));   
}

QString MainWindow::getTableCardImage(game gameboard, int cardIndex){
    string name = gameboard.tableCards[cardIndex].getCardName();
    QString qname = QString::fromUtf8(name.c_str());
    QString path;
    if(qname.isEmpty() || qname.isNull()){
        path = "background-image: url(:/images/images/b2fv.gif);";        
    }
    else{
        path = "background-image: url(:/images/images/" + qname + ".gif);";
    }
    return path;
}

QString MainWindow::getPlayerCardImage(player gamePlayer, int cardIndex){
    card *playerHand = gamePlayer.getHand();
    string playerCard = playerHand[cardIndex].getCardName();
    cout<<playerCard<<endl;
    QString qname = QString::fromUtf8(playerCard.c_str());
    QString path;
    if(qname.isEmpty() || qname.isNull()){
        path = "background-image: url(:/images/images/b2fv.gif);";
    }
    else{
        path = "background-image: url(:/images/images/" + qname + ".gif);";
    }
    return path;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbQuitGame_clicked()
{
    this->close();
}

void MainWindow::on_pbNewGame_clicked()
{
   QMessageBox::StandardButton reply;
   reply = QMessageBox::question(this, "Poker", "Are you sure you want to start a New Game?", QMessageBox::Yes|QMessageBox::No);
   if (reply == QMessageBox::Yes) {
       this->close();
       MainMenu newGame;
       newGame.setModal(true);
       newGame.exec();
   } else {
       //do Nothing
   }
}

void MainWindow::on_pbCheck_clicked()
{
    PlayerCursor.insertText("Player checks          ");
    PlayerCursor.movePosition(QTextCursor::Down);
    turnOption = "check";
    playerTurn = false;
    if(human.bigBlind == false){
        PlayerCursor.insertText("AI's turn...           ");
        PlayerCursor.movePosition(QTextCursor::Down);
        AImoves();
    }
    else{
        PlayerCursor.insertText("AI's turn...           ");
        PlayerCursor.movePosition(QTextCursor::Down);
        betValue = 0;
        settingUpTableCards();
    }
}

void MainWindow::on_pbCall_clicked()
{
    PlayerCursor.insertText("Player Calls     ");
    PlayerCursor.movePosition(QTextCursor::Down);
    if(human.bigBlind == false){
        playerTurn = false;
        turnOption = "call";
        cout << level << endl;
//        if(level == 0){
//           //betValue = gameBoard.getCallValue();
//            betValue = 10;
//        }
        betValue = 10;
        human.subtractChips(betValue);
        gameBoard.addToPot(betValue);
        ui->lePotBalance->setText(QString::number(gameBoard.getPot()));
        setPlayerBalance();
        ui->leAIBetValue->clear();
        betValue = 0;
        PlayerCursor.insertText("AI's turn...     ");
        PlayerCursor.movePosition(QTextCursor::Down);
        AImoves();
    }
}

void MainWindow::on_pbFold_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Poker", "Are you sure you want to fold?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        newRound(&AI, false);
    }
    else {
        //Do Nothing
    }
}

void MainWindow::newRound(player *roundWinner, bool draw){
    level = 0;
    ui->teAIMoves->clear();
    ui->tePlayerMoves->clear();
    ui->gvAICard1->setStyleSheet("background-image: url(:/images/images/b2fv.gif);");
    ui->gvAICard2->setStyleSheet("background-image: url(:/images/images/b2fv.gif);");
    gameBoard.fold(&human, !human.bigBlind);
    human.clearHand();
    AI.clearHand();
    if(draw){
        int drawPot = gameBoard.getPot()/2;
        AI.addToChips(drawPot);
        human.addToChips(drawPot);
    }
    else{
        roundWinner->addToChips(gameBoard.getPot());
    }
    gameBoard.clearTableCards();
    gameBoard.clearPot();
    settingUpTableCards();
    settingUpPlayerCards();
    ui->lePotBalance->setText(QString::number(gameBoard.getPot()));
    gameBoard.deal(&human, &AI);
    AICard1 = getPlayerCardImage(AI, 0);
    AICard2 = getPlayerCardImage(AI, 1);
    gameBoard.setUpBlinds(&human, &AI);
    QString value =  QString::number(gameBoard.getCallValue());
    ui->leAIBetValue->setText(value);
    settingUpPlayerCards();
    ui->lePotBalance->setText(QString::number(gameBoard.getPot()));
    setComputerBalance();
    setPlayerBalance();
}

void MainWindow::setPlayerBalance(){
    QString PlayerBalance = QString::number(human.getChips());
    ui->lePlayerBalance->setText(PlayerBalance);
}

void MainWindow::setComputerBalance(){
    QString AIBalance = QString::number(AI.getChips());
    ui->leAIBalance->setText(AIBalance);
}

void MainWindow::on_pbRaise_clicked()
{
    if(ui->leRaise->text().isEmpty()){
        QMessageBox::information(this, "ERROR!", "Please Enter a Raise amount!", QMessageBox::Ok);
    }
    else{
        PlayerCursor.insertText("Player raised          ");
        PlayerCursor.movePosition(QTextCursor::Down);
        playerTurn = false;
        turnOption = "raise";
        QString str = "";
        str = ui->leRaise->text();
        string raiseValue = str.toUtf8().constData();
        int raiseValueNumber = atoi(raiseValue.c_str());
        betValue =  betValue + raiseValueNumber;
        if(raiseValueNumber > human.getChips()){
            gameBoard.addToPot(human.getChips());
        }
        else{
            gameBoard.addToPot(raiseValueNumber);
        }
        human.subtractChips(raiseValueNumber);
        ui->leRaise->clear();
        setPlayerBalance();
        setComputerBalance();
        PlayerCursor.insertText("AI's turn...           ");
        PlayerCursor.movePosition(QTextCursor::Down);
        AImoves();
    }
}

void MainWindow::AImoves(){
    if(playerTurn == false){
        if(turnOption == "raise" || level == 0){
            AIcursor.insertText("AI calls your raise                ");
            AIcursor.movePosition(QTextCursor::Down);
            playerTurn = true;
            AI.subtractChips(betValue);
            gameBoard.addToPot(betValue);
            ui->lePotBalance->setText(QString::number(gameBoard.getPot()));
            QString AIBalance = QString::number(AI.getChips());
            ui->leAIBalance->setText(AIBalance);
            betValue = 0;
            turnOption = "null";
            settingUpTableCards();
            AIcursor.insertText("Waiting for player...                   ");
            AIcursor.movePosition(QTextCursor::Down);
            PlayerCursor.insertText("Your turn...     ");
            PlayerCursor.movePosition(QTextCursor::Down);
        }
        if(turnOption == "call"){
            AIcursor.insertText("AI calls raise             ");
            AIcursor.movePosition(QTextCursor::Down);
            turnOption = "null";
            settingUpTableCards();            
            AIcursor.insertText("Waiting for player...                  ");
            AIcursor.movePosition(QTextCursor::Down);
            PlayerCursor.insertText("Your turn...");
            PlayerCursor.movePosition(QTextCursor::Down);
        }
        if(turnOption == "check" && human.bigBlind == false){
            AIcursor.insertText("AI checked             ");
            AIcursor.movePosition(QTextCursor::Down);
            turnOption = "null";
            settingUpTableCards();            
            AIcursor.insertText("Waiting for player...                   ");
            AIcursor.movePosition(QTextCursor::Down);
            PlayerCursor.insertText("Your turn...           ");
            PlayerCursor.movePosition(QTextCursor::Down);
        }
        if(turnOption == "check"){
            AIcursor.insertText("AI checked             ");
            AIcursor.movePosition(QTextCursor::Down);
            turnOption = "null";
            settingUpTableCards();            
            AIcursor.insertText("Waiting for player...                   ");
            AIcursor.movePosition(QTextCursor::Down);
            PlayerCursor.insertText("Your turn...           ");
            PlayerCursor.movePosition(QTextCursor::Down);
        }
        playerTurn = true;
    }
}
