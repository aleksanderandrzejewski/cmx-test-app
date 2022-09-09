#include <ctime>
#include <iostream>
#include <cmw-cmx-cpp/ProcessComponent.h>
#include <cmw-cmx-cpp/Component.h>

using namespace cmw::cmx;

int main()
{
    ProcessComponent::update();

    ComponentPtr component = Component::create("stats");
    CmxInt64 metr_test = component->newInt64("test");

    std::cout << "Enter loop" << std::endl;
    int i=0;
    while (true)
    {
        for (int i = 0; i < 100; i++)
        {
            metr_test = i;  // update metric
            ProcessComponent::update(); // update process metrics
            usleep(1000000);
            if (i % 10 == 0) std::cout << i << std::endl;
        }
    }
}
