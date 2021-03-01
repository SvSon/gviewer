#pragma once

#include <QDockWidget>

namespace gviewer {
class CommonSceneTools : public QDockWidget
{
    Q_OBJECT
public:
    explicit CommonSceneTools(QWidget *parent = nullptr);
};

}
