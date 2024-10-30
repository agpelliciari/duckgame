#ifndef SETHOSTNAMEPORTWIDGET_H
#define SETHOSTNAMEPORTWIDGET_H

#include <QWidget>
#include <string>

struct SetHostnamePortHandler {
    std::function<void(std::string, std::string)> onClickContinue;
    std::function<void()> onClickQuit;
};

namespace Ui {
class SetHostnamePortWidget;
}

class SetHostnamePortWidget: public QWidget {
    Q_OBJECT

private:
    Ui::SetHostnamePortWidget* ui;         // cppcheck-suppress unusedStructMember
    const SetHostnamePortHandler handler;  // cppcheck-suppress unusedStructMember

public:
    explicit SetHostnamePortWidget(const SetHostnamePortHandler& handler,
                                   QWidget* parent = nullptr);

    ~SetHostnamePortWidget();

private:
    void onClickContinue();

    void onClickQuit();
};

#endif
