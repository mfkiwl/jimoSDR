#include "devices.h"
#include <iostream>
#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

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

        static void print_stream_args_info(std::vector<sdr_arg_info> infos,
            const uint32_t indent_spaces)
        {
            auto infos_size = infos.size();
            if(infos_size > 0)
            {
                string indent(indent_spaces - 4, ' ');
                string props_indent(indent_spaces, ' ');
                string range_indent(indent_spaces + 4, ' ');
                string options_indent = range_indent;
                for(size_t i = 0; i < infos_size; ++i)
                {
                    cout << indent << "RX Stream Args Info" << i << ":\n";
                    cout << props_indent << "key: " << infos[i].key() << '\n';
                    cout << props_indent << "value: " << infos[i].value() << '\n';
                    cout << props_indent << "name: " << infos[i].name() << '\n';
                    cout << props_indent << "description: "
                        << infos[i].description() << '\n';
                    cout << props_indent << "units: " << infos[i].units() << '\n';
                    cout << props_indent << "range:\n";
                    auto range = infos[i].range();
                    cout << range_indent << "minimum: " << range.minimum() << '\n';
                    cout << range_indent << "maximum: " << range.maximum() << '\n';
                    cout << range_indent << "step: " << range.step() << '\n';
                    cout << props_indent << "options: \n";
                    auto options = infos[i].options();
                    auto option_names = infos[i].option_names();
                    if(options.size() == 0)
                    {
                        cout << options_indent << "None\n";
                    }
                    else
                    {
                        for(size_t onum = 0; onum < options.size(); ++onum)
                        {
                            cout << props_indent << option_names[onum] << ": "
                                << options[onum] << '\n';
                        }
                    }
                }
            }
        }
};

int main()
{
    devices devs;
    cout << "Number of SDR devices found = " << devs.size() << '\n';
    for (auto& dev : devs)
    {
        cout << "SDR = " << (*dev)["label"] << '\n';    
        print::print_string_map(*dev, 4);
        cout << "    driver_key: " << dev->driver_key() << '\n';
        cout << "    hardware_key: " << dev->hardware_key() << '\n';
        cout << "    Hardware Info:\n";
        print::print_string_map(dev->hardware_info(), 8);
        cout << "    RX Frontend Mapping: " 
            << dev->frontend_mapping(device::direction::rx) << '\n';
        auto number_of_rx_channels = dev->number_of_channels(device::direction::rx);
        cout << "    Number of RX Channels: "
             << number_of_rx_channels << '\n';
        for(size_t channel = 0; channel <number_of_rx_channels; ++channel)
        {
            cout << "    RX Channel Info for Channel " << channel << ":\n";
            auto channel_info = dev->channel_info(device::direction::rx, channel);
            print::print_string_map(channel_info, 8);
            cout << (dev->full_duplex(device::direction::rx, channel)
                ? "        Full Duplex\n" : "        Half Duplex\n");
            const auto stream_formats = dev->stream_formats(device::direction::rx, channel);
            cout << "        Stream Formats:\n";
            print::print_strings(stream_formats, 12);
            auto [format, fullScale] = dev->native_stream_format(
                device::direction::rx, channel);
            cout << "        Native Stream Format:\n";
            cout << "            Format:" << format <<'\n';
            cout << "            Full scale: " << fullScale << '\n';
            print::print_stream_args_info(dev->stream_args_info(device::direction::rx,
                channel), 12);
            cout << "        Sample Rates:\n";
            auto rates = dev->sample_rates(device::direction::rx, channel);
            for(auto rate : rates)
            {
                cout << "            " << rate << '\n';
            }
            cout << "        Current Sample Rate: " << dev->sample_rate(
                device::direction::rx, channel) << '\n';
            cout << "        Exercise device::sample_rate:\n";
            for(auto rate : rates)
            {
                cout << "            Setting sample rate to: " << rate;
                dev->sample_rate(device::direction::rx, channel, rate);
                cout << " Sample rate is now: " << dev->sample_rate(
                    device::direction::rx, channel) << '\n';
            }
            cout << "    GPIO Banks:\n";
            print::print_strings(dev->gpio_banks(), 8);

            cout << "    Register Interfaces:\n";
            print::print_strings(dev->register_interfaces(), 8);
         }
    }
    cout << "In next 5 seconds, add or remove receivers\n";
    usleep(5000000);
    devs.refresh();
    cout << "After refresh, number of devices = " << devs.size() << '\n';
    return EXIT_SUCCESS;
}