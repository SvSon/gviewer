#pragma once

#include "../../../include/ggraph.h"
#include "../../../include/sceneproperties.h"

#include <QGraphicsItem>

namespace gviewer {

class GraphicsNodeItem : public QGraphicsItem
{
public:
    explicit GraphicsNodeItem(GGraph& ggraph, quint64 descriptor, GNode& gnode,
                              const NodesSceneProperties& properties,
                              QGraphicsItem *parent = nullptr);

    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    GNode &getNode() const;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    /// Залить область подложки цветом
    void fillArea(const QColor& color, QPainter* painter);

private:
    GGraph& graph;
    quint64 desc;
    GNode& node;

    const NodesSceneProperties& nodeProperties;

    QRectF areaRect;

};


}
