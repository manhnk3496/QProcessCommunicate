#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QSocketNotifier>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sig = new QSocketNotifier(fileno(stdin),QSocketNotifier::Read, this);
    connect(ui->pushButtonSend,SIGNAL(clicked()),this,SLOT(sendMessage()));
    connect(ui->lineEditChat,SIGNAL(returnPressed()),this,SLOT(sendMessage()));
    connect(sig,SIGNAL(activated(int)),this,SLOT(receiveMessage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//clear content
void MainWindow::on_pushButtonClear_clicked()
{
    ui->listWidgetContent->clear();
}

//close program
void MainWindow::on_pushButtonQuit_clicked()
{
    close();
}

/*.....................................................
 *
 ....................................................*/


//send message
void MainWindow::sendMessage()
{
    auto msg = ui->lineEditChat->text();
    std::cout << msg.toStdString() << std::endl;
    ui->lineEditChat->clear();
    ui->labelNotification->setText("Send message is success!");
}

//receive message
void MainWindow::receiveMessage()
{
//    std::string msg;
//    std::cin >> msg;
//    std::getline(std::cin, msg);
//    QString m = QString::fromStdString(msg);
//    std::fflush(stdin);

    QTextStream msg1(stdin);
    QString m = msg1.readLine();
    ui->listWidgetContent->addItem("ProcessA: " + m);
    ui->listWidgetContent->addItem("");
    ui->labelNotification->setText("New message!");
}
