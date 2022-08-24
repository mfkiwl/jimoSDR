#include "device.h"

namespace soapy
{
    device::device(const SoapySDR::Kwargs& kwargs) : _properties(kwargs)
    {
        _device = SoapySDR::Device::make(kwargs);
    }

    device::device(device&& dev) : _properties(dev._properties)
    {
        _device = dev._device;
        dev._device = nullptr;
    }

    device::~device() noexcept
    {
        if (_device != nullptr)
        {
            SoapySDR::Device::unmake(_device);
            _device = nullptr;
        }
    }

    const std::string device::operator[](const std::string& key) const
    { 
        if(_properties.find(key) != _properties.cend())
        {
            return _properties.at(key);
        }
        else
        {
            return "not found";
        }
    }

    const std::string device::driver_key() const
    {
        return _device->getDriverKey();
    }
}