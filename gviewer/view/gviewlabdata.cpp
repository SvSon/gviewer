#include "gviewlabdata.h"
#include "ui_gviewlabdata.h"

namespace gviewer {

GViewLabData::GViewLabData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GViewLabData)
{
    ui->setupUi(this);
}

GViewLabData::~GViewLabData()
{
    delete ui;
}

void GViewLabData::setGraph(const GGraph &value)
{
    graph = value;
}

}
