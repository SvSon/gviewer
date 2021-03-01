#pragma once

#include "../../include/ggraph.h"

namespace gviewer {

/// Укладка графа на плоскости согласно случайному распределению верниш
class RandomLayoutTransformation
{
public:
    /// Применить алогоритм к графу
    void applyFor(GGraph& graph);
};

}
