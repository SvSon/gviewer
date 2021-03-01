#pragma once

#include "../include/ggraph.h"
#include "../include/sceneproperties.h"

#include "scence/items/selectors/areaselectoritem.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>

namespace gviewer {

class GViewGraphScene : public QGraphicsView
{
    Q_OBJECT
public:

    struct Tools {
        AreaSelectorItem* selector = nullptr;
    };

    explicit GViewGraphScene(QWidget *parent = nullptr);

    /// Установит текущий граф
    void setGraph(const GGraph &value);

    /// Установить свойста отображения
    void setSceneProperties(const SceneProperties &value);
    /// Получить текущие свойства отображения сцены
    SceneProperties getSceneProperties() const;

    NodesSceneProperties getNodesSceneProperties() const;
    void setNodesSceneProperties(const NodesSceneProperties &value);

    EdgesSceneProperties getEdgesSceneProperties() const;
    void setEdgesSceneProperties(const EdgesSceneProperties &value);

    SceneMode getMode() const;
    void setMode(SceneMode value);

    void printDebug();

private slots:
    /// Обновить всё отображение
    void updateAll();
    /// Обновить отображение сцены
    void updateView();
    /// Обновить отображение вершин
    void updateNodes();
    /// Обновить отображение рёбер
    void updateEdges();

private:
    /// Очистить группу элементов на сцене
    void deleteItemsFromGroup(QList<QGraphicsItem*>& group);

    /// Получить отображаемый участок
    QRectF getVisibleRect();

    /// Масштабировать с коэффициентом
    void zoom(qreal zooming, bool positiong = false);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    /// Сцена, на которой рисуются элменеты
    QGraphicsScene* scene = nullptr;
    /// Группа элементов для узлов
    QList<QGraphicsItem*> nodes;
    /// Группа элементов для рёбер
    QList<QGraphicsItem*> edges;

    /// Инструменты для работы со сценой
    Tools tools;

    /// Группа элементов временных объектов
    std::unique_ptr<QGraphicsItemGroup> tmp = nullptr;

    /// Таймер отложенной перерисовки
    QTimer* timer = nullptr;

    /// Настройки отображения сцены
    SceneProperties sceneProperties;
    /// Настройки отображения вершин на сцене
    NodesSceneProperties nodesSceneProperties;
    /// Настройки отображения рёбер на сцене
    EdgesSceneProperties edgesSceneProperties;

    /// Текущий режим работы со сценой
    SceneMode mode;

    /// Заполненнный граф
    GGraph graph;

    /// Позиция последнего нажатия левой кнопки мыши
    QPoint mousePressPosition;

    /// Текущая позиция курсора на сцене
    QPointF currentScenePos;
    /// Текущая позиция курсора
    QPointF currentViewportPos;

};

}
