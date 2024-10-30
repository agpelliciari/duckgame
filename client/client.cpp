#include "client.h"

#include "./simpleeventlistener.h"

Client::Client(int argc, char* argv[]): argc(argc), argv(argv) {
    setHostnameAndPort("127.0.0.1", "2048");
}

int Client::execMenu(GameLoop& gameLoop, GameContext& context) {
    MenuHandler menuHandler(gameLoop.initLobbyClient(context));

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
    Menu menu(menuHandler);
    menu.show();
    return application.exec();
}
int Client::exec() {
    GameContext context;
    GameLoop gameLoop(hostname.c_str(), port.c_str());
    if (execMenu(gameLoop, context) != 0) {
        return 1;
    }


    // if (execGame(gameLoop) != 0) {
    //     return 1;
    // }

    return execGame(gameLoop, context);
}


int Client::execGame(GameLoop& gameloop, const GameContext& context) {
    // Crear event queue iniciar action listener y exec del uiloop!
    SimpleEventListener listener;

    GameActionSender actionListener(gameloop.initGame(listener));
    actionListener.begin();

    if (context.second_player == NOT_DEFINED_FLAG) {
        // Solo un jugador
        std::cout << "Un solo jugador!!! " << context.first_player << std::endl;
    } else {
        std::cout << "Dos jugadores!!! " << context.first_player << " y " << context.second_player
                  << std::endl;
    }

    UILoop uiLoop(actionListener, listener);
    uiLoop.exec();

    return 0;
}

Client::~Client() {}

void Client::setHostnameAndPort(const std::string& newHostname, const std::string& newPort) {
    hostname = newHostname;
    port = newPort;
}
