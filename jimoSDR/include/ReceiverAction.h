/// @file receiver_action.h
/// @copyright Copyright © 2022 Jim Orcheson. Licensed under GPL version 3.0

#pragma once
#include <functional>
#include <any>
#include "ReceiverTask.h"

namespace jimo_sdr
{
    struct ReceiverAction
    {
        ReceiverTask task;
        std::function<void(std::any)> callback;
        std::any m_data;
    };
}
