#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QDebug"
#include"QString"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("HJT212 CRC");
    this->setFixedWidth(800);
    this->setFixedHeight(480);
}

MainWindow::~MainWindow()
{
    delete ui;
}

unsigned int MainWindow::mainwindow_crc16_212(char* buf, int len)
{
    unsigned int r = 0;
    unsigned char hi = 0;
    char flag = 0;
    int i, j;

    r = 0xffff;
    for(j=0; j < len; j++) {
        hi = r >> 8;
        hi ^= buf[j];
        r = hi;

       for(i=0;i<8;i++)
       {
          flag = r & 0x0001;
          r = r >> 1;
          if(flag == 1) r ^= 0xa001;
       }
    }
    return r;
}

QString MainWindow::mainwindow_package(QString qstr)
{
    int len = 0;
    unsigned int CRC = 0;
    unsigned int size = 0;
    char str[20] = {0};
    char packet[102400] = {0};
    char * packet_p = NULL;
    QByteArray qbarray;
    QString ret_qstr;

    qbarray = qstr.toLatin1();
    packet_p = qbarray.data();
    len = qbarray.size();
    memcpy(&packet[6], packet_p, len);
    CRC = this->mainwindow_crc16_212(&packet[6], len);
    size = DCB(len);
    memset(str, 0, sizeof(str));
    sprintf(str, "##%.4x",size);
    memcpy(packet, str, 6);
    memset(str, 0, sizeof(str));
    sprintf(str,"%.4X\r\n",CRC);
    memcpy(&packet[len+6], str, 6);
    ret_qstr = QString(QLatin1String(packet));
    qDebug() << "ret_qstr:" + ret_qstr;
    return ret_qstr;
}


void MainWindow::on_pushButton_clicked()
{
    qDebug() << "********** on_pushButton_clicked **********";
    QTextEdit *tedit1 = this->ui->textEdit1;
    QTextEdit *tedit2 = this->ui->textEdit2;
    QString input_str;
    QString output_str;

    input_str = tedit1->toPlainText();
    qDebug() << input_str;
    output_str = this->mainwindow_package(input_str);
    tedit2->setText(output_str);
}
