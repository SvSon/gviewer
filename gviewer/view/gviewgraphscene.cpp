#include "gviewgraphscene.h"

#include "scence/items/graphicsnodeitem.h"
#include "scence/items/graphicsedgeitem.h"

#include <QApplication>
#include <QWheelEvent>
#include <QScrollBar>
#include <QOpenGLWidget>
#include <QCursor>
#include <QDebug>

#include <iterator>

namespace gviewer {

GViewGraphScene::GViewGraphScene(QWidget *parent) : QGraphicsView(parent)
{
    setAlignment(Qt::AlignCenter);
    setInteractive(true);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setMouseTracking(true);

    scene = new QGraphicsScene();
    setScene(scene);

    timer = new QTimer();
    timer->setSingleShot(true);

    connect(timer, &QTimer::timeout, this, &GViewGraphScene::updateAll);
    timer->start(50);

    setMode(SELECTING);

}

void GViewGraphScene::updateView()
{
    scene->setBackgroundBrush(QBrush(sceneProperties.background));
}

void GViewGraphScene::updateNodes()
{
    deleteItemsFromGroup(nodes);

    GNodeIterator it, end;
    boost::tie(it, end) = boost::vertices(graph);

    QFont font;
    QGraphicsItem* item;
    quint64 desc;
    for(; it!=end; ++it) {
        desc = *it;
        auto& node = boost::get(boost::vertex_bundle, graph)[desc];
        item = new GraphicsNodeItem(graph, desc, node, nodesSceneProperties);

        nodes.append(item);
        scene->addItem(item);
    }
    scene->update();
}

void GViewGraphScene::updateEdges()
{
    deleteItemsFromGroup(edges);

    GEdgeIterator it, end;
    boost::tie(it, end) = boost::edges(graph);

    QPen pen;
    QFont font;
    GEdgeDescriptor desc;
    QGraphicsItem* item;
    for(; it!=end; ++it) {
        GEdge& edge = boost::get(boost::edge_bundle, graph)[*it];
        GNode& source = boost::get(boost::vertex_bundle, graph)[boost::source(*it, graph)];
        GNode& target = boost::get(boost::vertex_bundle, graph)[ boost::target(*it, graph)];

        item = new GraphicsEdgeItem(graph, edge, source, target,
                                    edgesSceneProperties);

        edges.append(item);
        scene->addItem(item);
    }
    scene->update();
}

void GViewGraphScene::deleteItemsFromGroup(QList<QGraphicsItem *> &group)
{
    qDeleteAll(group);
    group.clear();
}

QRectF GViewGraphScene::getVisibleRect()
{
    const QPointF tl(horizontalScrollBar()->value(), verticalScrollBar()->value());
    const QPointF br = tl + viewport()->rect().bottomRight();
    const QMatrix mat = matrix().inverted();
    return mat.mapRect(QRectF(tl,br));
}

void GViewGraphScene::zoom(qreal zooming, bool positiong)
{
    scale(zooming, zooming);

    if(positiong) {
        centerOn(currentScenePos);
        const QPointF deltaViewportPos = currentViewportPos - QPointF(viewport()->width() / 2.0,
                                                                      viewport()->height() / 2.0);
        const QPointF viewportCenter = currentViewportPos - deltaViewportPos;
        centerOn(mapToScene(viewportCenter.toPoint()));
    }

    scene->update();
}

void GViewGraphScene::resizeEvent(QResizeEvent *event)
{
    timer->start(50);
    QWidget::resizeEvent(event);
}

void GViewGraphScene::setGraph(const GGraph& value)
{
    graph = value;

    updateAll();
}

SceneMode GViewGraphScene::getMode() const
{
    return mode;
}

void GViewGraphScene::setMode(SceneMode value)
{
    mode = value;
    switch (mode) {
        case gviewer::SELECTING:
            setDragMode(QGraphicsView::ScrollHandDrag);
            break;
    }
}

void GViewGraphScene::printDebug()
{
    auto toS = [](const QRectF& rect) {
        return QString("rect(%1,%2) w:%3 h:%4")
                .arg(rect.x())
                .arg(rect.y())
                .arg(rect.width())
                .arg(rect.height());
    };

    for(auto* item : nodes) {
        auto node = static_cast<GraphicsNodeItem*>(item);
        qDebug() << "NODE (" << node->getNode().id << "): " << node->getNode().properties.center
                 << " " << toS(item->boundingRect());
    }
    for(auto* item : edges) {
        auto edge = static_cast<GraphicsEdgeItem*>(item);
        qDebug() << "EDGE (" << edge->getEdge().id << "): "
                 << " " << toS(item->boundingRect());
    }
}

EdgesSceneProperties GViewGraphScene::getEdgesSceneProperties() const
{
    return edgesSceneProperties;
}

void GViewGraphScene::setEdgesSceneProperties(const EdgesSceneProperties &value)
{
    edgesSceneProperties = value;
    scene->update();
}

NodesSceneProperties GViewGraphScene::getNodesSceneProperties() const
{
    return nodesSceneProperties;
}

void GViewGraphScene::setNodesSceneProperties(const NodesSceneProperties &value)
{
    nodesSceneProperties = value;
    scene->update();
}

void GViewGraphScene::setSceneProperties(const SceneProperties &value)
{
    sceneProperties = value;
    updateView();
}

SceneProperties GViewGraphScene::getSceneProperties() const
{
    return sceneProperties;
}

void GViewGraphScene::updateAll()
{
    updateView();
    updateNodes();
    updateEdges();

    fitInView(scene->sceneRect().adjusted(-500,-500,500,500), Qt::KeepAspectRatio);
}

void GViewGraphScene::mouseMoveEvent(QMouseEvent *event)
{
    currentViewportPos = event->pos();
    currentScenePos = mapToScene(event->pos());

    QGraphicsView::mouseMoveEvent(event);

    const auto scenePosition = mapToScene(event->pos());

    if(tools.selector) {
        tools.selector->trackMouse(scenePosition);
    }
    scene->update();
}

void GViewGraphScene::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);

    if(tools.selector) {
        auto selecting = tools.selector->shape();
        scene->setSelectionArea(selecting, Qt::AddToSelection, Qt::ContainsItemShape);
        delete tools.selector;
        tools.selector = nullptr;
        scene->update(selecting.boundingRect());
    }
}

void gviewer::GViewGraphScene::mousePressEvent(QMouseEvent *event)
{
    mousePressPosition = event->pos();
    if ((event->buttons() & Qt::LeftButton)
            && (event->modifiers() & Qt::ControlModifier)){
        if(!tools.selector) {
            auto position = mapToScene(mousePressPosition);
            // TODO: выбирать инструмен селектора в записимости от типа
            tools.selector = new AreaSelectorItem(position);
            scene->addItem(tools.selector);
        }
    }
    else {
        QGraphicsView::mousePressEvent(event);
    }
}

void GViewGraphScene::wheelEvent(QWheelEvent *event)
{
    bool zoomIn = (event->angleDelta().ry() > 0);

    if (QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)) {
        if(zoomIn) zoom(1.3, true);
        else zoom(0.7);
    }
    else {
        if(zoomIn) zoom(1.1, true);
        else zoom(0.9);
    }

}

}
