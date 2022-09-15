#include "device_properties.h"

namespace jimo_sdr
{
    device_properties::device_properties(std::shared_ptr<soapy::device> device)
        : _device(device), _sampling_mode(sampling_mode::mode::quadrature)
    {
    }
}