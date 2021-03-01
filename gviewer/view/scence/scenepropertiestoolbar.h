#pragma once

#include "../gviewgraphscene.h"

#include <QWidget>
#include <QToolBar>

namespace gviewer {

/// Иструменты для настройки отображения сцены
class ScenePropertiesToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit ScenePropertiesToolBar(GViewGraphScene* gscene, QWidget* parent = nullptr);

private:
    /// Инициализировать действия
    void initActions();

private:
    /// Текущая сцена для настройки
    GViewGraphScene* scene;
};

}
