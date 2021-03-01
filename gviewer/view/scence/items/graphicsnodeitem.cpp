#include "graphicsnodeitem.h"

#include "../../../include/gsceneevents.h"
#include "../../../include/sceneproperties.h"
#include "graphicsedgeitem.h"

#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include <QApplication>
#include <QEvent>

#include <QDebug>

//#include <boost/graph/

#include <math.h>

namespace gviewer {

GraphicsNodeItem::GraphicsNodeItem(GGraph& ggraph, quint64 descriptor, GNode &gnode,
                                   const NodesSceneProperties& properties,
                                   QGraphicsItem *parent)
    : QGraphicsItem(parent), graph(ggraph), desc(descriptor), node(gnode),
      nodeProperties(properties)
{
    if(node.properties.rect.isNull()) {
        const auto& size = node.properties.size*MULTIPLY_SIZE;
        node.properties.rect = QRectF(node.properties.center-QPointF(size, size),
                                      QSize(size*2, size*2));
    }

    areaRect = node.properties.rect;

    setFlags(QGraphicsItem::ItemIsSelectable
             | QGraphicsItem::ItemIsMovable
             | QGraphicsItem::ItemSendsGeometryChanges);

    setAcceptDrops(true);
    setAcceptHoverEvents(true);

    setZValue(2);
    setData(DataKeys::Type, ItemsType::ItemsType_Node);
}

QPainterPath gviewer::GraphicsNodeItem::shape() const
{
    QPainterPath path;
    path.addRect(areaRect);
    return path;
}

QRectF gviewer::GraphicsNodeItem::boundingRect() const
{
    return areaRect;
}

void gviewer::GraphicsNodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget*)
{
    if(option->state & QStyle::State_Selected) {
        fillArea(QColor(119, 161, 104, 154), painter);
    }

    QPen pen(node.properties.color.lighter(), 30);
    painter->setPen(pen);
    painter->setBrush(node.properties.color);
    painter->drawEllipse(node.properties.rect);

    if(nodeProperties.nodeLabelVisible) {
        QFont font;
        font.setPixelSize(node.properties.label.size*MULTIPLY_SIZE);
        font.setBold(true);
        painter->setPen(node.properties.label.color);
        painter->setFont(font);
        const auto rect = node.properties.rect;
        painter->drawText(QPointF(rect.right()+rect.width()/8, rect.center().y()),
                          node.properties.label.name);
    }

    if(node.viewProperties.hovering == ViewProperties::Hovering_Current) {
        setZValue(3);
        fillArea(QColor("#FFFF55"), painter);
    }
    else if(node.viewProperties.hovering == ViewProperties::Hovering_In) {
        setZValue(3);
        fillArea(QColor("#AA0000"), painter);
    }
    else if(node.viewProperties.hovering == ViewProperties::Hovering_Out) {
        setZValue(3);
        fillArea(QColor("#00AA00"), painter);
    }
    else if(node.viewProperties.hovering == ViewProperties::Hovering_Zero) {
        setZValue(2);
        fillArea(QColor(160,160,160), painter);
    }
    else {
        setZValue(2);
    }
}

void GraphicsNodeItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    if(!nodeProperties.nodeInteractiveHoverEnable) return;

    boost::graph_traits<GGraph>::edge_iterator eIt, eEnd;
    for (boost::tie(eIt, eEnd)=boost::edges(graph); eIt!= eEnd; ++eIt) {
        boost::get(boost::edge_bundle, graph)[*eIt].viewProperties.hovering = ViewProperties::Hovering_Zero;
    }

    boost::graph_traits<GGraph>::vertex_iterator nIt, nEnd;
    for (boost::tie(nIt, nEnd)=boost::vertices(graph); nIt!= nEnd; ++nIt) {
        boost::get(boost::vertex_bundle, graph)[*nIt].viewProperties.hovering = ViewProperties::Hovering_Zero;
    }

    node.viewProperties.hovering = ViewProperties::Hovering_Current;

    boost::graph_traits<GGraph>::out_edge_iterator eOutIt, eOutEnd;
    for (boost::tie(eOutIt, eOutEnd)=boost::out_edges(desc, graph); eOutIt!= eOutEnd; ++eOutIt) {
        boost::get(boost::edge_bundle, graph)[*eOutIt].viewProperties.hovering = ViewProperties::Hovering_Out;
        boost::get(boost::vertex_bundle, graph)[ boost::target(*eOutIt, graph)].viewProperties.hovering = ViewProperties::Hovering_Out;
    }

    boost::graph_traits<GGraph>::in_edge_iterator eInIt, eInEnd;
    for (boost::tie(eInIt, eInEnd)=boost::in_edges(desc, graph); eInIt!= eInEnd; ++eInIt) {
        boost::get(boost::edge_bundle, graph)[*eInIt].viewProperties.hovering = ViewProperties::Hovering_In;
        boost::get(boost::vertex_bundle, graph)[ boost::source(*eInIt, graph)].viewProperties.hovering = ViewProperties::Hovering_In;
    }

    update();
}

void GraphicsNodeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    if(!nodeProperties.nodeInteractiveHoverEnable) return;

    boost::graph_traits<GGraph>::edge_iterator eIt, eEnd;
    for (boost::tie(eIt, eEnd)=boost::edges(graph); eIt!= eEnd; ++eIt) {
        boost::get(boost::edge_bundle, graph)[*eIt].viewProperties.hovering = ViewProperties::Hovering_None;
    }

    boost::graph_traits<GGraph>::vertex_iterator nIt, nEnd;
    for (boost::tie(nIt, nEnd)=boost::vertices(graph); nIt!= nEnd; ++nIt) {
        boost::get(boost::vertex_bundle, graph)[*nIt].viewProperties.hovering = ViewProperties::Hovering_None;
    }

    update();
}

void GraphicsNodeItem::fillArea(const QColor &color, QPainter *painter)
{
    painter->setPen(color);
    painter->setBrush(color);
    painter->drawEllipse(areaRect);
}

QVariant GraphicsNodeItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    static const int MAX_SIZE_OUTLINE = 100;
    if(change == QGraphicsItem::ItemSelectedHasChanged) {
        prepareGeometryChange();
        if(value.toBool()) {
            auto size2 = node.properties.size*2*MULTIPLY_SIZE;
            if(size2 > MAX_SIZE_OUTLINE) size2 = MAX_SIZE_OUTLINE;
            areaRect = node.properties.rect.adjusted(-size2,-size2,size2,size2);
        }
        else {
            auto tmpRect = areaRect;
            areaRect = node.properties.rect;
            scene()->update(tmpRect);
        }
        scene()->update();
    }
    auto res = QGraphicsItem::itemChange(change, value);
    if (change == ItemPositionHasChanged) {
        auto position = boundingRect().center();
        node.properties.center = mapToScene(position);
        scene()->update();
    }
    return res;
}

GNode &GraphicsNodeItem::getNode() const
{
    return node;
}

}
