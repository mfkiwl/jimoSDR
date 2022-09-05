#include "device_properties.h"

namespace jimo_sdr
{
/*    device_properties::device_properties() : _device(nullptr)
    {
//        _device = nullptr;
    }*/

    device_properties::device_properties(std::shared_ptr<soapy::device> device)
        : _device(device)
    {
    }
}