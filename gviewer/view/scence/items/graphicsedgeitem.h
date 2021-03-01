#pragma once

#include "../../../include/ggraph.h"
#include "../../../include/sceneproperties.h"

#include <QGraphicsItem>

namespace gviewer {

class GraphicsEdgeItem : public QGraphicsItem
{
public:
    explicit GraphicsEdgeItem(GGraph& ggraph, GEdge& gedge,
                              const GNode& gsource, const GNode& gtarget,
                              const EdgesSceneProperties& properties,
                              QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    GEdge &getEdge() const;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QPolygonF paintArrow(const QLineF &line);

private:
    GGraph& graph;
    GEdge& edge;
    const GNode& source;
    const GNode& target;

    const EdgesSceneProperties& edgeProperties;

};

}
