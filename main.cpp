#include "SDL_Framework.h"
#include "UniverseProceduralGeneration/SDL_UniverseProceduralGeneration.h"
#include "SnowfallSimulation/SDL_Snowfall.h"
#include "ParticleSimulation/SDL_ParticleSimulation.h"
#include "WaveFunctionCollapse/SDL_WaveFunctionCollapse.h"
#include "Sand/SDL_Sand.h"
#include "RayCastingWalls/SDL_RayCastingWalls.h"

using namespace std;

// Miscellaneous
vector<SDL_Framework *> misc_menu;

// The nature of code book
vector<SDL_Framework *> noc_menu1;
SDL_Framework *GetInstanceExample_1_1();
SDL_Framework *GetInstanceExample_1_2();
SDL_Framework *GetInstanceExample_1_3();
SDL_Framework *GetInstanceExample_1_4();
SDL_Framework *GetInstanceExample_1_5();
SDL_Framework *GetInstanceExample_1_6();
SDL_Framework *GetInstanceExample_1_7();
SDL_Framework *GetInstanceExample_1_8();
SDL_Framework *GetInstanceExample_1_9();
SDL_Framework *GetInstanceExample_1_10();

void InitNocMenu1()
{
    noc_menu1.clear();
    noc_menu1.push_back(GetInstanceExample_1_1());
    noc_menu1.push_back(GetInstanceExample_1_2());
    noc_menu1.push_back(GetInstanceExample_1_3());
    noc_menu1.push_back(GetInstanceExample_1_4());
    noc_menu1.push_back(GetInstanceExample_1_5());
    noc_menu1.push_back(GetInstanceExample_1_6());
    noc_menu1.push_back(GetInstanceExample_1_7());
    noc_menu1.push_back(GetInstanceExample_1_8());
    noc_menu1.push_back(GetInstanceExample_1_9());
    noc_menu1.push_back(GetInstanceExample_1_10());
}

void InitMiscMenu()
{
    misc_menu.clear();
    misc_menu.push_back(new SDL_UniverseProceduralGeneration());
    misc_menu.push_back(new SDL_Snowfall());
    misc_menu.push_back(new SDL_ParticleSimulation());
    misc_menu.push_back(new SDL_WaveFunctionCollapse("Images\\Circuit"));
    misc_menu.push_back(new SDL_Sand());
    misc_menu.push_back(new SDL_RayCastingWalls());
}

void NatureOfCodeChapter1Menu(void)
{
    InitNocMenu1();
    while (true) {
        cout << "Menu" << endl << endl;
        for (int i = 0; i < noc_menu1.size(); i++) {
            cout << "\t " << (char)('a' + i) << ". " << noc_menu1[i]->WindowTitle() << endl;
        }
        cout << endl << "\t x. Exit" << endl << endl << "--> ";
        string response;
        getline(cin, response);
        if (response.compare("x") == 0) {
            break;
        }
        for (int i = 0; i < noc_menu1.size(); i++) {
            string selection(1, ('a' + i));
            if (response.compare(selection) == 0) {
                if (noc_menu1[i]->Init()) {
                    noc_menu1[i]->Run();
                }
                break;
            }
        }
    }
}

void NatureOfCodeMenu(void)
{
    while (true) {
        cout << "Nature of Code Menu" << endl;
        cout << endl << "\t 1. Chapter 1 - Vectors";
        cout << endl << "\t 2. Chapter 2 - Forces";
        cout << endl << "\t x. Exit" << endl << endl << "--> ";
        string response;
        getline(cin, response);
        if (response.compare("x") == 0) {
            break;
        }
        if (response.compare("1") == 0) {
            NatureOfCodeChapter1Menu();
            continue;
        }
    }
}

int main(int argc, char* argv[])
{
    InitMiscMenu();
    while (true) {
        cout << "Menu" << endl << endl;
        cout << "\t 0. The Nature of Code book by Daniel Shiffman" << endl << endl;
        for (int i = 0; i < misc_menu.size(); i++) {
            cout << "\t " << (char)('a' + i) << ". " << misc_menu[i]->WindowTitle() << endl;
        }
        cout << endl << "\t x. Exit" << endl << endl << "--> ";
        string response;
        getline(cin, response);
        if (response.compare("x") == 0) {
            break;
        }
        if (response.compare("0") == 0) {
            NatureOfCodeMenu();
            continue;
        }
        for (int i = 0; i < misc_menu.size(); i++) {
            string selection(1, ('a' + i));
            if (response.compare(selection) == 0) {
                if (misc_menu[i]->Init()) {
                    misc_menu[i]->Run();
                }
                break;
            }
        }
    }
    return 0;
}
