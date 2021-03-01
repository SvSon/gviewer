#include "areaselectoritem.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QBrush>

namespace gviewer {

AreaSelectorItem::AreaSelectorItem(const QPointF start, QGraphicsItem *parent) :
    QGraphicsItem(parent), startPoint(start)
{
    setAcceptHoverEvents(true);
    setZValue(10);
    areaRect = QRectF(start, QSize(0,0));
}

QRectF AreaSelectorItem::boundingRect() const
{
    return areaRect;
}

void AreaSelectorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    auto path = shape();

    const auto colorSelection = QColor(51, 114, 104);

    QPen pen(colorSelection.darker(), 20, Qt::DashLine);
    painter->setPen(pen);

    QColor bColor = colorSelection;
    bColor.setAlphaF(0.5);
    QBrush brush(bColor);

    painter->setBrush(brush);

    painter->drawPath(path);
}

void AreaSelectorItem::trackMouse(const QPointF &position)
{
    prepareGeometryChange();

    areaRect.setBottomRight(position);

    selectionChanged(shape());
}

QPainterPath AreaSelectorItem::shape() const
{
    QPainterPath path;
    path.addRect(areaRect);
    return path;
}

}






