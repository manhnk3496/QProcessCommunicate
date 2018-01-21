#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mProcess = new QProcess(this);
    connect(ui->pushButtonSend,SIGNAL(clicked()),this,SLOT(sendMessage()));
    connect(ui->lineEditChat,SIGNAL(returnPressed()),this,SLOT(sendMessage()));

    //get signal cout of process
    connect(mProcess,&QProcess::readyReadStandardOutput,[&](){
        ui->labelNotication->setText("New message!");
        auto msg = mProcess->readAllStandardOutput();
        ui->listWidgetContent->addItem("ProcessB: " + msg);
    });

    //get signal error of process
    connect(mProcess, &QProcess::readyReadStandardError, [&](){
        ui->labelNotication->setText("Error!");
        auto data = mProcess->readAllStandardError();
        ui->listWidgetContent->addItem("Error: \n" + data);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


//function is control process!
//compelete
void MainWindow::on_pushButtonOpen_clicked()
{
    if(!mProcess->isOpen()){
        ui->pushButtonOpen->setText("Close");
        auto program = ui->lineEditProgram->text();
        if(program.isEmpty()){
            program = "/home/hoangth9-server/Qt_Program/Process/CommunicateProcess"
                      "/build-QProcessB-Desktop_Qt_5_3_GCC_64bit-Debug/QProcessB";
        }
        mProcess->setProgram(program);
        mProcess->start();
        if(mProcess->isOpen()){
            ui->labelNotication->setText("Program is running!");
        }
        else{
            ui->labelNotication->setText("Error: " + mProcess->errorString());
        }
    }
    else{
        mProcess->close();
        if(mProcess->isOpen()){
            ui->labelNotication->setText("Cann't closs program!");
        }
        else{
            ui->labelNotication->setText("Program is close!");
            ui->pushButtonOpen->setText("Open");
        }
    }
}


//Function take path to program
//complete
void MainWindow::on_toolButtonAccess_clicked()
{
    auto filename = QFileDialog::getOpenFileName(this,"","/","");
    if(filename.isEmpty()){
        return;
    }
    ui->lineEditProgram->setText(filename);
    ui->labelNotication->setText("Take path is success!");
}


//Clear content
void MainWindow::on_pushButtonClear_clicked()
{
    ui->labelNotication->setText("Program is close");
}


//Close program
void MainWindow::on_pushButtonQuit_clicked()
{
    close();
}
/*.....................................................

 ....................................................*/


//Send message to process
void MainWindow::sendMessage()
{
    mProcess->write(ui->lineEditChat->text().toLatin1()+"\n");
    ui->labelNotication->setText("Send is success!");
    ui->lineEditChat->clear();
}
