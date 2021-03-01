#pragma once

#include "../include/ggraph.h"

#include "gviewlabdata.h"
#include "gviewgraph.h"

#include <QMainWindow>

namespace Ui {
class GView;
}

namespace gviewer {

/// Главное окно отбражения графа
class GView : public QMainWindow
{
    Q_OBJECT

public:
    explicit GView(QWidget *parent = nullptr);
    ~GView();

    /// Установить граф для отображения
    void setGraph(const GGraph &value);

    /// Выдать виджет отображения графа
    GViewGraph *getViewGraph() const;

private:
    Ui::GView *ui;

    /// Заполненнный граф
    GGraph graph;

    /// Виджет отображения графа
    GViewGraph* viewGraph = nullptr;
};

}
