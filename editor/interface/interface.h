#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QStringList>

struct InterfaceHandler {
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
    QGraphicsScene* preview;

    const InterfaceHandler handler;

    QGraphicsRectItem* block;

public:
    explicit Interface(const InterfaceHandler& handler, QWidget* parent = nullptr);

    void setBlockDropdownOptions(std::vector<std::string> blockNames);

    void blockDropdownIndexChanged(size_t index);

    void displayOnPreview(QBrush texture);

    ~Interface();

private:
    void initializePreview();

    void onBlockDropdownIndexChanged(int index);

    void onClickExport();
};

#endif
