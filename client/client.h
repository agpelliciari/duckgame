#ifndef CLIENT_H
#define CLIENT_H

#include "menu/mainwindow.h"
#include "game_loop.h"

#include <string>
#include <QApplication>
#include <QStyleFactory>

class Client {
private:
    int argc;
    char** argv;

    std::string hostname = "";
    std::string port = "";

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
