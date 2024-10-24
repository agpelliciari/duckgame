#include "client.h"

Client::Client(int argc, char* argv[]): argc(argc), argv(argv) {
    setHostnameAndPort("127.0.0.1", "2048");
}

int Client::exec() {
    GameLoop gameLoop(hostname.c_str(), port.c_str());
    menuHandler menuHandler = {
            [&gameLoop](uint8_t playercount) { gameLoop.startCreateLobby(playercount); },
            [&gameLoop](uint8_t playercount, unsigned int idlobby) {
                gameLoop.startJoinLobby(playercount, idlobby);
            }};

    QApplication application(argc, argv);
    //-------
    QPalette darkTheme;
    darkTheme.setColor(QPalette::Window, QColor(53, 53, 53));
    darkTheme.setColor(QPalette::WindowText, Qt::white);
    darkTheme.setColor(QPalette::Base, QColor(25, 25, 25));
    darkTheme.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkTheme.setColor(QPalette::ToolTipBase, Qt::white);
    darkTheme.setColor(QPalette::ToolTipText, Qt::white);
    darkTheme.setColor(QPalette::Text, Qt::white);
    darkTheme.setColor(QPalette::Button, QColor(53, 53, 53));
    darkTheme.setColor(QPalette::ButtonText, Qt::white);
    darkTheme.setColor(QPalette::BrightText, Qt::red);
    darkTheme.setColor(QPalette::Link, QColor(42, 130, 218));
    darkTheme.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkTheme.setColor(QPalette::HighlightedText, Qt::black);
    application.setPalette(darkTheme);
    //------
    MainWindow window(menuHandler);
    window.show();
    return application.exec();
}

Client::~Client() {}

void Client::setHostnameAndPort(const std::string& newHostname, const std::string& newPort) {
    hostname = newHostname;
    port = newPort;
}
