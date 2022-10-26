#include "Device.h"

namespace sdr
{
    Device::Device(const SoapySDR::Kwargs& kwargs) : _properties(kwargs)
    {
        _device = SoapySDR::Device::make(kwargs);
    }

    Device::~Device() noexcept
    {
        if (_device != nullptr)
        {
            SoapySDR::Device::unmake(_device);
            _device = nullptr;
        }
    }

    const std::string Device::operator[](const std::string& key) const
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

    const std::string Device::GetDriverKey() const
    {
        return _device->getDriverKey();
    }

    const std::string Device::GetHardwareKey() const
    {
        return _device->getHardwareKey();
    }

    const std::map<std::string, std::string> Device::GetHardwareInfo() const
    {
        return _device->getHardwareInfo();
    }

    const std::string Device::GetFrontendMapping(const direction dir) const
    {
        return _device->getFrontendMapping(static_cast<int>(dir));
    }

    size_t Device::GetNumberOfChannels(const direction dir) const
    {
        return _device->getNumChannels(static_cast<int>(dir));
    }

    std::map<std::string, std::string> Device::GetChannelInfo(const direction dir, 
                const size_t channel) const
    {
        return _device->getChannelInfo(static_cast<int>(dir), channel);
    }

    bool Device::GetFullDuplex(const direction dir, const size_t channel) const
    {
        return _device->getFullDuplex(static_cast<int>(dir), channel);
    }

    const std::vector<std::string> Device::GetStreamFormats(const direction dir,
                const size_t channel) const
    {
        return _device->getStreamFormats(static_cast<int>(dir), channel);
    }

    const std::tuple<std::string, double> Device::GetNativeStreamFormat(
                const direction dir, const size_t channel) const
    {
        double fullScale;
        auto format = _device->getNativeStreamFormat(static_cast<int>(dir), channel,
            fullScale);
        return std::make_tuple(format, fullScale);
    }

    std::vector<sdr_arg_info> Device::GetStreamArgsInfo(const direction dir,
                const size_t channel) const
    {
        std::vector<sdr_arg_info> infos;
        std::vector<SoapySDR::ArgInfo> soapy_infos = _device->getStreamArgsInfo(
            static_cast<int>(dir), channel);
        for(auto& soapy_info : soapy_infos)
        {
            infos.push_back(soapy_info);
        }
        return infos;
    }

    double Device::GetSampleRate(const direction dir, const size_t channel) const
    {
        return _device->getSampleRate(static_cast<int>(dir), channel);
    }

    void Device::GetSampleRate(const direction dir, const size_t channel,
                const double rate)
    {
        _device->setSampleRate(static_cast<int>(dir), channel, rate);
    }

    std::vector<double> Device::GetSampleRates(const direction dir,
                const size_t channel) const
    {
        if (_device != nullptr)
        {
            return _device->listSampleRates(static_cast<int>(dir), channel);
        }
        else 
        {
            return std::vector<double>();
        }
    }

    std::vector<std::string> Device::gpio_banks() const
    {
        return _device->listGPIOBanks();
    }

    std::vector<std::string> Device::register_interfaces() const
    {
        return _device->listRegisterInterfaces();
    }

    double Device::GetCenterFrequency(const direction dir, const size_t channel) const
    {
        return _device->getFrequency(static_cast<int>(dir), channel);
    }

    void Device::SetCenterFrequency(const direction dir, const size_t channel, const double frequency)
    {
        _device->setFrequency(static_cast<int>(dir), channel, frequency);
    }
}