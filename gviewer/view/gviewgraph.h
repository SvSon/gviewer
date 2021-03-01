#pragma once

#include "../include/ggraph.h"

#include "gviewgraphscene.h"

#include <QWidget>
#include <QMainWindow>

namespace Ui {
class GViewGraph;
}

namespace gviewer {

/// Форма отображения сцены графа и инструменов для работы со сценой
class GViewGraph : public QWidget
{
    Q_OBJECT

public:

    explicit GViewGraph(QWidget *parent = nullptr);
    ~GViewGraph();

    /// Установить отображаемый граф
    void setGraph(const GGraph &value);

    /// Выдать сцену
    GViewGraphScene *getView() const;

    /// Установить инструменты для главного окна
    void setToolBarsFor(QMainWindow* window);

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

signals:
    void visibleChaned(bool visible);

private:
    Ui::GViewGraph *ui;

    /// Виджет сцены, на которой будет рисоваться граф
    GViewGraphScene* view;

    /// Заполненнный граф
    GGraph graph;


};

}
