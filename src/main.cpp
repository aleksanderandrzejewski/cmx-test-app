#include <ctime>
#include <iostream>
#include <string>
#include <cmw-cmx-cpp/ProcessComponent.h>
#include <cmw-cmx-cpp/Component.h>
#include <random>

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

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distr(1,10);
    std::uniform_int_distribution<std::mt19937::result_type> distr2(-5,5);

    ComponentPtr component = Component::create(instance_name);
    CmxInt64 test_counter1 = component->newInt64("test_counter1");
    CmxInt64 test_counter2 = component->newInt64("test_counter2");
    CmxInt64 test_gauge1 = component->newInt64("test_gauge1");

    std::cout << "Enter loop" << std::endl;
    int i = 0;
    while (true)
    {
        for (int i = 0; i < 100; i++)
        {
            test_counter1 = i;
            test_counter2 = test_counter2 + distr(rng);

            int test_gauge1_tmp = test_gauge1 + distr2(rng);
            if (test_gauge1_tmp <= 100 and test_gauge1_tmp>=0)
            {
                test_gauge1 = test_gauge1_tmp;
            }

            ProcessComponent::update();
            
            if (i % 10 == 0)
                std::cout << i << std::endl;

            usleep(1000000);
        }
    }
}
