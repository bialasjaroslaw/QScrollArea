#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Dialog* dialog = new Dialog();
    connect(ui->pushButton, &QPushButton::clicked, dialog, &Dialog::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}
