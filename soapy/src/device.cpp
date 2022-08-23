#include "device.h"

namespace soapy
{
    device::device(const SoapySDR::Kwargs& kwargs) : _kwargs(kwargs)
    {
        _device = SoapySDR::Device::make(kwargs);
    }

    device::device(device&& dev) : _kwargs(dev._kwargs)
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
}