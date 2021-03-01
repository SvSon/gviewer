#pragma once

#include <QEvent>

namespace gviewer {

/// Специальные события сцены
enum GSceneEvent {
    /// Обновление позиции прилегающего узла
    GSceneEvent_UpdateNodePosition = QEvent::User+1
};

}
