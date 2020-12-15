#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QString>

QT_BEGIN_NAMESPACE
#define DCB(x) ((x/1000)*16*16*16 + ((x%1000)/100)*16*16+(((x%1000)%100)/10)*16+((x%1000)%100)%10)
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

public:
    QString mainwindow_package(QString qstr);
    unsigned int mainwindow_crc16_212(char* buf, int len);
};
#endif // MAINWINDOW_H
