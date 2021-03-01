#include "jsonconverter.h"

#include <QHash>

namespace gviewer {

GGraph JsonConverter::from(const QJsonDocument &document)
{
    GGraph graph;

    const auto root = document.object();

    QHash<int, GNodeDescriptor> nodesMap;

    QJsonObject obj;

    const auto nodes = root.value("nodes").toArray();
    GNode gnode;
    int id;
    for(const auto& node : nodes) {
        obj = node.toObject();
        id = obj.value("id").toInt();
        gnode.id = QString::number(id);
        gnode.properties.center.setX(obj.value("x").toDouble()*10000);
        gnode.properties.center.setY(obj.value("y").toDouble()*10000);
        gnode.properties.label.name = QString("Узел %1").arg(id);
        nodesMap.insert(id, boost::add_vertex(gnode, graph));
    }

    const auto links = root.value("links").toArray();
    GEdge edge;
    int source;
    int target;
    for(const auto& link : links) {
        obj = link.toObject();
        edge.id = QString::number(obj.value("key").toInt());
        edge.properties.label.name = QString::number(obj.value("label").toDouble());
        edge.properties.color = QColor(obj.value("color").toString());
        if(obj.contains("width")) {
            edge.properties.size = obj.value("width").toInt();
        }
        source = obj.value("source").toInt();
        target = obj.value("target").toInt();
        boost::add_edge(nodesMap[source], nodesMap[target], edge, graph);

    }


//    auto getAttributes = [](const QVariantMap& map) -> QString {
//        QString result = "[";
//        for(auto it= map.begin(); it!=map.end(); ++it) {
//            if(it.key() != "source" && it.key() != "target") {
//                result.append(" " + it.key() + "=\"" + it.value().toString() + "\"");
//            }
//        }
//        return result.append("]");
//    };

    return graph;

}
}
