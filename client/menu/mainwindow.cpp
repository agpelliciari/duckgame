#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(MenuHandler& handler): ui(new Ui::MainWindow), handler(handler) {
    ui->setupUi(this);
    connect(ui->buttonCreate, &QPushButton::clicked, this, &MainWindow::onClickCreateLobby);
    connect(ui->buttonJoin, &QPushButton::clicked, this, &MainWindow::onClickJoinLobby);
    connect(ui->buttonQuit, &QPushButton::clicked, this, &MainWindow::onClickQuit);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onClickCreateLobby() { handler.createLobby(2); }

void MainWindow::onClickJoinLobby() { handler.joinLobby(2, 1); }

void MainWindow::onClickQuit() { this->close(); }
