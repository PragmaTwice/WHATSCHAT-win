#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(user* _userPtr, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWidget),
    userPtr(_userPtr)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);
}

MainWidget::~MainWidget()
{
    delete ui;
}
