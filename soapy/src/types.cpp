#include "types.h"

namespace soapy
{
    sdr_range::sdr_range(const SoapySDR::Range& range)
        : _minimum(range.minimum()), _maximum(range.maximum()), _step(range.step()) {}

    sdr_arg_info::sdr_arg_info(SoapySDR::ArgInfo& info)
        : _range(info.range)
    {
        _key = info.key;
        _value = info.value;
        _name = info.name;
        _description = info.description;
        _units = info.units;
        _type = static_cast<arg_type>(info.type);
//        _range = info.range;
        _options = info.options;
        _option_names = info.optionNames;
    }

    const std::string sdr_arg_info::key() const
    { 
        return _key;
//        return std::get<std::string>(_values["key"]);
    }

    const std::string sdr_arg_info::value() const
    {
        return _value;
 //       return std::get<std::string>(_values["value"]);
    }

    const std::string sdr_arg_info::name() const
    {
        return _name;
//        return std::get<std::string>(_values["name"]);
    }

    const std::string sdr_arg_info::description() const
    {
        return _description;
//        return std::get<std::string>(_values["description"]);
    }

    const std::string sdr_arg_info::units() const
    {
        return _units;
//        return std::get<std::string>(_values["units"]);
    }

    sdr_arg_info::arg_type sdr_arg_info::type() const
    {
        return _type;
//        return std::get<sdr_arg_info::arg_type>(_values["type"]);
    }

    const sdr_range sdr_arg_info::range() const
    {
        return _range;
//        return std::get<sdr_range>(_values["range"]);
    }

    const std::vector<std::string> sdr_arg_info::options() const
    {
        return _options;
//        return std::get<std::vector<std::string>>(_values["options"]);
    }

    const std::vector<std::string> sdr_arg_info::option_names() const
    {
        return _option_names;
 //       return std::get<std::vector<std::string>>(_values["option_names"]);
    }
}