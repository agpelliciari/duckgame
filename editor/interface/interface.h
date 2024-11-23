#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QStringList>
#include <QComboBox>
#include <QPushButton>
#include <QTimer>

#include "../types.h"

struct InterfaceHandler {
    std::function<void(MapObjectType)> onEditorModeDropdownChanged;
    std::function<void(size_t)> onSelectorDropdownIndexChanged;
    std::function<void()> onExport;
    std::function<void()> onImport;
};

namespace Ui {
class Interface;
}

class Interface : public QWidget {
    Q_OBJECT

public:

size_t selectedTexture = 0;

private:
    static constexpr const char* SAVE_ICON_SOURCE = "/ui/save.png";
    static constexpr const char* LOAD_ICON_SOURCE = "/ui/load.png";

    Ui::Interface* ui;
    const InterfaceHandler handler;

    QGraphicsRectItem* preview;
    QWidget* currentNotification = nullptr;

    const int textureSize = 16;

public:
    explicit Interface(const InterfaceHandler& handler, QWidget* parent = nullptr);

    void setEditorModeDropdownOptions(std::vector<std::string> editorModeNames);

    void setSelectorDropdownOptions(std::vector<std::string> names);

    void selectorDropdownIndexChanged(size_t index);

    void displayNoneOnPreview();

    void displayMapObjectOnPreview(Texture texture);

    void displayNotificationError(const std::string& label);

    void displayNotificationSuccess(const std::string& label);

    ~Interface();

private:
    void onClickExport();
    void onClickImport();

    void onEditorModeDropdownChangedInt(int index);
    void onEditorModeDropdownChanged(MapObjectType mode);

    void onSelectorDropdownIndexChanged(int index);

    void initializePreview();

    void setDropdownOptions(std::vector<std::string> options, QComboBox* dropdown);

    void setUpButton(QPushButton* button, const QString& iconPath, void (Interface::*method)());

    void displayNotification(const std::string& label);
};

#endif
