#include <CL/cl.hpp>
#include <iostream>
#include <chrono>
#include "WND.hpp"


using namespace std;

int main(int argc, char** argv)
{
    QApplication app(argc,argv);
    MainWindow wnd;
    wnd.show();
    /*using namespace cl;

    vector<Platform> all_platforms;
    Platform::get(&all_platforms);

    if(all_platforms.empty())
    {
        cout << "no platforms found" << endl;
    }
    else
    {
        for(auto& platform : all_platforms)
        {
            cout << platform.getInfo<CL_PLATFORM_NAME>() << ":" << endl;

            cout << endl;
            vector<Device> all_devices;
            platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
            if(all_devices.empty())
            {
                cout << "no devices found" << endl;
            }
            else
            {
                for (auto& device : all_devices)
                {
                    cout << device.getInfo<CL_DEVICE_NAME>() << endl;
                }
            }
            cout << endl;
        }
    }
    */
    return app.exec();
}