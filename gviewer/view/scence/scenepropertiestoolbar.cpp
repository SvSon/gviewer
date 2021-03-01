#include "scenepropertiestoolbar.h"

#include "../elements/colorpicker.h"

namespace gviewer {

ScenePropertiesToolBar::ScenePropertiesToolBar(GViewGraphScene* gscene, QWidget* parent) :
    QToolBar(parent), scene(gscene)
{
    initActions();
    setIconSize({24,24});
    setMinimumSize({32,32});
}

void ScenePropertiesToolBar::initActions()
{
    auto backgroundColor = new ColorPicker("Цвет фона: ", this);
    backgroundColor->setColor(scene->getSceneProperties().background);
    connect(backgroundColor, &ColorPicker::colorChanged, this, [this](const QColor& color){
        auto properties = scene->getSceneProperties();
        properties.background = color;
        scene->setSceneProperties(properties);
    });
    addWidget(backgroundColor);

    addSeparator();

    auto edgeVisible = addAction(QIcon(":/gviewer/images/resource/png/ic_16_edge_visible.png"), "Рёбра");
    edgeVisible->setCheckable(true);
    edgeVisible->setToolTip("Отображать рёбра");
    edgeVisible->setChecked(scene->getEdgesSceneProperties().edgeVisible);



    addSeparator();

    auto nodeLabelVisible = addAction(QIcon(":/gviewer/images/resource/png/ic_16_node_label.png"), "Подписи вершин");
    nodeLabelVisible->setCheckable(true);
    nodeLabelVisible->setToolTip("Подписи вершин");
    nodeLabelVisible->setChecked(scene->getNodesSceneProperties().nodeLabelVisible);
    connect(nodeLabelVisible, &QAction::toggled, this, [this](bool checked){
        auto properties = scene->getNodesSceneProperties();
        properties.nodeLabelVisible = checked;
        scene->setNodesSceneProperties(properties);
    });

    auto edgeLabelVisible = addAction(QIcon(":/gviewer/images/resource/png/ic_16_edge_label.png"), "Подписи рёбер");
    edgeLabelVisible->setCheckable(true);
    edgeLabelVisible->setToolTip("Подписи рёбер");
    edgeLabelVisible->setChecked(scene->getEdgesSceneProperties().edgeLabelVisible);

    connect(edgeLabelVisible, &QAction::toggled, this, [this](bool checked){
        auto properties = scene->getEdgesSceneProperties();
        properties.edgeLabelVisible = checked;
        scene->setEdgesSceneProperties(properties);
    });
    connect(edgeVisible, &QAction::toggled, this, [this, edgeLabelVisible](bool checked){
        auto properties = scene->getEdgesSceneProperties();
        properties.edgeVisible = checked;
        scene->setEdgesSceneProperties(properties);
        edgeLabelVisible->setEnabled(checked);
    });

    addSeparator();

    auto nodeHoverInteractive = addAction(QIcon(":/gviewer/images/resource/png/ic_15_mouse_hovering.png"), "Интерактивность наведения");
    nodeHoverInteractive->setCheckable(true);
    nodeHoverInteractive->setToolTip("Интерактивное наведение");
    nodeHoverInteractive->setChecked(scene->getNodesSceneProperties().nodeInteractiveHoverEnable);
    connect(nodeHoverInteractive, &QAction::toggled, this, [this](bool checked){
        auto properties = scene->getNodesSceneProperties();
        properties.nodeInteractiveHoverEnable = checked;
        scene->setNodesSceneProperties(properties);
    });

    connect(nodeHoverInteractive, &QAction::toggled, this, [this](bool checked){
        auto properties = scene->getNodesSceneProperties();
        properties.nodeInteractiveHoverEnable = checked;
        scene->setNodesSceneProperties(properties);
    });

}

}
