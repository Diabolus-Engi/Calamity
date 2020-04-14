#include "Game.h"
#include "BearLibTerminal.h"
#include <iostream>
#include "Group.h"
#include "Character.h"

int Game::SCREEN_WIDTH = 32;
int Game::SCREEN_HEIGHT = 32;

Game::Game()
{
    game_state = GAME_STATE::RUNNING;

    // Create starting region
    region = Region();

    // ### WORLD BUILDING ### ///
    // 1. Create starting kingdoms
    // 2. Create ruler characters for kingdoms
    // 3. Create and spawn starting pioneers with rulers as commanders

    // Human Kingdom
    Kingdom *human_k = new Kingdom("Humanity", Alignment::NEUTRAL, "blue");
    Character* human_r = new Character("King Harold", Alignment::NEUTRAL, { 0,0 },human_k);
    human_k->ruler = human_r;
    player = human_r; // Set player control to human ruler
    region.entities.push_back(human_r);
    region.kingdoms.push_back(human_k);

    Group* human_p = new Group("Human Pioneers", Alignment::NEUTRAL, 1,human_k);
    human_p->commander = human_r;
    region.entities.push_back(human_p);

    // Undead Kingdom
    Kingdom *undead_k = new Kingdom("Undead", Alignment::CHAOTIC_EVIL, "grey");
    Character* undead_r = new Character("Lich King", Alignment::CHAOTIC_EVIL, { 0,0 },undead_k);
    undead_k->ruler = undead_r;
    region.kingdoms.push_back(undead_k);
    region.entities.push_back(undead_r);

    // Nature Kingdom
    Kingdom *nature_k = new Kingdom("Nature", Alignment::CHAOTIC_NEUTRAL, "green");
    Character* nature_r = new Character("Gaia", Alignment::CHAOTIC_NEUTRAL, { 0,0 },nature_k);
    nature_k->ruler = nature_r;
    region.kingdoms.push_back(nature_k);
    region.entities.push_back(nature_r);

    camera = Camera(0, 0);
    cursor_pos = { SCREEN_WIDTH/2, SCREEN_HEIGHT/2 };
  
    // Spawn starting settlement
    Settlement s = Settlement({ 16,16 });
    region.settlements.push_back(s);
}

Point2D Game::screen_to_world(int x, int y)
{
    return Point2D{ x - camera.pos.x, y - camera.pos.y };
}

Point2D Game::screen_to_world(Point2D xy)
{
    return screen_to_world(xy.x,xy.y);
}

bool Game::Update()
{
    // Handle input
    if (terminal_has_input()) {
        int mouse_x = terminal_state(TK_MOUSE_X);
        int mouse_y = terminal_state(TK_MOUSE_Y);

        switch (terminal_read()) {
        case TK_ENTER:
        case TK_MOUSE_LEFT: {
            switch (terminal_state(TK_MOUSE_CLICKS)) {
            case 0:
            case 1: //Single
                // Find all units on tile
                for (Entity *e : region.entities) {
                    if (e->pos.x == (cursor_pos.x - camera.pos.x) && e->pos.y == (cursor_pos.y - camera.pos.y) && e != selected_entity) {
                        selected_entity = e;
                        break;
                    }
                }

                // Select tile

                break;
            case 2: //Double
                //TODO: Select all visible units of same type, ie military.
                break;
            default:
                break;
            }
        }
            break;
        case TK_MOUSE_RIGHT: {
            //  Move sleected entity
            if (selected_entity != nullptr) {
                Point2D pos = screen_to_world(cursor_pos);

                selected_entity->pos = pos;
            }
        }
            break;
        case TK_RESIZED:
            SCREEN_WIDTH = terminal_state(TK_WIDTH);
            SCREEN_HEIGHT = terminal_state(TK_HEIGHT);
            break;
        case TK_MOUSE_MOVE: {
            // Mouse controls
            if (mouse_x != last_mouse_pos.x || mouse_y != last_mouse_pos.y) {
                cursor_pos.x = mouse_x;
                cursor_pos.y = mouse_y;
            }

            last_mouse_pos.x = mouse_x;
            last_mouse_pos.y = mouse_y;
        }
            break;
        case TK_KP_2:
        case TK_DOWN: 
            cursor_pos.y += 1;
            break;
        case TK_KP_4:
        case TK_LEFT: 
            cursor_pos.x -= 1;
            break;
        case TK_KP_6:
        case TK_RIGHT:
            cursor_pos.x += 1;
            break;
        case TK_KP_8:
        case TK_UP: 
            cursor_pos.y -= 1;
            break;
        case TK_CLOSE: //Quit game
        case TK_ESCAPE: 
            game_state = GAME_STATE::CLOSING;
            return false;
            break;
        case TK_K: 
            // Print kingdom details
            std::cout << "Total Kingdoms: " << region.kingdoms.size() << "\n";
            for (Kingdom * k : region.kingdoms) {
                Entity* e = k->ruler;
                Character* r = dynamic_cast<Character*>(e);
                std::cout << "Kingdom " << k->name << " Ruler GUID: " << e->id.guid << " Ruler: " << r->name << std::endl;
            }

            // Print entities
            for (Entity* e : region.entities) {
                Group* g = dynamic_cast<Group*>(e);
                if (g != NULL) {
                    std::cout << "Name: " << g->name << " Size: " << g->size << " Commander: " << g->commander->name << " Owner: " << g->owner->name << std::endl;
                }
                Character* c = dynamic_cast<Character*>(e);
                if (c != NULL) {
                    std::cout << "Name: " << c->name << " Owner: " << c->owner->name << std::endl;
                }
            }

            std::cout << "Player name: " << reinterpret_cast<Character*>(player)->name << "\n";
            break;

        // End turn
        case TK_SPACE:
        case TK_COMMA:

            break;
        default:
            break;
        }
    }

    // Camera controls
    // TODO: Restrict camera to region dimensions
    const int scroll_edgedist = 1;

    if (cursor_pos.x < scroll_edgedist || last_mouse_pos.x < scroll_edgedist) {
        camera.pos.x += 1;
    }

    if (cursor_pos.x >= SCREEN_WIDTH - scroll_edgedist || last_mouse_pos.x >= SCREEN_WIDTH - scroll_edgedist) {
        camera.pos.x -= 1;
    }

    if (cursor_pos.y < scroll_edgedist || last_mouse_pos.y < scroll_edgedist) {
        camera.pos.y += 1;
    }

    if (cursor_pos.y >= SCREEN_HEIGHT - scroll_edgedist || last_mouse_pos.y >= SCREEN_HEIGHT - scroll_edgedist) {
        camera.pos.y -= 1;
    }

    // clamp camera to region bounds

    if (camera.pos.x > 1)
        camera.pos.x = 1;

    if (camera.pos.y > 1)
        camera.pos.y = 1;

    if (camera.pos.x < -(region.MAX_X-SCREEN_WIDTH+1))
        camera.pos.x = -(region.MAX_X - SCREEN_WIDTH+1);

    if (camera.pos.y < -(region.MAX_Y - SCREEN_HEIGHT+1))
        camera.pos.y = -(region.MAX_Y - SCREEN_HEIGHT+1);

    return true;
}

void Game::Render()
{
    terminal_clear();
    int offset_x = camera.pos.x;
    int offset_y = camera.pos.y;

    const color_t col_void = color_from_name("black");
    const color_t col_placeholder = color_from_name("yellow");

    terminal_bkcolor(col_void);
    terminal_color(col_void);

    // Render all terrain for the region
    for (int x = 0; x < region.MAX_X; x++)
        for (int y = 0; y < region.MAX_Y; y++) {
            terminal_color(color_from_name(region.ter(x, y)->col_s));
            terminal_bkcolor(color_from_name(region.ter(x, y)->bkcol_s));
            terminal_put(x + offset_x,y + offset_y,region.ter(x,y)->ch);
        }


    // Render settlements
    for (Settlement s : region.settlements) {
        terminal_color(col_placeholder);
        terminal_put(s.pos.x + offset_x, s.pos.y + offset_y, 'H');
    }

    // Render all characters for region
    for (Entity * e : region.entities) {
        terminal_color(color_from_name(e->owner->col_s));
        terminal_put(e->pos.x + offset_x, e->pos.y + offset_y, e->ch);
    }

    // Draw cursor
    terminal_color(color_from_name(player->owner->col_s));
    terminal_put(cursor_pos.x, cursor_pos.y, cursor);

    // Print UI
    if (selected_entity != nullptr) {
        Character* character = dynamic_cast<Character*>(selected_entity);
        std::string ui_info;

        if (character) {
            ui_info = "[offset=1,1][color=white][bkcolor=black]Unit: " + character->name + " / " + character->owner->name;
            
        }
        else {
            Group* group = dynamic_cast<Group*>(selected_entity);

            if (group) {
                ui_info = "[offset=1,1][color=white][bkcolor=black]Unit: " + group->name + " / " + group->owner->name;
            }
        }
        
        terminal_printf(0, 0, ui_info.c_str());
    }

    terminal_bkcolor(col_void);
    terminal_color(col_void);

    terminal_refresh();
}


