#pragma once

#include <QColor>

namespace gviewer {

/// Свойства ребра графа
struct GEdgeProperties
{
    /// Подпись вершины
    struct Label {
        /// Размер подписи вершины
        int size = 20;
        /// Цвет подписи
        QColor color = Qt::white;
        /// Наименование ребра
        QString name;
    };

    /// Размер ребра
    qreal size = 2;
    /// Цвет ребра
    QColor color = QColor("#A0A0A4");
    /// Подпись
    Label label;
};

}
