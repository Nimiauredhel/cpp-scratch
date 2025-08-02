#include "player.hpp"
#include "transform.hpp"
#include "scene.hpp"

#include <set>

static constexpr int POLLING_DELAY_MS = (32);
static constexpr int COOLDOWN_DELAY_MS = (32);

static bool is_initialized = false;
static int32_t player_entity_id = -1;
static Transform player_transform_duplicate = { { 0, 0 }, { 1, 1 } };
static Sprite player_sprite_duplicate = { TEXTURE_HUMANOID2 };

static void player_check_collision(Transform &player_transform)
{
    int door_count = scene_get_current()->GetDoorCount();

    if (door_count > 0)
    {
        Door *door;

        for (int i = 0; i < door_count; i++)
        {
            door = scene_get_current()->GetDoorFromIdx(i);

            if (door->position.x == player_transform.position.x
                && door->position.y == player_transform.position.y
                && door->dest_scene_index < scene_get_count()
                && door->dest_door_index < scene_get_by_idx(door->dest_scene_index)->GetDoorCount())
            {
                if (scene_get_current() != scene_get_by_idx(door->dest_scene_index))
                {
                    gfx_set_focal_entity(-1);
                    scene_get_current()->DestroyEntity(player_entity_id);
                    player_entity_id = -1;
                    scene_set_current(door->dest_scene_index);
                }

                Vector2Int new_position = scene_get_current()->GetDoorFromIdx(door->dest_door_index)->position;
                player_transform_duplicate.position = { new_position.x, new_position.y };
                break;
            }
        }
    }
}

static void player_move(Transform &player_transform, int x_delta, int y_delta)
{
    Vector2Int new_position = { player_transform.position.x + x_delta, player_transform.position.y + y_delta };

    if (new_position.x < 0 || new_position.y < 0) return;
    Vector2Int scene_size = scene_get_current()->GetSize();
    if (new_position.x >= scene_size.x || new_position.y >= scene_size.y) return;
    if (scene_get_current()->GetTileTypeByCoord(new_position.x, new_position.y) != TILE_FLOOR) return;

    player_transform.position = { new_position.x, new_position.y };
    player_check_collision(player_transform);
}

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

    Transform *player_transform;
    Sprite *player_sprite;

    while (!should_terminate)
    {
        if (player_entity_id < 0)
        {
            player_entity_id = scene_get_current()->CreateEntity(COM_FLAG_TRANSFORM | COM_FLAG_SPRITE | COM_FLAG_CONTROL);
            player_transform = &scene_get_current()->GetTransforms()[player_entity_id];
            player_sprite = &scene_get_current()->GetSprites()[player_entity_id];
            *player_transform = player_transform_duplicate;
            *player_sprite = player_sprite_duplicate;
            gfx_set_focal_entity(player_entity_id);
        }

        SDL_Delay(POLLING_DELAY_MS);
        last_input = input_poll();

        switch(last_input)
        {
        case INPUT_LEFT:
            player_move(*player_transform, -1, 0);
            SDL_Delay(COOLDOWN_DELAY_MS);
            break;
        case INPUT_UP:
            player_move(*player_transform, 0, -1);
            SDL_Delay(COOLDOWN_DELAY_MS);
            break;
        case INPUT_RIGHT:
            player_move(*player_transform, 1, 0);
            SDL_Delay(COOLDOWN_DELAY_MS);
            break;
        case INPUT_DOWN:
            player_move(*player_transform, 0, 1);
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
