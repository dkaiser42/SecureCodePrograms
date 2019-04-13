all				:	CreatureFight

CreatureFight	:	Creature.o CreatureFight.o
					g++ -o CreatureFight.exe Creature.o CreatureFight.o
				
Creature.o		:	Creature.cpp
					g++ -I ./ -c Creature.cpp
				
CreatureFight.o	:	CreatureFight.cpp
					g++ -I ./ -c CreatureFight.cpp
				
clean			:	CreatureFight.exe
					del *.o
					del CreatureFight.exe