#pragma once

#include "Device.h"

namespace jimo_sdr
{
    struct SetSampleRateData
    {
        std::shared_ptr<sdr::Device> m_device;
        double m_rate;
    };
}