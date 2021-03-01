#include "gview.h"
#include "ui_gview.h"

#include <QFile>
#include <QUrl>
#include <QDebug>

namespace gviewer {

GView::GView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GView)
{
    ui->setupUi(this);

    Q_INIT_RESOURCE(resource_gviewer);

    QFile file(":/gviewer/styles/resource/css/style.css");
    if(file.open(QFile::ReadOnly)) setStyleSheet(file.readAll());
    file.close();

    viewGraph = new GViewGraph(this);
    ui->viewL->addWidget(viewGraph);

    viewGraph->setToolBarsFor(this);
}

GView::~GView()
{
    delete ui;
}

void GView::setGraph(const GGraph &value)
{
    graph = value;
    viewGraph->setGraph(graph);
}

GViewGraph *GView::getViewGraph() const
{
    return viewGraph;
}

}
