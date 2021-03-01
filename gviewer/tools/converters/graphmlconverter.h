#pragma once

#include "../../include/ggraph.h"

#include <QXmlStreamReader>

namespace gviewer {

class GraphMLConverter
{
public:
    GGraph from(QXmlStreamReader &reader);
};

}
