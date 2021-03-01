#include "scenemodetoolbar.h"

#include <QActionGroup>
#include <QKeySequence>

#include <functional>

namespace gviewer {

gviewer::SceneModeToolBar::SceneModeToolBar(gviewer::GViewGraphScene *gscene, QWidget *parent)
    : QToolBar(parent), scene(gscene)
{
    initActions();
}

void SceneModeToolBar::initActions()
{
    auto modeGroup = new QActionGroup(this);
    modeGroup->setExclusive(true);

    auto debug = addAction("debug");
    addAction(debug);
    connect(debug, &QAction::triggered, this, [this](bool checked){
        scene->printDebug();
    });

}

}
