#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream> // TODO remove

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->buttonCreate, &QPushButton::clicked, this, &MainWindow::onClickCreateLobby);
    connect(ui->buttonJoin, &QPushButton::clicked, this, &MainWindow::onClickJoinLobby);
    connect(ui->buttonQuit, &QPushButton::clicked, this, &MainWindow::onClickQuit);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onClickCreateLobby() {
    std::cout << "onClickCreate\n"; // TODO remove
}

void MainWindow::onClickJoinLobby() {
    std::cout << "onClickJoin\n"; // TODO remove
}

void MainWindow::onClickQuit() {
    this->close();
}