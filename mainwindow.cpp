#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "threadbase.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /// ThreadBase
    /// ThreadBase 强转 MainWindow, ThreadBase 赋值 this：*p, threadBaseTest: *q
    ThreadBase<MainWindow> *t = new ThreadBase<MainWindow>(this, &MainWindow::threadBaseTest);
    t->start(0, 0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::threadBaseTest(void *p, void *q)
{
    return 0;
}
