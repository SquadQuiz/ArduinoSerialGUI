
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openBtn_clicked();

    void on_closeBtn_clicked();

    void on_sendBtn_clicked();

    void readData();

    void on_ledOnBtn_clicked();

    void on_ledOffBtn_clicked();

    void on_clearTextSend_clicked();

    void on_clearTextBox_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
