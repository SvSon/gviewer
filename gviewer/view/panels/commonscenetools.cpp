#include "commonscenetools.h"

#include <QVBoxLayout>

namespace gviewer {

CommonSceneTools::CommonSceneTools(QWidget *parent) :
    QDockWidget(parent)
{
    setLayout(new QVBoxLayout(this));
    setAllowedAreas(Qt::LeftDockWidgetArea
                    | Qt::RightDockWidgetArea
                    | Qt::TopDockWidgetArea
                    | Qt::BottomDockWidgetArea);
}

}
