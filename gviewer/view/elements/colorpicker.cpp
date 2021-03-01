#include "colorpicker.h"
#include "ui_colorpicker.h"

#include <QColorDialog>
#include <QPixmap>

namespace gviewer {

ColorPicker::ColorPicker(QWidget *parent) : ColorPicker("", parent) {}

ColorPicker::ColorPicker(const QString &title, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorPicker)
{
    ui->setupUi(this);
    setTitle(title);
    setColor(Qt::white);

    connect(ui->colorButton, &QToolButton::clicked, this, &ColorPicker::chooseColor);
}

ColorPicker::~ColorPicker()
{
    delete ui;
}

void ColorPicker::setTitle(const QString &title)
{
    ui->title->setText(title);
}

void ColorPicker::setColor(const QColor &color)
{
    if(color.isValid()) {
        QPixmap px(ui->colorButton->size() - QSize(10,10));
        px.fill(color);
        ui->colorButton->setIcon(px);
        ui->colorButton->setIconSize(px.size());

        emit colorChanged(color);
    }
}

void ColorPicker::chooseColor()
{
    setColor(QColorDialog::getColor());
}

}
