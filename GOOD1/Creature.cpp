
#include "Creature.h"

using namespace std;

Creature::Creature() {
    
}

Creature::Creature(string name, string desc, int life, int hit) {
    this->name = name;
    this->description = desc;
    this->lifePoints = life;
    this->hitPoints = hit;
}


void Creature::printCreatureDetails() {
    cout << "NAME:\t" << name << "\n";

    int length = description.length();
    cout << "DESCRIPTION:\n\t";
    bool breakLine = false;
    for(int i = 0; i < length; i++) {
        if((i != 0) && (i % 70 == 0))
            breakLine = true;
        if(breakLine && description[i] == ' ') {
            cout <<"\n\t";
            breakLine = false;
        }

        cout << description[i];
    }

    cout << "\n\n";



    cout << "LIFE POINTS:\t" << lifePoints << "\n";
    cout << "HIT POINTS:\t" << hitPoints << "\n\n";
}