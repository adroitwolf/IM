#ifndef ENTERWINDOW_H
#define ENTERWINDOW_H

#include <QWidget>

namespace Ui {
class EnterWindow;
}

class EnterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EnterWindow(QWidget *parent = nullptr);
    ~EnterWindow();

private:
    Ui::EnterWindow *ui;
};

#endif // ENTERWINDOW_H
