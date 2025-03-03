//-------------------------------------------------------------------------------------------------
//  SDL Programming menu
//-------------------------------------------------------------------------------------------------

#include "SDL_Framework.h"
#include "UniverseProceduralGeneration/SDL_UniverseProceduralGeneration.h"
#include "SnowfallSimulation/SDL_Snowfall.h"
#include "ParticleSimulation/SDL_ParticleSimulation.h"
#include "WaveFunctionCollapse/SDL_WaveFunctionCollapse.h"
#include "Sand/SDL_Sand.h"
#include "RayCastingWalls/SDL_RayCastingWalls.h"

using namespace std;

// Miscellaneous
vector<SDL_Framework *> misc_menu = {
    new SDL_UniverseProceduralGeneration(),
    new SDL_Snowfall(),
    new SDL_ParticleSimulation(),
    new SDL_WaveFunctionCollapse("Images\\Circuit"),
    new SDL_Sand(),
    new SDL_RayCastingWalls(),
};

int main(int argc, char* argv[])
{
    while (true) {
        cout << "Menu" << endl << endl;
        for (int i = 0; i < misc_menu.size(); i++) {
            cout << "\t " << (char)('a' + i) << ". " << misc_menu[i]->WindowTitle() << endl;
        }
        cout << endl << "\t x. Exit" << endl << endl << "--> ";
        string response;
        getline(cin, response);
        if (response.compare("x") == 0) {
            break;
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
