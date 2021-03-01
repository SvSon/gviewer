#pragma once

#include "../../include/ggraph.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace gviewer {

/// Конвертер из json в формат графа
class JsonConverter
{
public:

    GGraph from(const QJsonDocument& document);

};

}
