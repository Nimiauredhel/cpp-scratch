#include "player.hpp"
#include "transform.hpp"

#include <set>

static constexpr int POLLING_DELAY_MS = (32);
static constexpr int COOLDOWN_DELAY_MS = (32);

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

    static std::set<SDL_Keycode> key_up_set;

    key_up_set.clear();

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYUP:
                key_up_set.insert(event.key.keysym.sym);
                break;
            case SDL_QUIT:
            case SDL_APP_TERMINATING:
                latest_input_id = INPUT_QUIT;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_a:
                        latest_keycode = event.key.keysym.sym;
                        latest_input_id = INPUT_LEFT;
                        break;
                    case SDLK_w:
                        latest_keycode = event.key.keysym.sym;
                        latest_input_id = INPUT_UP;
                        break;
                    case SDLK_d:
                        latest_keycode = event.key.keysym.sym;
                        latest_input_id = INPUT_RIGHT;
                        break;
                    case SDLK_s:
                        latest_keycode = event.key.keysym.sym;
                        latest_input_id = INPUT_DOWN;
                        break;
                    case SDLK_q:
                        latest_keycode = event.key.keysym.sym;
                        latest_input_id = INPUT_QUIT;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    if (key_up_set.find(latest_keycode) != key_up_set.end())
    {
        latest_keycode = SDLK_UNKNOWN;
        latest_input_id = INPUT_NONE;
    }

    return latest_input_id;
}

bool player_is_initialized(void)
{
    return is_initialized;
}

int player_task(void *arg)
{
    std::cout << "Player task started." << std::endl;
    input_init();
    is_initialized = true;

    InputId last_input = INPUT_NONE;

    Transform *element = (Transform *)arg;

    while (!should_terminate)
    {
        SDL_Delay(POLLING_DELAY_MS);
        last_input = input_poll();

        switch(last_input)
        {
        case INPUT_LEFT:
            element->MovePosition(-1, 0);
            SDL_Delay(COOLDOWN_DELAY_MS);
            break;
        case INPUT_UP:
            element->MovePosition(0, -1);
            SDL_Delay(COOLDOWN_DELAY_MS);
            break;
        case INPUT_RIGHT:
            element->MovePosition(1, 0);
            SDL_Delay(COOLDOWN_DELAY_MS);
            break;
        case INPUT_DOWN:
            element->MovePosition(0, 1);
            SDL_Delay(COOLDOWN_DELAY_MS);
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
