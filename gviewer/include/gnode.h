#pragma once

#include "gnodeproperties.h"
#include "gattributes.h"
#include "viewproperties.h"

namespace gviewer {

/// Вершина графа
struct GNode
{
    /// Идентификатор вершины
    QString id;
    /// Свойста вершины
    GNodeProperties properties {};
    /// Дополнительные аттрибуты вершины
    GAttributes attributes {};

    /// Свойств отображения вершины
    ViewProperties viewProperties;
};

}
