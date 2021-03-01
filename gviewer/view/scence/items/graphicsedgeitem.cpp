#include "graphicsedgeitem.h"

#include "../../../include/gsceneevents.h"

#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>

#include <QDebug>

#include <QtMath>

namespace gviewer {

GraphicsEdgeItem::GraphicsEdgeItem(GGraph& ggraph, GEdge& gedge, const GNode& gsource, const GNode& gtarget,
                                   const EdgesSceneProperties& properties, QGraphicsItem *parent) :
    QGraphicsItem(parent), graph(ggraph), edge(gedge), source(gsource), target(gtarget),
    edgeProperties(properties)
{
    setFlags(QGraphicsItem::ItemSendsGeometryChanges);

    setData(DataKeys::Type, ItemsType::ItemsType_Edge);

}

QRectF gviewer::GraphicsEdgeItem::boundingRect() const
{
    return QRectF(source.properties.center, target.properties.center).normalized();
}

QPolygonF GraphicsEdgeItem::paintArrow(const QLineF& line)
{
    QPolygonF arrow;
    const int arrowSize = edge.properties.size*100;
    const double angle = std::atan2(-line.dy(), line.dx());

    static const double M_PI_2_25 = M_PI/2.25;
    static const double M_PI_M_2_25 = M_PI - M_PI_2_25;

    const QPointF arrowP1 = line.p2() - QPointF(sin(angle + M_PI_2_25) * arrowSize, cos(angle + M_PI_2_25) * arrowSize);
    const QPointF arrowP2 = line.p2() - QPointF(sin(angle + M_PI_M_2_25) * arrowSize, cos(angle + M_PI_M_2_25) * arrowSize);
    arrow << line.p2() << arrowP1 << arrowP2;
    return arrow;
}

GEdge &GraphicsEdgeItem::getEdge() const
{
    return edge;
}

void gviewer::GraphicsEdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    if(!edgeProperties.edgeVisible) {
        return;
    }

    QPen pen;

    if(edge.viewProperties.hovering == ViewProperties::Hovering_In) {
        pen.setColor(QColor("#AA0000"));
        setZValue(2);
    }
    else if(edge.viewProperties.hovering == ViewProperties::Hovering_Out) {
        pen.setColor(QColor("#00AA00"));
        setZValue(2);
    }
    else if(edge.viewProperties.hovering == ViewProperties::Hovering_Zero) {
        pen.setColor(QColor(160,160,160,120));
        setZValue(1);
    }
    else {
        pen.setColor(edge.properties.color);
        setZValue(1);
    }

    pen.setWidth(edge.properties.size*MULTIPLY_SIZE*4);
    painter->setPen(pen);

    QLineF line(source.properties.center, target.properties.center);
    painter->drawLine(line);

    line.setLength(line.length() - target.properties.size*MULTIPLY_SIZE);
    pen.setWidth(1);
    pen.setColor(pen.color().lighter(200));
    painter->setPen(pen);
    painter->setBrush(pen.color());

    painter->drawPolygon(paintArrow(line));

    if(edgeProperties.edgeLabelVisible) {
        QFont font;
        font.setPixelSize(edge.properties.label.size*MULTIPLY_SIZE);
        font.setBold(true);
        painter->setPen(edge.properties.label.color);
        painter->setFont(font);
        painter->setBrush(Qt::NoBrush);
        const auto rect = boundingRect();
        painter->drawText(rect.center(), edge.properties.label.name);
    }
}

QVariant GraphicsEdgeItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    return QGraphicsItem::itemChange(change, value);
}

}


