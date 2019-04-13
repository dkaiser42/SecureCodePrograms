#ifndef CREATURE_H
#define CREATURE_H
#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

class Creature {
    private:
        string name;
        string description;
        int lifePoints;
        int hitPoints;

    public:
        Creature();

        Creature(string, string, int, int);
        
        /*
            Function Name: printCreatureDetails()
            Parameters: none
            Returns: nothing (void)
            Purpose: Presents the detailed inforamtion regarding a creature.
        */
        void printCreatureDetails();

        //Creature getter functions
        string getCreatureName() {
            return this->name;
        }
        string getCreatureDesc() {
            return this->description;
        }
        int getCreatureLife() {
            return this->lifePoints;
        }
        int getCreatureHit() {
            return this->hitPoints;
        }

        //Creature setter functions
        void setCreatureName(string name) {
            this->name = name;
        }
        void setCreatureDesc(string desc) {
            this->description = desc;
        }
        void setCreatureLife(int life) {
            this->lifePoints = life;
        }
        void setCreatureHit(int hit) {
            this->hitPoints = hit; 
        }
};

#endif