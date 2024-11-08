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

    std::vector<BlockTexture> blocks;
    size_t selectedBlockIndex = 0;

    std::vector<BlockTexture> backgrounds;
    size_t selectedBackgroundIndex = 0;

public:
    EditorWindow(QWidget *parent = nullptr);

    ~EditorWindow();

private:
    void wheelEvent(QWheelEvent *event) override;

    void selectedBackgroundTexture(size_t index);

    void selectedBlockTexture(size_t index);

    void exportToFileSystem();

    std::vector<std::string> blockTextureNames();

    std::vector<std::string> backgroundTextureNames();
};

#endif
