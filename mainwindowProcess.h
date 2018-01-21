#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QProcess;

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
    void on_pushButtonOpen_clicked();
    void on_toolButtonAccess_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonQuit_clicked();
    //
    void sendMessage();


private:
    Ui::MainWindow *ui;
    QProcess *mProcess;
};

#endif // MAINWINDOW_H
