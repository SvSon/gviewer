#pragma once

#include <QPointF>
#include <QRectF>
#include <QColor>

namespace gviewer {

/// Свойства для отображения текущего состояния узла/ребра
struct ViewProperties
{
    /// Текущее позиция курсора
    enum Hovering {
        /// Стандартный режим
        Hovering_None = 0,
        /// Наведение на входящую сущность (по отношению к текущей)
        Hovering_In,
        /// Наведение на исходящую сущность (по отношению к текущей)
        Hovering_Out,
        /// Наведение на текущую сущность
        Hovering_Current,
        /// Наведение на неприлигающую сущность
        Hovering_Zero
    };

    Hovering hovering = Hovering::Hovering_None;
};

}
