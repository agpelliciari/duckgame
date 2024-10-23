#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream> // TODO remove

MainWindow::MainWindow(Client& _client, QWidget *parent): QMainWindow(parent),client(_client), ui(new Ui::MainWindow) {
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
    
    LobbyCreateMode& mode = client.startCreateLobby(1);
    
    mode.startLobby();
}

void MainWindow::onClickJoinLobby() {
    std::cout << "onClickJoin\n"; // TODO remove
    //JoinLobbyMode& mode = 
    client.startJoinLobby(1, 1); // playercount , idlobby
    
}

void MainWindow::onClickQuit() {
    this->close();
}
