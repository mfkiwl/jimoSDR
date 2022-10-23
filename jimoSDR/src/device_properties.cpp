#include "device_properties.h"

namespace jimo_sdr
{
    device_properties::device_properties(std::shared_ptr<sdr::device> device)
        : _device(device), _sample_rate(0), _sampling_mode(sampling_mode::mode::quadrature)
    {
    }
}