#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QStringList>
#include <QComboBox>

#include "../types.h"

struct InterfaceHandler {
    std::function<void(MapObjectType)> onEditorModeDropdownChanged;
    std::function<void(size_t)> onSelectorDropdownIndexChanged;
    std::function<void()> onExport;
};

namespace Ui {
class Interface;
}

class Interface : public QWidget {
    Q_OBJECT

public:

size_t selectedTexture = 0;

private:
    Ui::Interface* ui;
    const InterfaceHandler handler;

    QGraphicsRectItem* preview;

    const int textureSize = 16;

public:
    explicit Interface(const InterfaceHandler& handler, QWidget* parent = nullptr);

    void setEditorModeDropdownOptions(std::vector<std::string> editorModeNames);

    void setSelectorDropdownOptions(std::vector<std::string> names);

    void selectorDropdownIndexChanged(size_t index);

    void displayNoneOnPreview();

    void displayMapObjectOnPreview(Texture texture);

    ~Interface();

private:
    void onClickExport();

    void onEditorModeDropdownChangedInt(int index);
    void onEditorModeDropdownChanged(MapObjectType mode);

    void onSelectorDropdownIndexChanged(int index);

    void initializePreview();

    void setDropdownOptions(std::vector<std::string> options, QComboBox* dropdown);
};

#endif
