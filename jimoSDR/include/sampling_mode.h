#pragma once

#include <vector>
#include <string>

namespace jimo_sdr
{
    class sampling_mode
    {
        public:
            enum class mode
            {
                quadrature = 0,
                i_branch,
                q_branch
            };
            sampling_mode(enum mode mode = mode::quadrature) : _mode(mode) {}
            sampling_mode(const sampling_mode&) = default;
            sampling_mode(sampling_mode&&) = default;
            sampling_mode& operator=(const sampling_mode&) = default;
            sampling_mode& operator=(sampling_mode&&) = default;
            void mode(enum mode mode) { _mode = mode; }
            enum mode mode() { return _mode; }
            void mode(int mode) { _mode = static_cast<enum mode>(mode);
            ; }
            int mode_as_int() { return static_cast<int>(_mode); }
            static const std::vector<std::string> names();
        private:
            enum mode _mode;
    };
}