#include "randomlayouttransformation.h"

#include <boost/graph/random_layout.hpp>
#include <boost/graph/fruchterman_reingold.hpp>
#include <boost/graph/kamada_kawai_spring_layout.hpp>
#include <boost/graph/topology.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/progress.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

#include <QDebug>

namespace gviewer {

class progress_cooling : public boost::linear_cooling<double>
{
  typedef boost::linear_cooling<double> inherited;

 public:
  explicit progress_cooling(std::size_t iterations) : inherited(iterations)
  {
    display.reset(new boost::progress_display(iterations + 1, std::cerr));
  }

  double operator()()
  {
    ++(*display);
    return inherited::operator()();
  }

 private:
  boost::shared_ptr<boost::progress_display> display;
};

void RandomLayoutTransformation::applyFor(GGraph &graph)
{
    GNodeIterator it, end;
    boost::tie(it, end) = boost::vertices(graph);

    const uint count = end - it;
    if(count < 1) return;

    const int areaSize = 500.0*count;
    const int areaSizeH2 = areaSize/2;

//    typedef boost::rectangle_topology<> topology_type;
//    typedef topology_type::point_type point_type;

//    typedef std::vector<point_type> PositionVec;
//    typedef boost::iterator_property_map<PositionVec::iterator, boost::property_map<GGraph, boost::vertex_index_t>::type> PositionMap;

//    PositionVec position_vec(num_vertices(graph));
//    PositionMap position(position_vec.begin(), get(boost::vertex_index, graph));

//    int iterations = 400;
//    boost::minstd_rand gen;
//    topology_type topo(gen, -areaSizeH2/2, -areaSizeH2/2, areaSizeH2/2, areaSizeH2/2);
//    boost::random_graph_layout(graph, position, topo);
//    boost::fruchterman_reingold_force_directed_layout(graph, position, topo,
//                                                      cooling(boost::linear_cooling<double>(iterations)));
////    auto w = boost::get(boost::edge_weight, graph);
////    auto w = graph.get_edge_double_map("weight");
////    boost::kamada_kawai_spring_layout(graph, position, w, topo, boost::side_length(areaSize));

//    boost::graph_traits<GGraph>::vertex_iterator vi, vi_end;
//    for (boost::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi) {
//        auto& node = boost::get(boost::vertex_bundle, graph)[*vi];
////        qDebug() << node.id << QString::number(position[*vi][0]) << '\t' << QString::number(position[*vi][1]);
//        node.properties.center = QPointF(position[*vi][0], position[*vi][1]);
//    }

    float rx = 0.0;
    float ry = 0.0;

    for(; it!=end; ++it) {
        auto& node = boost::get(boost::vertex_bundle, graph)[*it];

        if(node.properties.center.isNull()) {
            rx = rand()%areaSize - areaSizeH2;
            ry = rand()%areaSize - areaSizeH2;
            const auto& size = node.properties.size;
            node.properties.center = QPointF(rx-size, ry-size);
        }
    }



}


}
