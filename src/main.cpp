#include <ctime>
#include <iostream>
#include <string>
#include <cmw-cmx-cpp/ProcessComponent.h>
#include <cmw-cmx-cpp/Component.h>

using namespace cmw::cmx;

int main(int argc, char *argv[])
{
    std::string instance_name;
    if (argc > 1)
    {
        instance_name = argv[1];
    } else {
        instance_name = "cmx_test_app";
    }

    ProcessComponent::update();

    ComponentPtr component = Component::create(instance_name);
    CmxInt64 test_counter = component->newInt64("test_counter");

    std::cout << "Enter loop" << std::endl;
    int i = 0;
    while (true)
    {
        for (int i = 0; i < 100; i++)
        {
            test_counter = i;
            ProcessComponent::update();
            usleep(1000000);
            if (i % 10 == 0)
                std::cout << i << std::endl;
        }
    }
}
