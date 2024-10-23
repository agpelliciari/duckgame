#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(menuHandler handler): ui(new Ui::MainWindow), handler(handler) {
    ui->setupUi(this);
    connect(ui->buttonCreate, &QPushButton::clicked, this, &MainWindow::onClickCreateLobby);
    connect(ui->buttonJoin, &QPushButton::clicked, this, &MainWindow::onClickJoinLobby);
    connect(ui->buttonQuit, &QPushButton::clicked, this, &MainWindow::onClickQuit);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onClickCreateLobby() {
    if (handler.onClickCreateLobby)
        handler.onClickCreateLobby(1);
}

void MainWindow::onClickJoinLobby() {
    if (handler.onClickJoinLobby)
        handler.onClickJoinLobby(1, 1);
}

void MainWindow::onClickQuit() {
    this->close();
}