#include <memory>
#include "Devices.h"

namespace sdr
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
            _devices.push_back(std::make_shared<Device>(dev));
        }
    }

    void devices::clear()
    {
        _devices.clear();
    }

    void devices::refresh()
    {
        _devices.clear();
        _attached_devices();
    }

    void devices::remove_all_except(std::shared_ptr<Device>& pdev)
    {
        _devices.clear();
        _devices.push_back(pdev);
    }

    const std::shared_ptr<sdr::Device>& devices::operator[](size_t index) const
    {
        return _devices[index];
    }
}