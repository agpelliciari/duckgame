#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QStringList>
#include <QComboBox>

struct InterfaceHandler {
    std::function<void(size_t)> onBackgroundDropdownIndexChanged;
    std::function<void(size_t)> onBlockDropdownIndexChanged;
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

    void setBackgroundDropdownOptions(std::vector<std::string> backgroundNames);

    void setBlockDropdownOptions(std::vector<std::string> blockNames);

    void blockDropdownIndexChanged(size_t index);

    void displayOnPreview(QPixmap pixelMap);

    ~Interface();

private:
    void onClickExport();

    void onBackgroundDropdownIndexChanged(int index);

    void onBlockDropdownIndexChanged(int index);

    void initializePreview();

    void setDropdownOptions(std::vector<std::string> options, QComboBox* dropdown);
};

#endif
