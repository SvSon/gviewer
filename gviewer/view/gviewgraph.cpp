#include "gviewgraph.h"
#include "ui_gviewgraph.h"

#include "scence/scenepropertiestoolbar.h"
#include "scence/scenemodetoolbar.h"
#include "panels/commonscenetools.h"

#include <QWheelEvent>
#include <QPushButton>
#include <QDebug>

namespace gviewer {

GViewGraph::GViewGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GViewGraph)
{
    ui->setupUi(this);

    view = new GViewGraphScene(this);
    ui->scene->addWidget(view);
}

GViewGraph::~GViewGraph()
{
    delete ui;
}

void GViewGraph::showEvent(QShowEvent *event)
{
    visibleChaned(true);
    QWidget::showEvent(event);
}

void GViewGraph::hideEvent(QHideEvent *event)
{
    visibleChaned(false);
    QWidget::hideEvent(event);
}

void GViewGraph::setGraph(const GGraph& value)
{
    graph = value;
    view->setGraph(graph);
}

GViewGraphScene *GViewGraph::getView() const
{
    return view;
}

void GViewGraph::setToolBarsFor(QMainWindow *window)
{
    if(!window) return;

    auto scenePropertiesToolBar = new ScenePropertiesToolBar(view, this);
    scenePropertiesToolBar->setAllowedAreas(Qt::ToolBarArea::LeftToolBarArea
                                            | Qt::ToolBarArea::RightToolBarArea
                                            | Qt::ToolBarArea::BottomToolBarArea);
    window->addToolBar(Qt::ToolBarArea::BottomToolBarArea, scenePropertiesToolBar);

    connect(this, &GViewGraph::visibleChaned, scenePropertiesToolBar, &ScenePropertiesToolBar::setVisible);
}

}
