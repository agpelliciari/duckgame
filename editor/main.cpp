#include <iostream>
#include <QApplication>

#include "editorWindow.h"

constexpr int ERROR_CODE = 1;

int main(int argc, char* argv[]) {
    try {
        QApplication application(argc, argv);
        QPixmap cursorPixmap("./res/ui/default.png");
        QApplication::setOverrideCursor(QCursor(cursorPixmap));

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

        EditorWindow editorWindow;
        editorWindow.show();
        return application.exec();
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return ERROR_CODE;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return ERROR_CODE;
    }
}
