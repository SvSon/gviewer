#pragma once

#include <QPointF>
#include <QRectF>
#include <QColor>

namespace gviewer {

/// Свойства вершины графа
struct GNodeProperties
{
    /// Подпись вершины
    struct Label {
        /// Размер подписи вершины
        int size = 20;
        /// Цвет подписи
        QColor color = Qt::white;
        /// Наименование вершины
        QString name;
    };

    /// Размер вершины
    qreal size = 50;
    /// Прямоугольник вершины на области
    QRectF rect;
    /// Место примыкания вершины
    QPointF center;
    /// Цвет вершины
    QColor color = QColor("#c02943");
    /// Подпись
    Label label;

};

}
