#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSocketNotifier;
class QBuffer;

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
    void on_pushButtonClear_clicked();
    void on_pushButtonQuit_clicked();
    //
    void sendMessage();
    void receiveMessage();

private:
    QSocketNotifier *sig;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
