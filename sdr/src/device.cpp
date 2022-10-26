#include "Device.h"

namespace sdr
{
    Device::Device(const SoapySDR::Kwargs& kwargs) : m_properties(kwargs)
    {
        m_device = SoapySDR::Device::make(kwargs);
    }

    Device::~Device() noexcept
    {
        if (m_device != nullptr)
        {
            SoapySDR::Device::unmake(m_device);
            m_device = nullptr;
        }
    }

    const std::string Device::operator[](const std::string& key) const
    { 
        if(m_properties.find(key) != m_properties.cend())
        {
            return m_properties.at(key);
        }
        else
        {
            return "not found";
        }
    }

    const std::string Device::GetDriverKey() const
    {
        return m_device->getDriverKey();
    }

    const std::string Device::GetHardwareKey() const
    {
        return m_device->getHardwareKey();
    }

    const std::map<std::string, std::string> Device::GetHardwareInfo() const
    {
        return m_device->getHardwareInfo();
    }

    const std::string Device::GetFrontendMapping(const direction dir) const
    {
        return m_device->getFrontendMapping(static_cast<int>(dir));
    }

    size_t Device::GetNumberOfChannels(const direction dir) const
    {
        return m_device->getNumChannels(static_cast<int>(dir));
    }

    std::map<std::string, std::string> Device::GetChannelInfo(const direction dir, 
                const size_t channel) const
    {
        return m_device->getChannelInfo(static_cast<int>(dir), channel);
    }

    bool Device::GetFullDuplex(const direction dir, const size_t channel) const
    {
        return m_device->getFullDuplex(static_cast<int>(dir), channel);
    }

    const std::vector<std::string> Device::GetStreamFormats(const direction dir,
                const size_t channel) const
    {
        return m_device->getStreamFormats(static_cast<int>(dir), channel);
    }

    const std::tuple<std::string, double> Device::GetNativeStreamFormat(
                const direction dir, const size_t channel) const
    {
        double fullScale;
        auto format = m_device->getNativeStreamFormat(static_cast<int>(dir), channel,
            fullScale);
        return std::make_tuple(format, fullScale);
    }

    std::vector<sdr_arg_info> Device::GetStreamArgsInfo(const direction dir,
                const size_t channel) const
    {
        std::vector<sdr_arg_info> infos;
        std::vector<SoapySDR::ArgInfo> soapy_infos = m_device->getStreamArgsInfo(
            static_cast<int>(dir), channel);
        for(auto& soapy_info : soapy_infos)
        {
            infos.push_back(soapy_info);
        }
        return infos;
    }

    double Device::GetSampleRate(const direction dir, const size_t channel) const
    {
        return m_device->getSampleRate(static_cast<int>(dir), channel);
    }

    void Device::GetSampleRate(const direction dir, const size_t channel,
                const double rate)
    {
        m_device->setSampleRate(static_cast<int>(dir), channel, rate);
    }

    std::vector<double> Device::GetSampleRates(const direction dir,
                const size_t channel) const
    {
        if (m_device != nullptr)
        {
            return m_device->listSampleRates(static_cast<int>(dir), channel);
        }
        else 
        {
            return std::vector<double>();
        }
    }

    std::vector<std::string> Device::ListGPIOBanks() const
    {
        return m_device->listGPIOBanks();
    }

    std::vector<std::string> Device::ListRegisterInterfaces() const
    {
        return m_device->listRegisterInterfaces();
    }

    double Device::GetCenterFrequency(const direction dir, const size_t channel) const
    {
        return m_device->getFrequency(static_cast<int>(dir), channel);
    }

    void Device::SetCenterFrequency(const direction dir, const size_t channel, const double frequency)
    {
        m_device->setFrequency(static_cast<int>(dir), channel, frequency);
    }
}