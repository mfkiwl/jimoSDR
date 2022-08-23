#include "devices.h"
#include <iostream>

using namespace std;
using namespace soapy;

int main()
{
    std::vector<device> devs = devices::get_devices();
    cout << "Number of SDR devices found = " << devs.size() << '\n';
    for (auto& dev : devs)
    {
        cout << "Tuner = " << dev["tuner"] << '\n';
    }

    return EXIT_SUCCESS;
}