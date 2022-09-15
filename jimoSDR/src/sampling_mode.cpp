#include "sampling_mode.h"

namespace jimo_sdr
{
    const std::vector<std::string> sampling_mode::names()
    {
        std::vector<std::string> names = {"Quadrature", "Direct (I Branch)", "Direct (Q Branch)"};
        return names;
    }
}