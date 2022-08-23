#include "devices.h"

namespace soapy
{
    std::vector<device> devices::get_devices()
    {
        std::vector<SoapySDR::Kwargs> kList = SoapySDR::Device::enumerate();
        std::vector<device> devs;
//        devs.reserve(kList.size());
        for(auto& dev : kList)
        {
            devs.push_back(device(dev));
        }
        return devs;
    }
}