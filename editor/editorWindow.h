#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>

#include "interface/interface.h"
#include "playground/playground.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class EditorWindow;
}
QT_END_NAMESPACE

class EditorWindow : public QMainWindow {
    Q_OBJECT

private:
    Ui::EditorWindow *ui;

    Interface *interface;
    Playground *playground;

public:
    EditorWindow(QWidget *parent = nullptr);

    ~EditorWindow();

private:
    void exportToFileSystem();
};

#endif
