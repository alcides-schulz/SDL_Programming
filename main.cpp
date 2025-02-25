#include "SDL_Framework.h"
#include "UniverseProceduralGeneration/SDL_UniverseProceduralGeneration.h"
#include "SnowfallSimulation/SDL_Snowfall.h"
#include "ParticleSimulation/SDL_ParticleSimulation.h"
#include "WaveFunctionCollapse/SDL_WaveFunctionCollapse.h"
#include "Sand/SDL_Sand.h"
#include "RayCastingWalls/SDL_RayCastingWalls.h"

#include "TheNatureOfCode/Chapter01/Example_1_1.h"
#include "TheNatureOfCode/Chapter01/Example_1_2.h"

#include "TheNatureOfCode/Chapter02/Example_2_1.h"
#include "TheNatureOfCode/Chapter02/Example_2_2.h"
#include "TheNatureOfCode/Chapter02/Example_2_3.h"
#include "TheNatureOfCode/Chapter02/Example_2_4.h"

using namespace std;

// Miscellaneous
vector<SDL_Framework *> misc_menu;

// The nature of code book
vector<SDL_Framework *> noc_chapter01_menu;
vector<SDL_Framework *> noc_chapter02_menu;
SDL_Framework *GetInstanceExample_1_3();
SDL_Framework *GetInstanceExample_1_4();
SDL_Framework *GetInstanceExample_1_5();
SDL_Framework *GetInstanceExample_1_6();
SDL_Framework *GetInstanceExample_1_7();
SDL_Framework *GetInstanceExample_1_8();
SDL_Framework *GetInstanceExample_1_9();
SDL_Framework *GetInstanceExample_1_10();

void InitNatureOfCodeMenus()
{
    // chapter 01
    noc_chapter01_menu.push_back(new Example_1_1());
    noc_chapter01_menu.push_back(new Example_1_2());
    noc_chapter01_menu.push_back(GetInstanceExample_1_3());
    noc_chapter01_menu.push_back(GetInstanceExample_1_4());
    noc_chapter01_menu.push_back(GetInstanceExample_1_5());
    noc_chapter01_menu.push_back(GetInstanceExample_1_6());
    noc_chapter01_menu.push_back(GetInstanceExample_1_7());
    noc_chapter01_menu.push_back(GetInstanceExample_1_8());
    noc_chapter01_menu.push_back(GetInstanceExample_1_9());
    noc_chapter01_menu.push_back(GetInstanceExample_1_10());
    // chapter 02
    noc_chapter02_menu.push_back(new Example_2_1());
    noc_chapter02_menu.push_back(new Example_2_2());
    noc_chapter02_menu.push_back(new Example_2_3());
    noc_chapter02_menu.push_back(new Example_2_4());
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

void NatureOfCodeChapterMenu(vector<SDL_Framework *> chapter_menu)
{
    while (true) {
        cout << "Menu" << endl << endl;
        for (int i = 0; i < chapter_menu.size(); i++) {
            cout << "\t " << (char)('a' + i) << ". " << chapter_menu[i]->WindowTitle() << endl;
        }
        cout << endl << "\t x. Exit" << endl << endl << "--> ";
        string response;
        getline(cin, response);
        if (response.compare("x") == 0) {
            break;
        }
        for (int i = 0; i < chapter_menu.size(); i++) {
            string selection(1, ('a' + i));
            if (response.compare(selection) == 0) {
                if (chapter_menu[i]->Init()) {
                    chapter_menu[i]->Run();
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
        cout << endl << "\t a. Chapter 1 - Vectors";
        cout << endl << "\t b. Chapter 2 - Forces";
        cout << endl << "\t x. Exit" << endl << endl << "--> ";
        string response;
        getline(cin, response);
        if (response.compare("x") == 0) {
            break;
        }
        if (response.compare("a") == 0) {
            NatureOfCodeChapterMenu(noc_chapter01_menu);
            continue;
        }
        if (response.compare("b") == 0) {
            NatureOfCodeChapterMenu(noc_chapter02_menu);
            continue;
        }
    }
}

int main(int argc, char* argv[])
{
    InitMiscMenu();
    InitNatureOfCodeMenus();

    while (true) {
        cout << "Menu" << endl << endl;
        cout << "\t 0. The Nature of Code - book by Daniel Shiffman" << endl << endl;
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
