#pragma once

#include "gattributes.h"
#include "gnode.h"
#include "gedge.h"

#include <QHash>

#include <memory>

#include <boost/graph/adjacency_list.hpp>

namespace gviewer {

/// Направленный граф
using GGraph = boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, GNode, GEdge>;
/// Ссылка на направленный граф
using GGraphPtr = std::shared_ptr<GGraph>;
/// Тип итератора по рёбрам графа
using GEdgeIterator = boost::graph_traits<GGraph>::edge_iterator;
/// Тип итератора по вершинам графа
using GNodeIterator = boost::graph_traits<GGraph>::vertex_iterator;
/// Дескриптор хранения вершины в графе
using GNodeDescriptor = boost::graph_traits<GGraph>::vertex_descriptor;
/// Дескриптор хранения ребра в графе
using GEdgeDescriptor = boost::graph_traits<GGraph>::edge_descriptor;

}
Q_DECLARE_METATYPE(gviewer::GEdgeDescriptor)
