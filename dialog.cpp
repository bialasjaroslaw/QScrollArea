#include "dialog.h"
#include "ui_dialog.h"

#include <QScrollBar>
#include <QComboBox>
#include <QtGlobal>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    constexpr int itemsNumber = 12;
    ui->setupUi(this);
    for(int idx = 1 ; idx <= itemsNumber ; ++idx)
        ui->comboBox->addItem(QString("%1 item(s)").arg(idx));
    ui->comboBox->setCurrentIndex(-1);
    connect(ui->comboBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &Dialog::addItems);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::addItems(int index)
{
    auto addSomeItems = [this](int itemsNumber){
        while(itemsNumber-- >= 0)
        {
            auto* w =  new QComboBox(this);
            container.push_back(w);
            ui->scrollAreaWidgetContents->layout()->addWidget(w);
        }
    };

    for(auto* w : container)
        delete w;
    container.clear();
    addSomeItems(index);
    repaint();
}
