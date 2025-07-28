#include "input.hpp"
#include "transform.hpp"

static constexpr int DELAY_MS = (32);

static bool is_initialized = false;

static void input_init(void)
{
    SDL_Init(SDL_INIT_EVENTS);
}

static InputId input_poll(void)
{
    static SDL_Event event;
    static SDL_Keycode latest_keycode = SDLK_UNKNOWN;
    static InputId latest_input_id = INPUT_NONE;

    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYUP:
                if (latest_keycode == event.key.keysym.sym)
                {
                    latest_keycode = SDLK_UNKNOWN;
                    latest_input_id = INPUT_NONE;
                }
                break;
            case SDL_QUIT:
            case SDL_APP_TERMINATING:
                latest_input_id = INPUT_QUIT;
                break;
            case SDL_KEYDOWN:
                latest_keycode = event.key.keysym.sym;
                switch(latest_keycode)
                {
                    case SDLK_a:
                        latest_input_id = INPUT_LEFT;
                        break;
                    case SDLK_w:
                        latest_input_id = INPUT_UP;
                        break;
                    case SDLK_d:
                        latest_input_id = INPUT_RIGHT;
                        break;
                    case SDLK_s:
                        latest_input_id = INPUT_DOWN;
                        break;
                    case SDLK_q:
                        latest_input_id = INPUT_QUIT;
                        break;
                    default:
                        latest_input_id = INPUT_NONE;
                        break;
                }
                break;
            default:
                break;
        }
    }

    return latest_input_id;
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

    Transform *element = (Transform *)arg;

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
