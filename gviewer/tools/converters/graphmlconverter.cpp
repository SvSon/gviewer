#include "graphmlconverter.h"

#include <QXmlStreamAttribute>
#include <QDebug>

#include <tuple>

namespace gviewer {

GGraph GraphMLConverter::from(QXmlStreamReader &reader)
{
    GGraph graph;
    QHash<QString, GNodeDescriptor> nodesMap;

    using Attributes = QHash<QString, QString>;
    Attributes nodesAttribute;
    Attributes edgesAttribute;

    Attributes tmpAttribute;

    QString idAttribute;
    QString nameAttribute;

    GNodeDescriptor source;
    GNodeDescriptor target;

    auto readNode = [&nodesAttribute](GNode& node, QXmlStreamReader& reader) {
        QString nameAttribute;
        for(const auto& attr : reader.attributes()) {
            if(attr.name().toString() == "id") {
                node.id = attr.value().toString();
            }
        }
        reader.readNext();
        while (!(reader.isEndElement() && reader.name().toString() == "node")) {
            auto sds = reader.name().toString();
            if(reader.isStartElement() && reader.name().toString() == "data") {
                for(const auto& attr : reader.attributes()) {
                    if(attr.name().toString() == "key") {
                        nameAttribute = nodesAttribute[attr.value().toString()];
                        break;
                    }
                }

                if(nameAttribute == "x") {
                    node.properties.center.setX(reader.readElementText().toDouble());
                }
                else if(nameAttribute == "y") {
                    node.properties.center.setY(reader.readElementText().toDouble());
                }
                else if(nameAttribute == "size") {
                    node.properties.size = reader.readElementText().toDouble();
                }
                else if(nameAttribute == "label") {
                    node.properties.label.name = reader.readElementText();
                }
            }
            reader.readNext();
        };
    };

    auto readEdge = [&edgesAttribute, &nodesMap](GEdge& edge, GNodeDescriptor& source, GNodeDescriptor& target, QXmlStreamReader& reader) {

        for(const auto& attr : reader.attributes()) {
            if(attr.name().toString() == "id") {
                edge.id = attr.value().toString();
            }
            if(attr.name().toString() == "source") {
                source = nodesMap[attr.value().toString()];
            }
            if(attr.name().toString() == "target") {
                target = nodesMap[attr.value().toString()];
            }
        }
        reader.readNext();
        QString nameAttribute;
        while (!(reader.isEndElement() && reader.name().toString() == "edge")) {
            auto sds = reader.name().toString();
            if(reader.isStartElement() && reader.name().toString() == "data") {
                for(const auto& attr : reader.attributes()) {
                    if(attr.name().toString() == "key") {
                        nameAttribute = edgesAttribute[attr.value().toString()];
                        break;
                    }
                }

                if(nameAttribute == "weight") {
                    edge.properties.size = reader.readElementText().toDouble();
                }
            }
            reader.readNext();
        };
    };


    GNode node;
    GEdge edge;

    while(!reader.atEnd()) {
        if(reader.isStartElement()) {
            if(reader.name() == "key") {
                tmpAttribute.clear();

                bool forNode = true;
                for(const auto& attr : reader.attributes()) {
                    if(attr.name().toString() == "for") {
                        const QString attrValue = attr.value().toString();
                        forNode = (attrValue == "node");
                    }
                    if(attr.name().toString() == "id") {
                        idAttribute = attr.value().toString();
                    }
                    if(attr.name().toString() == "attr.name") {
                        nameAttribute = attr.value().toString();
                    }
                }
                if(forNode) {
                    nodesAttribute[idAttribute] = nameAttribute;
                }
                else {
                    edgesAttribute[idAttribute] = nameAttribute;
                }
            } else if(reader.name() == "node") {
                readNode(node, reader);
                nodesMap.insert(node.id, boost::add_vertex(node, graph));
            } else if(reader.name() == "edge"){
                readEdge(edge, source, target, reader);
                boost::add_edge(source, target, edge, graph);
            }
        }
        reader.readNext();
    }

    return graph;
}


}
