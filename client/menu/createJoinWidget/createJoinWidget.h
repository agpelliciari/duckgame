#ifndef CREATEJOINWIDGET_H
#define CREATEJOINWIDGET_H

#include <QWidget>

struct CreateJoinHandler {
    std::function<void()> onClickCreateGame;
    std::function<void()> onClickJoinGame;
    std::function<void()> onClickQuit;
};

namespace Ui {
class CreateJoinWidget;
}

class CreateJoinWidget: public QWidget {
    Q_OBJECT

private:
    Ui::CreateJoinWidget* ui;         // cppcheck-suppress unusedStructMember
    const CreateJoinHandler handler;  // cppcheck-suppress unusedStructMember

public:
    explicit CreateJoinWidget(const CreateJoinHandler& handler, QWidget* parent = nullptr);

    ~CreateJoinWidget();

private:
    void onClickCreateGame();

    void onClickJoinGame();

    void onClickQuit();
};

#endif
