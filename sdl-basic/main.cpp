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

    GfxElement *test_element = gfx_create_element();
    test_element->SetTexture(gfx_get_texture_pptr(TEXTURE_HEAD));

    while(counter < 10)
    {
        test_element->SetPosition(counter, counter);
        gfx_present();
        counter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_MS));
    }

    gfx_destroy_element(test_element);
    gfx_window_deinit();

    return 0;
}
