#include <memory>
#include "devices.h"

namespace soapy
{
    devices::devices()
    {
       _attached_devices();
    }

    void devices::_attached_devices()
    {
        std::vector<SoapySDR::Kwargs> kList = SoapySDR::Device::enumerate();
        _devices.reserve(kList.size());
        for(auto& dev : kList)
        {
            _devices.push_back(std::make_shared<device>(dev));
        }
    }

    void devices::refresh()
    {
        _devices.clear();
        _attached_devices();
    }
}