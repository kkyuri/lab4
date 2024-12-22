#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->submitButton, &QPushButton::clicked, this, [&]() {
        QString text = ui->lineEdit->text();
        QMessageBox::information(this, "Entered Text", "output: " + text);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
