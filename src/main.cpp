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

    bool process_component = true;
    if (argc > 2)
    {
        if (std::string(argv[2]) == "process_component=false")
        {
            process_component = false;
        }
        else if (std::string(argv[2]) == "process_component=true")
        {
            process_component = true;
        }
        else
        {
            std::cout << "Invalid argument: " << argv[2] << std::endl;
            return 1;
        }
    }

    bool second_component = true;
    if (argc > 3)
    {
        if (std::string(argv[3]) == "second_component=false")
        {
            second_component = false;
        }
        else if (std::string(argv[3]) == "second_component=true")
        {
            second_component = true;
        }
        else
        {
            std::cout << "Invalid argument: " << argv[3] << std::endl;
            return 1;
        }
    }

    std::string metric_name = "sample_metric";
    if (argc > 4)
    {
        std::string metric_name_arg = std::string(argv[4]);
        if (metric_name_arg.size() > 0)
        {
            metric_name = metric_name_arg;
        }
    }

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distr(1,10);
    std::uniform_int_distribution<std::mt19937::result_type> distr2(-5,5);

    ComponentPtr component = Component::create(instance_name);
    CmxInt64 test_counter1 = component->newInt64("test_counter1");
    CmxInt64 test_counter2 = component->newInt64("test_counter2");
    CmxInt64 test_gauge1 = component->newInt64("test_gauge1");

    ComponentPtr component2 = Component::create(instance_name + "_second_component");
    CmxFloat64 test_gauge2 = component2->newFloat64("test_gauge2");
    CmxBool test_bool = component2->newBool("test_bool");

    ComponentPtr component3 = Component::create(instance_name + "metric_name_test");
    CmxFloat64 test_gauge3 = component3->newFloat64(metric_name);
    test_gauge3 = 0;

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

            float test_gauge2_tmp = test_gauge2 / distr(rng);
            if (test_gauge2_tmp < 0.1)
            {
                test_gauge2 = 100.0;
                test_bool = true;
            }
            else if (test_gauge2_tmp < 0.2)
            {
                test_gauge2 = 50.0;
                test_bool = false;
            }
            else
            {
                test_gauge2 = test_gauge2_tmp;
            }

            if (process_component)
            {
                ProcessComponent::update();
            }
            
            if (i % 10 == 0)
                std::cout << i << std::endl;

            usleep(1000000);
        }
    }
}
