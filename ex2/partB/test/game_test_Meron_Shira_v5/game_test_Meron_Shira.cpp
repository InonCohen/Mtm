#include <iostream>
#include <iostream>
#include <fstream>
#include <cassert>

#include "../../Exceptions.h"
#include "../../Game.h"

using namespace mtm;

void test_basic_errors();
void test_rules();
void test_range();
void test_move();

int main()
{
    test_basic_errors();
    test_rules();
    test_range();
    test_move();
}

void test_basic_errors()
{
    std::cout << "------test_basic_errors------" << std::endl;
    Game g1(1, 1);

    // move from empty cell to same cell
    try
    {
        g1.move(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::CellEmpty &e)
    {
        std::cout << e.what() << std::endl;
    }
    // negative gridpoint src
    try
    {
        g1.move(GridPoint(-1, 0), GridPoint(0, 0));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    //  negative gridpoint dst
    try
    {
        g1.move(GridPoint(0, 0), GridPoint(-1, 0));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    //  CellEmpty vs. IllegalCell
    try
    {
        g1.move(GridPoint(0, 0), GridPoint(1, 0));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    // Attack from empty cell
    try
    {
        g1.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::CellEmpty &e)
    {
        std::cout << e.what() << std::endl;
    }
    // Attack from empty cell to out of bounds, CellEmpty vs. IllegalCell
    try
    {
        g1.attack(GridPoint(0, 0), GridPoint(0, 1));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    //zero health
    try
    {
        g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 0, 2, 4, 5));
    }
    catch (mtm::IllegalArgument &e)
    {
        std::cout << e.what() << std::endl;
    }
    //negative health
    try
    {
        g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, -5, 2, 4, 5));
    }
    catch (mtm::IllegalArgument &e)
    {
        std::cout << e.what() << std::endl;
    }
    //copy
    Game g2(g1);
    assert((&g1 == &g2) == false);

    //zero ammo, range and power (legal)
    try
    {
        g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 5, 0, 0, 0));
    }
    catch (mtm::IllegalArgument &e)
    {
        std::cout << e.what() << std::endl;
    }

    //checks if g2 content is the same as g1 (cell is occupied)
    try
    {
        g2.move(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::CellEmpty &e)
    {
        std::cout << e.what() << std::endl;
    }
    // moving to the same cell confirmed here: https://piazza.com/class/kltecxyt6h914w?cid=654
    try
    {
        g1.move(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::CellOccupied &e)
    {
        std::cout << e.what() << std::endl;
    }

    // checks if medic can attack itself (IllegalTarget comes before OutOfAmmo for medic, checked in Piazza https://piazza.com/class/kltecxyt6h914w?cid=718_f4)
    try
    {
        g1.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }
    // checks if medic can move to itself
    try
    {
        g1.move(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::CellOccupied &e)
    {
        std::cout << e.what() << std::endl;
    }
    //Medic moves to out of bounds
    try
    {
        g1.attack(GridPoint(0, 0), GridPoint(0, 1));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }

    //negative ammo
    try
    {
        g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 5, -1, 0, 0));
    }
    catch (mtm::IllegalArgument &e)
    {
        std::cout << e.what() << std::endl;
    }

    //negative range
    try
    {
        g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 5, 0, -1, 0));
    }
    catch (mtm::IllegalArgument &e)
    {
        std::cout << e.what() << std::endl;
    }

    //negative power
    try
    {
        g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 5, 0, 0, -1));
    }
    catch (mtm::IllegalArgument &e)
    {
        std::cout << e.what() << std::endl;
    }

    //cell occupied check
    try
    {
        g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 5, 0, 0, 1));
    }
    catch (mtm::CellOccupied &e)
    {
        std::cout << e.what() << std::endl;
    }
    //Adding Sniper
    try
    {
        g2.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::SNIPER, Team::CROSSFITTERS, 5, 0, 0, 1));
    }
    catch (mtm::CellOccupied &e)
    {
        std::cout << e.what() << std::endl;
    }
    //Sniper attacking itself
    try
    {
        g2.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }
    //Adding Soldier
    Game g3(1, 1);

    try
    {
        g3.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::SOLDIER, Team::CROSSFITTERS, 5, 0, 0, 1));
    }
    catch (mtm::CellOccupied &e)
    {
        std::cout << e.what() << std::endl;
    }

    //Soldier attacking itself (Out of ammo)
    try
    {
        g3.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }
    //Soldier attacking itself
    try
    {
        g3.reload(GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        g3.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }
    //Soldier shoots until out of ammo
    try
    {
        g3.attack(GridPoint(0, 0), GridPoint(0, 0));
        g3.attack(GridPoint(0, 0), GridPoint(0, 0));
        g3.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }

    //check assignment
    Game g4(2, 2);
    g4 = g3;
    // g4 Board becomes 1x1
    try
    {
        g4.addCharacter(GridPoint(1, 1), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 5, 2, 4, 5));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        g4.reload(GridPoint(1, 1));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    // Checks g4 is not the same as g3
    try
    {
        g4.reload(GridPoint(0, 0));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        g3.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        g4.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }

    mtm::Team winning_team = mtm::Team::CROSSFITTERS;
    assert(g1.isOver(&winning_team) == true);
    assert(winning_team == POWERLIFTERS);
    assert(g2.isOver(&winning_team) == true);
    assert(winning_team == CROSSFITTERS);
    assert(g3.isOver(&winning_team) == true);
    assert(winning_team == CROSSFITTERS);
    assert(g4.isOver(&winning_team) == true);
    assert(winning_team == CROSSFITTERS);
    Game g5(1, 1);
    assert(g5.isOver(&winning_team) == false);
    std::cout << "\ntest_basic_errors[Ok]\n\n";
}

void test_rules()
{
    std::cout << "------test_rules------" << std::endl;

    Game g1(2, 2);
    //check attacks
    std::cout << "\n"
              << g1;
    try
    {
        g1.addCharacter(GridPoint(1, 1), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 5, 2, 4, 5));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n" << g1 << "\n";


    try
    {
        g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 5, 2, 1, 5));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n" << g1 << "\n";
    try
    {
        g1.addCharacter(GridPoint(0, 1), Game::makeCharacter(CharacterType::MEDIC, Team::CROSSFITTERS, 10, 2, 0, 3));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n" << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 0), GridPoint(0, 1)); // MEDIC's health is damaged as follows: 10-->10 - 5 = 5
    }
    catch (mtm::OutOfRange &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n" << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 0), GridPoint(0, 0)); // MEDIC's health is damaged as follows: 5-->5 - ceil(5/2) = 2
    }
    catch (mtm::OutOfRange &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n" << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n" << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n" << g1 << "\n";

    try
    {
        g1.reload(GridPoint(0, 0));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        g1.attack(GridPoint(0, 0), GridPoint(0, 0));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n" << g1 << "\n";

    //checking sniper
    try
    {
        g1.addCharacter(GridPoint(1, 0), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 6, 2, 1, 5));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n" << g1 << "\n";
    try
    {
        g1.addCharacter(GridPoint(0, 1), Game::makeCharacter(CharacterType::SNIPER, Team::CROSSFITTERS, 6, 2, 2, 5));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n" << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 1), GridPoint(0, 0));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n" << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 1), GridPoint(0, 0));
    }
    catch (mtm::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n" << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 1), GridPoint(1, 0));
    }
    catch (mtm::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n" << g1 << "\n";
    try
    {
        g1.attack(GridPoint(1, 1), GridPoint(1, 0));
    }
    catch (mtm::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n" << g1 << "\n";
    try
    {
        g1.reload(GridPoint(0, 1));
    }
    catch (mtm::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n" << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 1), GridPoint(1, 1));
    }
    catch (mtm::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n" << g1 << "\n";
    mtm::Team winning_team = mtm::Team::CROSSFITTERS;
    assert(g1.isOver(&winning_team) == false);
    assert((winning_team == POWERLIFTERS) == false);
    try
    {
        g1.attack(GridPoint(0, 1), GridPoint(0, 1));
    }
    catch (mtm::OutOfRange &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n" << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 1), GridPoint(1, 0));
    }
    catch (mtm::OutOfRange &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n" << g1 << "\n";

    try
    {
        g1.attack(GridPoint(0, 1), GridPoint(1, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n" << g1 << "\n";

    try
    {
        g1.reload(GridPoint(0, 1));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n" << g1 << "\n";
    try
    {
        g1.attack(GridPoint(0, 1), GridPoint(1, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n" << g1 << "\n";
    //check if soldier can attack if not in the same line (he shouldn't)
    try
    {
        g1.addCharacter(GridPoint(1, 0), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 6, 8, 3, 5));
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n" << g1 << "\n";
    try
    {
        g1.attack(GridPoint(1, 0), GridPoint(0, 1));
    }
    catch (mtm::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n" << g1 << "\n";
    try
    {
        g1.attack(GridPoint(1, 0), GridPoint(0, 0));
        g1.attack(GridPoint(1, 0), GridPoint(1, 1));
        g1.attack(GridPoint(1, 0), GridPoint(0, 0));
    }
    catch (mtm::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\n" << g1 << "\n";

    assert(g1.isOver(&winning_team) == true);
    assert((winning_team == POWERLIFTERS) == true);

    g1.addCharacter(GridPoint(0, 1), Game::makeCharacter(CharacterType::SOLDIER, Team::CROSSFITTERS, 6, 0, 0, 5));
    std::cout << "\n" << g1 << "\n";

    try
    {
        g1.attack(GridPoint(0, 1), GridPoint(0, 0));
    }
    catch (mtm::OutOfRange &e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        g1.attack(GridPoint(0, 1), GridPoint(1, 0));
    }
    catch (mtm::OutOfRange &e)
    {
        std::cout << e.what() << std::endl;
    }
    g1.reload(GridPoint(0, 1));
    try
    {
        g1.attack(GridPoint(0, 1), GridPoint(1, 0));
    }
    catch (mtm::OutOfRange &e)
    {
        std::cout << e.what() << std::endl;
    }

    Game g2(2, 2);
    g2.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::SNIPER, Team::CROSSFITTERS, 6, 3, 2, 1));
    g2.addCharacter(GridPoint(1, 0), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 3, 0, 2, 5));
    g2.addCharacter(GridPoint(0, 1), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 6, 0, 2, 1));
    g2.attack(GridPoint(0, 0), GridPoint(1, 0));
    std::cout << "\n"
              << g2 << "\n";
    g2.attack(GridPoint(0, 0), GridPoint(1, 0));
    std::cout << "\n"
              << g2 << "\n";
    g2.attack(GridPoint(0, 1), GridPoint(1, 0));
    std::cout << "\n"
              << g2 << "\n";
    g2.attack(GridPoint(0, 0), GridPoint(1, 0));
    std::cout << "\n"
              << g2 << "\n";
    std::cout << "\ntest_rules[Ok]\n\n";
}

void test_range()
{
    std::cout << "------test_range------" << std::endl;
    Game g1(2, 1);
    //check attacks
    std::cout << "\n" << g1 << "\n";

    g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 1, 8, 3, 5));
    g1.addCharacter(GridPoint(1, 0), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 1, 0, 3, 5));

    // Medic heal check if out of ammo (shouldn't be) taking any ammo
    try
    {
        g1.attack(GridPoint(1, 0), GridPoint(0, 0));
        g1.attack(GridPoint(1, 0), GridPoint(0, 0));
        g1.attack(GridPoint(1, 0), GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo &e)
    {
        std::cout << e.what() << std::endl;
    }
    mtm::Team winning_team = mtm::Team::CROSSFITTERS;
    assert(g1.isOver(&winning_team) == true);
    assert((winning_team == POWERLIFTERS) == true);

    Game g2(5, 8);
    std::cout << "\n"
              << g2 << "\n";

    //check Soldier Attack is correct (Same as instructions)
    g2.addCharacter(GridPoint(2, 0), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 1, 8, 4, 10));
    std::cout << "\n"
              << g2 << "\n";
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (i != 2 || j != 0)
            {
                g2.addCharacter(GridPoint(i, j), Game::makeCharacter(CharacterType::SNIPER, Team::CROSSFITTERS, 10, 1, 1, 1));
            }
        }
    }
    std::cout << "\n"
              << g2 << "\n";
    try
    {
        g2.attack(GridPoint(2, 0), GridPoint(3, 1));
    }
    catch (mtm::IllegalTarget &e)
    {
        std::cout << e.what() << std::endl;
    }

    g2.attack(GridPoint(2, 0), GridPoint(2, 4));
    std::cout << "\n"
              << g2 << "\n";

    g2.attack(GridPoint(2, 0), GridPoint(2, 4));
    std::cout << "\n"
              << g2 << "\n";

    //check sniper attack range and 3rd time shot
    Game g3(7, 7);
    g3.addCharacter(GridPoint(3, 3), Game::makeCharacter(CharacterType::SNIPER, Team::POWERLIFTERS, 1, 72, 3, 1));
    std::cout << "\n"
              << g3 << "\n";

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (i != 3 || j != 3)
            {
                g3.addCharacter(GridPoint(i, j), Game::makeCharacter(CharacterType::MEDIC, Team::CROSSFITTERS, 4, 1, 1, 1));
            }
        }
    }
    Game g4(g3);

    std::cout << "\n"
              << g3 << "\n";

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (i != 3 || j != 3)
            {
                try
                {
                    g3.attack(GridPoint(3, 3), GridPoint(i, j));
                    g3.attack(GridPoint(3, 3), GridPoint(i, j));
                }
                catch (mtm::OutOfRange &e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
        }
    }
    std::cout << "\n"
              << g3 << "\n";

    //check 3rd shot
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (i != 3 || j != 3)
            {
                try
                {
                    g4.attack(GridPoint(3, 3), GridPoint(i, j));
                    g4.attack(GridPoint(3, 3), GridPoint(i, j));
                    g4.attack(GridPoint(3, 3), GridPoint(i, j));
                }
                catch (mtm::OutOfRange &e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
        }
    }

    std::cout << "\n"
              << g4 << "\n";
    try
    {
        g4.attack(GridPoint(3, 3), GridPoint(3, 3));
    }
    catch (mtm::OutOfRange &e)
    {
        std::cout << e.what() << std::endl;
    }

    Game g5(11, 11);
    std::cout << "\n"
              << g5 << "\n";

    //check Medic Attack is correct (Same as instructions)
    g5.addCharacter(GridPoint(5, 5), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 1, 49, 3, 10));
    std::cout << "\n"
              << g5 << "\n";
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            if (i != 5 || j != 5)
            {
                g5.addCharacter(GridPoint(i, j), Game::makeCharacter(CharacterType::SNIPER, Team::CROSSFITTERS, 10, 1, 1, 1));
            }
        }
    }
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            try
            {
                g5.attack(GridPoint(5, 5), GridPoint(i, j));
            }
            catch (mtm::OutOfRange &e)
            {
                std::cout << e.what() << std::endl;
            }
            catch (mtm::IllegalTarget &e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    std::cout << "\n"
              << g5 << "\n";

    std::cout << "\ntest_range[Ok]\n\n";
}

void test_move()
{
    std::cout << "------test_move------" << std::endl;
    //Soldier Movement
    Game g1(11, 11);
    std::cout << "\n" << g1 << "\n";
    g1.addCharacter(GridPoint(5, 5), Game::makeCharacter(CharacterType::SOLDIER, Team::CROSSFITTERS, 4, 1, 1, 1));
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            try
            {
                g1.move(GridPoint(5, 5), GridPoint(i, j));
                std::cout << "\n"
                          << g1 << "\n";
                g1.move(GridPoint(i, j), GridPoint(5, 5));
                std::cout << "\n"
                          << g1 << "\n";
            }
            catch (mtm::MoveTooFar &e)
            {
                std::cout << e.what() << std::endl;
            }
            catch (mtm::CellOccupied &e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }

    std::cout << "\n" << g1 << "\n";

    try
    {
        g1.move(GridPoint(5, 5), GridPoint(5, 8));
        g1.move(GridPoint(5, 5), GridPoint(5, 11));
    }
    catch (mtm::MoveTooFar &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (mtm::CellOccupied &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        g1.move(GridPoint(5, 8), GridPoint(8, 8));
        g1.move(GridPoint(8, 8), GridPoint(11, 8));
    }
    catch (mtm::MoveTooFar &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (mtm::CellOccupied &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        g1.move(GridPoint(8, 8), GridPoint(5, 8));
        g1.move(GridPoint(5, 8), GridPoint(2, 8));
        g1.move(GridPoint(2, 8), GridPoint(-1, 8));
    }
    catch (mtm::MoveTooFar &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (mtm::CellOccupied &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }

    //Medic Movement
    Game g2(11, 11);
    g2.addCharacter(GridPoint(5, 5), Game::makeCharacter(CharacterType::MEDIC, Team::CROSSFITTERS, 4, 1, 1, 1));
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            try
            {
                g2.move(GridPoint(5, 5), GridPoint(i, j));
                std::cout << "\n"
                          << g2 << "\n";
                g2.move(GridPoint(i, j), GridPoint(5, 5));
                std::cout << "\n"
                          << g2 << "\n";
            }
            catch (mtm::MoveTooFar &e)
            {
                std::cout << e.what() << std::endl;
            }
            catch (mtm::CellOccupied &e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }

    try
    {
        g2.move(GridPoint(5, 5), GridPoint(5, 10));
        g2.move(GridPoint(5, 10), GridPoint(5, 11));
    }
    catch (mtm::MoveTooFar &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (mtm::CellOccupied &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        g2.move(GridPoint(5, 10), GridPoint(10, 10));
        g2.move(GridPoint(10, 10), GridPoint(11, 10));
    }
    catch (mtm::MoveTooFar &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (mtm::CellOccupied &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }

    //Sniper Movement

    Game g3(11, 11);
    g3.addCharacter(GridPoint(5, 5), Game::makeCharacter(CharacterType::MEDIC, Team::CROSSFITTERS, 4, 1, 1, 1));
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            try
            {
                g3.move(GridPoint(5, 5), GridPoint(i, j));
                std::cout << "\n"
                          << g3 << "\n";
                g3.move(GridPoint(i, j), GridPoint(5, 5));
                std::cout << "\n"
                          << g3 << "\n";
            }
            catch (mtm::MoveTooFar &e)
            {
                std::cout << e.what() << std::endl;
            }
            catch (mtm::CellOccupied &e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }

    try
    {
        g3.move(GridPoint(5, 5), GridPoint(5, 9));
        g3.move(GridPoint(5, 9), GridPoint(5, 11));
    }
    catch (mtm::MoveTooFar &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (mtm::CellOccupied &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        g3.move(GridPoint(5, 9), GridPoint(9, 9));
        g3.move(GridPoint(9, 9), GridPoint(11, 9));
    }
    catch (mtm::MoveTooFar &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (mtm::CellOccupied &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (mtm::IllegalCell &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "\ntest_move[Ok]\n\n";
}