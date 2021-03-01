#pragma once

#include <QColor>
#include <QMetaType>

namespace gviewer {

/// Множитель при преобразовании размера вершины
const int MULTIPLY_SIZE = 5;

/// Настройки отображения узлов на сцене
struct NodesSceneProperties
{
    /// Отображать подписи узлов
    bool nodeLabelVisible = false;

    /// Интерактивность графа (отображение входящих/исходящих) при наведении
    bool nodeInteractiveHoverEnable = false;

    /// Интерактивность графа (отображение входящих/исходящих) при выделении
    bool nodeInteractiveSelectEnable = false;
};

/// Настройки отображения рёбер на сцене
struct EdgesSceneProperties
{
    /// Отображать рёбра
    bool edgeVisible = true;
    /// Отображать подписи рёбер
    bool edgeLabelVisible = false;
};

/// Настройки отображения сцены
struct SceneProperties {
    /// Цвет фона сцены
    QColor background = QColor("#232528");
};

/// Текщий режим работы со сценой графа
enum SceneMode {
    /// Выделение
    SELECTING = 0
};

/// Инструмент выделения
enum SelectionMode {
    /// Выделение прямоугольником
    SelectionMode_Area = 0
};

/// Подрежим выделения
enum SelectionSubMode {
    /// Добавить к текущему выделению
    APPEND = 0,
    /// Удалить текущее выделение
    REMOVE,
    /// Заменить текущее выделение
    SET
};

/// Ключи данных в описании элемента
enum DataKeys {
    /// Тип элемента на сцене
    Type = 0
};

/// Тип элемента на сцене
enum ItemsType {
    /// Неизвестный
    ItemsType_Unknow = 0,
    /// Вершина
    ItemsType_Node,
    /// Ребро
    ItemsType_Edge
};

}
Q_DECLARE_METATYPE(gviewer::ItemsType)
