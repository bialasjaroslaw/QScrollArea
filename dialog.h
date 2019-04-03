#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSize>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
private slots:
    void addItems(int index);
private:
    QList<QWidget*> container;
    QSize calculateSizeHint();
};

#endif // DIALOG_H
