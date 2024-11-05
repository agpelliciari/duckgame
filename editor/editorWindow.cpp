#include "editorWindow.h"
#include "./ui_editorWindow.h"

#include <iostream>

EditorWindow::EditorWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::EditorWindow),
    interface(new Interface(InterfaceHandler{
        .onBackgroundSelected = []() {},
        .onExport = [this]() { exportToFileSystem(); }
    }, this)),
    playground(new Playground(this))
{
    ui->setupUi(this);

    interface->setMaximumWidth(200);
    ui->horizontalLayout->addWidget(interface);
    ui->horizontalLayout->addWidget(playground, 1);
}

EditorWindow::~EditorWindow() {
    delete ui;
}

void EditorWindow::exportToFileSystem() {
    std::cout << __func__ << std::endl;
}
