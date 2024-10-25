#ifndef CLIENT_H
#define CLIENT_H

#include <QApplication>
#include <QStyleFactory>
#include <string>

#include "menu/mainwindow.h"

#include "game_loop.h"

class Client {
private:
    int argc;     // cppcheck-suppress unusedStructMember
    char** argv;  // cppcheck-suppress unusedStructMember

    std::string hostname = "";
    std::string port = "";

    int execMenu(GameLoop& gameloop);
    int execGame(GameLoop& gameloop);

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
