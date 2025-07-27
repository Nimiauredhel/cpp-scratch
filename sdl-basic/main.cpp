#include <iostream>
#include <chrono>
#include <thread>

#include "gfx.hpp"
#include "input.hpp"

static constexpr int DELAY_MS = (32);

int main(void)
{
    int counter = 0;

    std::cout << "Hello World!" << std::endl;

    gfx_window_init(10, 10, 32);
    input_init();

    GfxElement *test_element = gfx_create_element();
    test_element->SetTexture(gfx_get_texture_pptr(TEXTURE_HEAD));
    test_element->SetPosition(0, 0);

    InputId last_input = INPUT_NONE;

    while(last_input != INPUT_QUIT)
    {
        gfx_present();
        std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_MS));

        last_input = input_poll();

        switch(last_input)
        {
        case INPUT_LEFT:
            test_element->MovePosition(-1, 0);
            break;
        case INPUT_UP:
            test_element->MovePosition(0, -1);
            break;
        case INPUT_RIGHT:
            test_element->MovePosition(1, 0);
            break;
        case INPUT_DOWN:
            test_element->MovePosition(0, 1);
            break;
        case INPUT_NONE:
        case INPUT_QUIT:
        default:
          break;
        }
    }

    gfx_destroy_element(test_element);
    gfx_window_deinit();

    return 0;
}
