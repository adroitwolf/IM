#include "enterwindow.h"
#include "ui_enterwindow.h"

EnterWindow::EnterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnterWindow)
{
    ui->setupUi(this);
}

EnterWindow::~EnterWindow()
{
    delete ui;
}
