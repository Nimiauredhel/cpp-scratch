#include <iostream>
#include <chrono>
#include <thread>

#include "gfx.hpp"

static constexpr int DELAY_MS = (250);

int main(void)
{
    int counter = 0;

    std::cout << "Hello World!" << std::endl;

    gfx_window_init(10, 10, 32);
    gfx_present();
    std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_MS));

    GfxElement *test_element = new GfxElement;

    while(counter < 10)
    {
        gfx_clear();
        test_element->SetPosition(counter, counter);
        test_element->Draw();
        gfx_present();
        counter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_MS));
    }

    delete(test_element);

    gfx_window_deinit();

    return 0;
}
