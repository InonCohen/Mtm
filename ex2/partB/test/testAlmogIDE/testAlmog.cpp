#include <iostream>
#include <fstream>
#include <string>
#include "../../Exceptions.h"
#include "../../Game.h"

using namespace std;
using namespace mtm;

void doCreate(Game &game, fstream &from)
{
    // {t} {health} {ammo} {range} {power} {pos[0]} {pos[1]}
    char char_type;
    CharacterType type;
    int health, ammo, range, power, x_pos, y_pos;
    from >> char_type >> health >> ammo >> range >> power >> x_pos >> y_pos;
    if (tolower(char_type) == 's')
        type = SOLDIER;
    else if (tolower(char_type) == 'm')
        type = MEDIC;
    else
        type = SNIPER;
    Team team = isupper(char_type) ? POWERLIFTERS : CROSSFITTERS;
    shared_ptr<Character> temp = game.makeCharacter(type, team, health, ammo, range, power);
    game.addCharacter(GridPoint(y_pos, x_pos), temp);
}

void doAttack(Game& game , std::fstream &from )
{
    int x_src, y_src, x_dst, y_dst;
    from >> x_src >> y_src >> x_dst >> y_dst;
    game.attack(GridPoint(y_src, x_src), GridPoint(y_dst, x_dst));
}

void doMove(Game& game , std::fstream &from )
{
    int x_src, y_src, x_dst, y_dst;
    from >> x_src >> y_src >> x_dst >> y_dst;
    game.move(GridPoint(y_src, x_src), GridPoint(y_dst, x_dst));
}

void doReload(Game& game , std::fstream &from )
{
    int xpos, ypos;
    from >> xpos >> ypos;
    game.reload(GridPoint(ypos, xpos));
}

int main()
{
    std::string MTM_DIR = "/Users/ohadbenacot/CLionProjects/Mtm/";
    std::string TEST_DIR = "ex2/partB/test/testAlmogIDE/";
    fstream from(MTM_DIR + TEST_DIR + "game_input_0.txt",ios::in);
    fstream to(MTM_DIR + TEST_DIR + "myOutput.txt");
    if (!from){
        cout<<"src filepath isn't exist."<<endl;
    }
    if (!to){
        cout<<"dst filepath isn't exist."<<endl;
    }

    int width = 0;
    int height = 0;
    from >> width >> height;
    Game game(height, width);
    int line = 2; // we start from line 2, because first line is the width and height

        while (!from.eof()) {
            char command = 0;
            try {
                to << "executing line: " << line++ << endl;
                from >> command;
                switch (command) {
                    case 'c':
                        doCreate(game, from);
                        break;
                    case 'i':
                        to << "isOver: " << game.isOver(nullptr) << endl;
                        break;
                    case 'a':
                        doAttack(game , from );
                        break;
                    case 'm':
                        doMove(game , from );
                        break;
                    case 'r':
                        doReload(game, from );
                        break;
                    default:
                        break;
                }
                to << game << endl;
            }
            catch (mtm::Exception const &e) {
                to << e.what() << endl;
            }
        }
}
