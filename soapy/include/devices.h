#pragma once

#include <vector>
#include <iterator>
#include "device.h"

namespace soapy
{
    class devices
    {
        public:
            using container=std::vector<std::shared_ptr<device>>;
            using iterator = typename container::iterator;
            using const_iterator = typename container::const_iterator;
            devices();
            devices(const devices&) = delete;
            devices(devices&&) = delete;
            devices& operator=(const devices&) = delete;
            devices&& operator=(devices&&) = delete;
            iterator begin() { return _devices.begin(); }
            iterator end() { return _devices.end(); }
            const_iterator cbegin() { return _devices.cbegin(); }
            const_iterator cend() { return _devices.cend(); }
            size_t size() { return _devices.size(); }
            void refresh();
        private:
            void _attached_devices();

            container _devices;
    };
}