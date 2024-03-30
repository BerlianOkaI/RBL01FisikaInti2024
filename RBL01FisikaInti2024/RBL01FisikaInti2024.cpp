// RBL01FisikaInti2024.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Type_Unit.h"
#include "DataBase.h"

using namespace std;

INT dummyArray[3] = { 0, 0, 0 };
ReactParticle mySystem;
ReactParticle SystemResult;
void setup(void)
{
    dbParticles.initializeDatabase();
    ReactParticleInit(&mySystem);
    ReactParticleInit(&SystemResult);
}

int main()
{
    setup();
    // Change or add initial reaction particle in this section
    // Particle type can be seen in enum definition of particleClass in DataBase.h
    /* * * * * * * * * * * * * * * * * * * * * * */
    mySystem.ParticleCombination[Proton]    = 1;
    mySystem.ParticleCombination[Muon]      = 1;
    /* * * * * * * * * * * * * * * * * * * * * * */
    

    // This section will simulate and predict the result of reaction
    SIMRESULT totalMatch = FindReactionProduct(&mySystem, &SystemResult);
    if (totalMatch)
    {
        std::cout << "Total Match Result :\t" << totalMatch << std::endl;
    }
    else {
        std::cout << "There is no matching result" << std::endl;
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
