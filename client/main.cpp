#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

#include "client/client.h"
//#include "common/core/liberror.h"
//#include "common/core/resolvererror.h"

#include "menu/mainwindow.h"

#include <iostream>
#include <QApplication>
#include <QStyleFactory>

constexpr int ERROR_CODE = 1;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "No se paso los parametros el <host> <servicio> de con quien conectar\n";
        return ERROR_CODE ;
    }


    try {

        // Inicializa el cliente.
        char* host = NULL;
        char* service = argv[1];
        if (argc > 2) {
            host = argv[1];
            service = argv[2];
        }

        Client client(host, service);



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
		MainWindow window;
		window.show();
		return application.exec();
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return ERROR_CODE;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return ERROR_CODE;
    }
}
