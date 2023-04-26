
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QString>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

// global
QSerialPort serial;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->comboBox->addItem(info.portName());
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openBtn_clicked()
{
    serial.setPortName(ui->comboBox->currentText());
    serial.setBaudRate(serial.Baud9600);
    serial.setDataBits(serial.Data8);
    serial.setStopBits(serial.OneStop);
    serial.setFlowControl(serial.NoFlowControl);
    connect(&serial, SIGNAL(readyRead()), this, SLOT(readData()));
    if(serial.open(QIODevice::ReadWrite))
    {
        ui->textEdit->clear();
        ui->textEdit->append("Open port Success\n");
    }
    else
    {
        ui->textEdit->append("Unable to Open COMPORT");
    }
}

void MainWindow::on_closeBtn_clicked()
{
    serial.close();
}

void MainWindow::on_sendBtn_clicked()
{
    serial.write(ui->lineEdit->text().toUtf8());
}

void MainWindow::readData()
{
    QByteArray data = serial.readAll();
    ui->textEdit->insertPlainText(QString(data));
}
