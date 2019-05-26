#ifndef SETWIDGET_H
#define SETWIDGET_H

#include <QWidget>

namespace Ui {
class SetWidget;
}

class SetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SetWidget(QWidget *parent = nullptr);
    ~SetWidget();

signals:
    void exitSignal();

private slots:


    void on_ButtonExit_clicked();

private:
    Ui::SetWidget *ui;
};

#endif // SETWIDGET_H
