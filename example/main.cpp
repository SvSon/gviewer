#include <QApplication>
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

#include "boost/graph/graphml.hpp"
#include "gviewer/include/ggraph.h"
#include "gviewer/view/gview.h"

#include "gviewer/tools/converters/jsonconverter.h"
#include "gviewer/tools/converters/graphmlconverter.h"
#include "gviewer/tools/transformations/randomlayouttransformation.h"

using namespace gviewer;

void fromRandom(GGraph& graph, int nodesCount, int edgesCount)
{
    QList<GNodeDescriptor> nodes;
    for(int i=0;i<nodesCount;++i) {
        GNode node;
//        node.properties.size = i;
        node.properties.color = "#c02943";
        node.properties.label.name = QString("node: %1").arg(i);
//        node.properties.label.size = i;
        nodes << boost::add_vertex(node, graph);
    }
    for(int i=0;i<edgesCount;++i) {
        auto from = rand()%(nodes.size()-1);
        auto to = rand()%(nodes.size()-1);

        GEdge edge;
//        edge.id = QString::number(i);
        edge.properties.label.name = QString("edge: %1").arg(i);
        boost::add_edge(nodes.at(from), nodes.at(to), edge, graph);
    }

//    auto node = nodes.at(50);
//    auto dd = boost::get(boost::vertex_bundle, graph);
//    auto out = boost::out_edges(node, graph);
//    auto outCount = out.second - out.first;
//    auto in = boost::in_edges(node, graph);
//    auto inCount = in.second - in.first;
//    auto inL = boost::in_edge_list(graph, node);
//    int i=0;

}

void fromJson(GGraph& graph, const QString& filename)
{
    QFile file(filename);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString json = file.readAll();

        QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
        qDebug() << doc.toJson(QJsonDocument::Compact);

        JsonConverter converter;
        graph = converter.from(doc);

        file.close();
    }

}

void fromFile(GGraph& graph, const QString& filename)
{
    QFile file(filename);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();

        GraphMLConverter converter;
        graph = converter.from(xmlReader);

        file.close();
    }
}

void printGraph(const GGraph& graph)
{
    boost::graph_traits<GGraph>::vertex_iterator vi, vi_end;
    for (boost::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi) {
        auto& node = boost::get(boost::vertex_bundle, graph)[*vi];
        qDebug() << node.id
                 << " " << node.properties.label.name
                 << " " << node.properties.center;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GGraph graph;

//    fromRandom(graph, 1000, 1000);
    fromJson(graph, "C:/tmp/ml/g3.json");
//    fromFile(graph, "C:/tmp/ml/1.graphml");

    RandomLayoutTransformation transformation;
    transformation.applyFor(graph);

    printGraph(graph);

    GView view;
    view.setGraph(graph);
    view.show();

    return a.exec();
}
