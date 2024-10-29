#ifndef CLIENT_H
#define CLIENT_H

#include <QApplication>
#include <QStyleFactory>
#include <string>

#include "./gamecontext.h"
#include "client/core/game_loop.h"
#include "interfaz/loop_ui.h"
#include "menu/mainwindow.h"

class Client {
private:
    int argc;     // cppcheck-suppress unusedStructMember
    char** argv;  // cppcheck-suppress unusedStructMember

    std::string hostname = "";
    std::string port = "";

    int execMenu(GameLoop& gameloop, GameContext& context);
    int execGame(GameLoop& gameloop, const GameContext& context);

public:
    explicit Client(int argc, char* argv[]);

    int exec();


    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    Client(Client&&) = delete;
    Client& operator=(Client&&) = delete;

    ~Client();

private:
    void setHostnameAndPort(const std::string& newHostname, const std::string& newPort);
};

#endif
