#include <iostream>
#include <string>

using namespace std;

// Misc
void RunUniverseProceduralGeneration(void);
void RunSnowfallSimulation(void);
void RunParticles(void);
void RunWaveFunctionCollapse(void);

// The nature of code
void RunExample_1_1(void);
void RunExample_1_2(void);
void RunExample_1_3(void);
void RunExample_1_4(void);
void RunExample_1_5(void);
void RunExample_1_6(void);
void RunExample_1_7(void);
void RunExample_1_8(void);
void RunExample_1_9(void);

void nature_of_code_menu(void)
{
    while (true) {
        cout << "Menu" << endl << endl;
        cout << "\t1. Example 1.1: Bouncing ball with no vectors" << endl;
        cout << "\t2. Example 1.2: Bouncing ball with PVector" << endl;
        cout << "\t3. Example 1.3: Vector subtraction" << endl;
        cout << "\t4. Example 1.4: Multiplying a vector" << endl;
        cout << "\t5. Example 1.5: Vector magnitude" << endl;
        cout << "\t6. Example 1.6: Normalizing a vector" << endl;
        cout << "\t7. Example 1.7: Motion 101 (velocity)" << endl;
        cout << "\t8. Example 1.8: Motion 101 (velocity and constant accelerarion)" << endl;
        cout << "\t9. Example 1.9: Motion 101 (velocity and random accelerarion)" << endl;

        cout << endl << "\tx. Exit" << endl << endl << "--> ";

        string response;
        getline(cin, response);

        if (response.compare("x") == 0) {
            break;
        }

        if (response.compare("1") == 0) {
            RunExample_1_1();
            continue;
        }
        if (response.compare("2") == 0) {
            RunExample_1_2();
            continue;
        }
        if (response.compare("3") == 0) {
            RunExample_1_3();
            continue;
        }
        if (response.compare("4") == 0) {
            RunExample_1_4();
            continue;
        }
        if (response.compare("5") == 0) {
            RunExample_1_5();
            continue;
        }
        if (response.compare("6") == 0) {
            RunExample_1_6();
            continue;
        }
        if (response.compare("7") == 0) {
            RunExample_1_7();
            continue;
        }
        if (response.compare("8") == 0) {
            RunExample_1_8();
            continue;
        }
        if (response.compare("9") == 0) {
            RunExample_1_9();
            continue;
        }
    }
}

int main(int argc, char* argv[])
{
    while (true) {
        cout << "Menu" << endl << endl;
        cout << "\t 0. The nature of code - Daniel Shiffman" << endl;
        cout << endl;
        
        cout << "\t 1. Universe procedural generation" << endl;
        cout << "\t 2. Snowfall simulation" << endl;
        cout << "\t 3. Particle simulation" << endl;
        cout << "\t 4. Wave Function Collapse" << endl;
        cout << endl;

        cout << endl << "\t x. Exit" << endl << endl << "--> ";

        string response;
        getline(cin, response);

        if (response.compare("x") == 0) {
            break;
        }

        if (response.compare("0") == 0) {
            nature_of_code_menu();
            continue;
        }
        if (response.compare("1") == 0) {
            RunUniverseProceduralGeneration();
            continue;
        }
        if (response.compare("2") == 0) {
            RunSnowfallSimulation();
            continue;
        }
        if (response.compare("3") == 0) {
            RunParticles();
            continue;
        }
        if (response.compare("4") == 0) {
            RunWaveFunctionCollapse();
            continue;
        }
    }

    return 0;
}
