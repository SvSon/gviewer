#pragma once

#include "../include/ggraph.h"

#include <QWidget>

namespace Ui {
class GViewLabData;
}

namespace gviewer {

/// Виджет отображения данных графа в виде таблицы
class GViewLabData : public QWidget
{
    Q_OBJECT

public:
    explicit GViewLabData(QWidget *parent = nullptr);
    ~GViewLabData();

    /// Установить отображаемый граф
    void setGraph(const GGraph &value);

private:
    Ui::GViewLabData *ui;

    /// Заполненнный граф
    GGraph graph;

};

}
