#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>

#include "interface/interface.h"
#include "playground/playground.h"

struct BlockTexture {
    std::string name;
    std::string source;
};

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

    std::vector<BlockTexture> textures;
    size_t selectedTextureIndex = 0;

public:
    EditorWindow(QWidget *parent = nullptr);

    ~EditorWindow();

private:
    void wheelEvent(QWheelEvent *event) override;

    void selectedBlockTexture(size_t index);

    void exportToFileSystem();

    std::vector<std::string> blockTextureNames();
};

#endif
