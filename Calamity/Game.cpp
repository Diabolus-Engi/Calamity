#include "Game.h"
#include "BearLibTerminal.h"
#include <iostream>
#include "Group.h"

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
    Kingdom *human_k = new Kingdom("Humanity", Alignment::NEUTRAL);
    Character* human_r = new Character("King Harold", Alignment::NEUTRAL);
    human_k->ruler = human_r;
    player = human_r; // Set player control to human ruler
    region.entities.push_back(human_r);
    region.kingdoms.push_back(human_k);

    Group* human_p = new Group("Human Pioneers", Alignment::NEUTRAL, 1);
    human_p->commander = human_r;
    region.entities.push_back(human_p);

    // Undead Kingdom
    Kingdom *undead_k = new Kingdom("Undead", Alignment::CHAOTIC_EVIL);
    Character* undead_r = new Character("Lich King", Alignment::CHAOTIC_EVIL);
    undead_k->ruler = undead_r;
    region.kingdoms.push_back(undead_k);
    region.entities.push_back(undead_r);

    // Nature Kingdom
    Kingdom *nature_k = new Kingdom("Nature", Alignment::CHAOTIC_NEUTRAL);
    Character* nature_r = new Character("Gaia", Alignment::CHAOTIC_NEUTRAL);
    nature_k->ruler = nature_r;
    region.kingdoms.push_back(nature_k);
    region.entities.push_back(nature_r);

    // Create cursor
    // TODO: Center cursor
    cursor_pos = { 0, 0 };

    // Spawn starting settlement
    Settlement s = Settlement({ 16,16 });
    region.settlements.push_back(s);
}

void Game::Update()
{
    // Handle input
    if (terminal_has_input()) {
        switch (terminal_read()) {
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
        case TK_ESCAPE: //Quit
            game_state = GAME_STATE::CLOSING;
            break;
        case TK_K: // Print kingdom details
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
                    std::cout << "Name: " << g->name << " Size: " << g->size << " Commander: " << g->commander->name << std::endl;
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
	
}

void Game::Render()
{
    // Render all terrain for the region
    for (int x = 0; x < region.MAX_X; x++)
        for (int y = 0; y < region.MAX_Y; y++) {
            terminal_color(region.ter(x, y)->col);
            terminal_put(x,y,region.ter(x,y)->ch);
        }

    // Render settlements
    for (Settlement s : region.settlements) {
        
        terminal_put(s.pos.x, s.pos.y, 'H');
    }

    // Render all characters for region
    for (Entity * e : region.entities) {
        terminal_put(e->pos.x, e->pos.y, e->ch);
    }

    // Draw cursor
    terminal_put(cursor_pos.x, cursor_pos.y, cursor);

    terminal_refresh();
}


