#pragma once

#include <vector>
#include <iterator>
#include "Device.h"

namespace sdr
{
    class devices
    {
        public:
            using container=std::vector<std::shared_ptr<Device>>;
            using iterator = typename container::iterator;
            using const_iterator = typename container::const_iterator;
            devices();
            devices(const devices&) = default;
            devices(devices&&) = default;
            devices& operator=(const devices&) = delete;
            devices& operator=(devices&&) = default;
            iterator begin() { return _devices.begin(); }
            iterator end() { return _devices.end(); }
            const_iterator cbegin() { return _devices.cbegin(); }
            const_iterator cend() { return _devices.cend(); }
            void clear();
            size_t size() { return _devices.size(); }
            void refresh();
            const std::shared_ptr<sdr::Device>& operator[](size_t index) const;
            void remove_all_except(std::shared_ptr<Device>& pdev);
        private:
            void _attached_devices();

            container _devices;
    };
}