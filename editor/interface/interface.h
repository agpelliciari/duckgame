#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>

struct InterfaceHandler {
    std::function<void()> onBackgroundSelected;
    std::function<void()> onExport;
};

namespace Ui {
class Interface;
}

class Interface : public QWidget {
    Q_OBJECT

private:
    Ui::Interface* ui;

    const InterfaceHandler handler;

public:
    explicit Interface(const InterfaceHandler& handler, QWidget* parent = nullptr);

    ~Interface();

private:
    void onClickExport();
};

#endif
