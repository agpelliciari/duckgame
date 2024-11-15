#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>

#include "loader.h"
#include "interface/interface.h"
#include "playground/playground.h"

#undef emit
#include "../serial/map_serializer.h"
#include "../serial/map_deserializer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class EditorWindow;
}
QT_END_NAMESPACE

class EditorWindow : public QMainWindow {
    Q_OBJECT

private:
    Ui::EditorWindow *ui;

    Loader loader;
    Interface *interface;
    Playground *playground;

    MapObjectType editorIsCurrentlySetting = MapObjectType::Background;

    size_t selectedBackgroundIndex = 0;
    size_t selectedBlockIndex = 0;
    size_t selectedSpawnPlayerIndex = 0;
    size_t selectedSpawnWeaponIndex = 0;
    size_t selectedBoxIndex = 0;
    size_t selectedDecorationIndex = 0;

public:
    EditorWindow(QWidget *parent = nullptr);

    ~EditorWindow();

private:
    void wheelEvent(QWheelEvent *event) override;

    void selectEditorMode(MapObjectType mode);

    void selectBackgroundTexture(size_t index);

    void selectBlockTexture(size_t index);

    void selectSpawnPlayerTexture(size_t index);

    void selectSpawnWeaponTexture(size_t index);

    void selectBoxTexture(size_t index);

    void selectDecorationTexture(size_t index);

    void exportToFileSystem();

    //void importFromFileSystem();
};

#endif
