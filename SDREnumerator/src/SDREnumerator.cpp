#include "devices.h"
#include <iostream>

using namespace std;
using namespace soapy;

class print
{
    public:
        static void print_string_map(const map<string, string>& string_map,
            const uint32_t indent_spaces)
        {
            string indent(indent_spaces, ' ');
            for(const auto& [key, value] : string_map)
            {
                cout << indent << key << ": " << value << '\n';
            }
        }

        static void print_strings(const vector<string>& strings,
            const uint32_t indent_spaces)
        {
            string indent(indent_spaces, ' ');
            if(strings.size() == 0)
            {
                cout << indent << "None\n";
            }
            else
            {
                for(const auto& str : strings)
                {
                    cout << indent << str << '\n';
                }
            }
        }
};

int main()
{
    std::vector<device> devs = devices::get_devices();
    cout << "Number of SDR devices found = " << devs.size() << '\n';
    for (auto& dev : devs)
    {
        cout << "SDR = " << dev["label"] << '\n';    
        print::print_string_map(dev, 4);
        cout << "    driver_key: " << dev.driver_key() << '\n';
        cout << "    hardware_key: " << dev.hardware_key() << '\n';
        cout << "    Hardware Info:\n";
        print::print_string_map(dev.hardware_info(), 8);
        cout << "    RX Frontend Mapping: " 
            << dev.frontend_mapping(device::direction::rx) << '\n';
        auto number_of_rx_channels = dev.number_of_channels(device::direction::rx);
        cout << "    Number of RX Channels: "
             << number_of_rx_channels << '\n';
        for(size_t channel = 0; channel <number_of_rx_channels; ++channel)
        {
            cout << "    RX Channel Info for Channel " << channel << ":\n";
            auto channel_info = dev.channel_info(device::direction::rx, channel);
            print::print_string_map(channel_info, 8);
            cout << (dev.full_duplex(device::direction::rx, channel)
                ? "        Full Duplex\n" : "        Half Duplex\n");
            const auto stream_formats = dev.stream_formats(device::direction::rx, channel);
            cout << "        Stream Formats:\n";
            print::print_strings(stream_formats, 12);
         }
    }

    return EXIT_SUCCESS;
}