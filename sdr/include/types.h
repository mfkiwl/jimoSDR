#pragma once

#include <string>
#include <vector>
#include <variant>
#include "SoapySDR/Types.hpp"

namespace soapy
{
    class sdr_range
    {
        public:
            sdr_range(const SoapySDR::Range& range);
            double minimum() const { return _minimum; }
            double maximum() const { return _maximum; }
            double step() const { return _step; }
        private:
            double _minimum;
            double _maximum;
            double _step;
    };

    class sdr_arg_info
    {
        public:
            enum class arg_type
            {
                BOOL = SoapySDR::ArgInfo::BOOL,
                INT = SoapySDR::ArgInfo::INT,
                FLOAT = SoapySDR::ArgInfo::FLOAT,
                STRING = SoapySDR::ArgInfo::STRING
            };

            sdr_arg_info(SoapySDR::ArgInfo& info); 
            const std::string key() const;
            const std::string value() const;
            const std::string name() const;
            const std::string description() const;
            const std::string units() const;
            arg_type type() const;
            const sdr_range range() const;
            const std::vector<std::string> options() const;
            const std::vector<std::string> option_names() const;
        
        private:
            std::string _key;
            std::string _value;
            std::string _name;
            std::string _description;
            std::string _units;
            arg_type _type;
            sdr_range _range;
            std::vector<std::string> _options;
            std::vector<std::string> _option_names;
//            std::map<std::string, std::variant<std::string, arg_type,
//                sdr_range, std::vector<std::string>>> _values;
    };
}