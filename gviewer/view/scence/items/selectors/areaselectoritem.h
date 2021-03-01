#pragma once

#include <QGraphicsItem>
#include <QPainterPath>

namespace gviewer {

class AreaSelectorItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit AreaSelectorItem(const QPointF start, QGraphicsItem* parent = nullptr);

    QPainterPath shape() const;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void trackMouse(const QPointF& position);

signals:
    void selectionChanged(const QPainterPath& path);

private:
    QRectF areaRect;
    QPointF startPoint;


};

}
