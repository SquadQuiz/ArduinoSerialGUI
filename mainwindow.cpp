
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QString>
#include <QMessageBox>
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
    // Initialize serial constructor.
    serial.setPortName(ui->comboBox->currentText());
    serial.setBaudRate(serial.Baud9600);
    serial.setDataBits(serial.Data8);
    serial.setStopBits(serial.OneStop);
    serial.setFlowControl(serial.NoFlowControl);
    connect(&serial, SIGNAL(readyRead()), this, SLOT(readData()));

    if(serial.open(QIODevice::ReadWrite))
    {
        ui->receivedTextBox->clear();
        ui->receivedTextBox->append("Open COM Port Success!\n");
    }
    else
    {
        ui->receivedTextBox->append("Unable to Open COM Port\n");
    }
}

void MainWindow::on_closeBtn_clicked()
{
    serial.close();
    ui->receivedTextBox->insertPlainText("Closed COM Port\n");
}

void MainWindow::on_sendBtn_clicked()
{
    if(!serial.isOpen())
    {
        ui->receivedTextBox->insertPlainText("ERROR: COM Port Non-Connect\n");
    }
    else
    {
        serial.write(ui->lineEdit->text().toUtf8());
        ui->receivedTextBox->insertPlainText("Send :" + ui->lineEdit->text() + "\n");
    }
}

void MainWindow::readData()
{
    QByteArray data = serial.readAll();
    ui->receivedTextBox->insertPlainText("Received: " + QString(data));
}

void MainWindow::on_ledOnBtn_clicked()
{
    if(!serial.isWritable())
    {
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText("Please Connect First");
        msgBox->setWindowTitle("Warning");
        msgBox->exec();
    }
    else
    {
        serial.write("H");
        ui->receivedTextBox->insertPlainText("Button: " + QString("Turn On") + "\n");
    }
}

void MainWindow::on_ledOffBtn_clicked()
{
    if(!serial.isWritable())
    {
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText("Please Connect First");
        msgBox->setWindowTitle("Warning");
        msgBox->exec();
    }
    else
    {
        serial.write("L");
        ui->receivedTextBox->insertPlainText("Button: " + QString("Turn Off") + "\n");
    }
}


void MainWindow::on_clearTextSend_clicked()
{
    ui->lineEdit->clear();
}


void MainWindow::on_clearTextBox_clicked()
{
    ui->receivedTextBox->clear();
}

