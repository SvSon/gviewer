#pragma once

#include "../gviewgraphscene.h"

#include <QWidget>
#include <QToolBar>

namespace gviewer {

/// Инструменты для настройки режима работы на сцене
class SceneModeToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit SceneModeToolBar(GViewGraphScene* gscene, QWidget* parent = nullptr);

private:
    /// Инициализировать действия
    void initActions();

private:
    /// Текущая сцена для настройки
    GViewGraphScene* scene;
};

}
