#include "input.hpp"
#include "gfx_element.hpp"

static constexpr int DELAY_MS = (16);

static bool is_initialized = false;

static void input_init(void)
{
    SDL_Init(SDL_INIT_EVENTS);
}

static InputId input_poll(void)
{
    static SDL_Event event;

    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            case SDL_APP_TERMINATING:
                return INPUT_QUIT;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_a:
                        return INPUT_LEFT;
                    case SDLK_w:
                        return INPUT_UP;
                    case SDLK_d:
                        return INPUT_RIGHT;
                    case SDLK_s:
                        return INPUT_DOWN;
                    case SDLK_q:
                        return INPUT_QUIT;
                }
                break;
            case SDL_KEYUP:
            default:
                break;
        }
    }

    return INPUT_NONE;
}

bool input_is_initialized(void)
{
    return is_initialized;
}

int input_task(void *arg)
{
    input_init();
    is_initialized = true;

    InputId last_input = INPUT_NONE;

    GfxElement *element = (GfxElement *)arg;

    while (!should_terminate)
    {
        SDL_Delay(DELAY_MS);
        last_input = input_poll();

        switch(last_input)
        {
        case INPUT_LEFT:
            element->MovePosition(-1, 0);
            break;
        case INPUT_UP:
            element->MovePosition(0, -1);
            break;
        case INPUT_RIGHT:
            element->MovePosition(1, 0);
            break;
        case INPUT_DOWN:
            element->MovePosition(0, 1);
            break;
        case INPUT_QUIT:
            should_terminate = true;
            break;
        case INPUT_NONE:
        default:
          break;
        }
    }

    return 0;
}
