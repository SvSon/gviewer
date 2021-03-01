#pragma once

#include "gattributes.h"
#include "gedgeproperties.h"
#include "viewproperties.h"

#include <QString>

namespace gviewer {

/// Ребро графа
struct GEdge
{
    /// Идентификатор ребра
    QString id;
    /// Свойста ребра
    GEdgeProperties properties;
    /// Дополнительные аттрибуты ребра
    GAttributes attibutes {};

    /// Свойств отображения ребра
    ViewProperties viewProperties;
};

}
