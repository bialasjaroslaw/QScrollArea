#include "dialog.h"
#include "ui_dialog.h"

#include <QScrollBar>
#include <QComboBox>
#include <QtGlobal>
#include <QTimer>

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

QSize Dialog::calculateSizeHint()
{
    int adjustedWidth = width();
    int adjustedHeight = 0;
    QLayout* currentLayout = layout();
    for(QObject* obj : this->children())
    {
        QWidget* w = qobject_cast<QWidget*>(obj);
        if(w == nullptr)
            continue;
        QSize hint = w->sizeHint();
        adjustedWidth = std::max(adjustedWidth, hint.width());
        adjustedHeight += hint.height() + currentLayout->spacing();
    }
    adjustedHeight += (ui->scrollAreaWidgetContents->sizeHint().height() + currentLayout->spacing());
    return QSize(adjustedWidth, adjustedHeight);
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
    QTimer::singleShot(1, this, [this](){
       this->resize(calculateSizeHint());
    });
}
