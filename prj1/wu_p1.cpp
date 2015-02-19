/** Victor Wu
  CS373 - Project 1
  02/12/2015  **/

#include <iostream>
#include <fstream>
#include <string.h>
#include <list>
#include <stdio.h>
#include <sstream>

struct States {
	int q, r;
	char a, b;
	enum X { LEFT, RIGHT } x;

	bool operator==(const char &s) const;
};

bool States::operator==(const char &s) const {return a == s;}

inline int verify (std::string *myString, char* c) {
	if ((c >= &(*myString)[0]) && (c <= &myString->back())) return 1;
	else { std::cout << "\tBOUND"; return 0;}
}

int main(int argc, char* argv[]) {
	std::ifstream myFile;
	int START_STATE, ACCEPT_STATE, REJECT_STATE;
	std::list<States*> myStates;

	if (argc == 2 && ((strcmp(argv[1],"--help") == 0) || (strcmp(argv[1], "-h") == 0))) std::cout << "Usage: [program] <file1> <file2> \n Files:\n\tfile1: Definition of simulated Turing machine\n\tString: to simulate Turing machine" << std::endl;
	else if (argc == 3) {
		myFile.open(argv[1]);
		//Part 1
		std::string myString;
		//Checking for the special states, working with flexibility for varying states (rather than fixed three)
		std::stringstream ss;
		while(std::getline(myFile, myString)) {
		ss.clear();
		ss.str("");
		ss << myString;	
		std::getline(ss, myString, '\t');
//std::cout << "DEBUG:\t" << ss << "\t" << myString;
			if (myString.find("transition") != std::string::npos) {
				States* newState = new States();
				std::getline(ss, myString, '\t');
				newState->q = stoi(myString);
				std::getline(ss, myString, '\t');
				newState->a = myString[0];
				std::getline(ss, myString, '\t');
				newState->r = stoi(myString);;
				std::getline(ss, myString, '\t');
				newState->b = myString[0];	
				std::getline(ss, myString, '\t');
				char LR = myString[0];
				newState->x = (LR == 'L') ? States::LEFT : States::RIGHT;
				
				myStates.push_back(newState);
			}
			else if(myString.find("state") != std::string::npos) {
				int x = 0;
				std::string y = "";
//std::cout << "DEBUG:ss:\t" << ss.str() << std::endl;		
				ss >> x;
				ss >> y;
//std::cout << "DEBUGss:\t" << ss.str() << std::endl;		
				if (y == "start")
					START_STATE = x;
				else if (y == "accept")
					ACCEPT_STATE = x;
				else if (y == "reject")
					REJECT_STATE = x;
				else
					std::cerr << "Error in input file: Invalid state" << std::endl;

			}
			else std::cerr << "Error in input file: Neither transition nor state found." << std::endl;

		}
		//Part 2
		myString = argv[2];	
		int currentState = ACCEPT_STATE;
		std::list<States*>::iterator it = myStates.begin();
		std::string::iterator itS=myString.begin();

			for (; it != myStates.end(); ++it) {
				//Check for Start State
				if ((*it)->q == START_STATE) {
						if (*itS == (*it)->a) {
							std::cout << (*it)->q;
							*itS = (*it)->b;
							if ((*it)->x == States::RIGHT) itS++;
							else itS--;
							verify(&myString, &*itS);
							goto Parsing;
						}
				}
			}
Parsing:	int loop = 1;
		//Under the assumption that it won't get stuck with foreign symbols out of recognizable language

		while (loop < 5000) {
			for(it = myStates.begin(); it != myStates.end(); ++it) {
				if ((*it)->q == currentState) {
				if ((*it)->q == ACCEPT_STATE) {
						std::cout << "\taccept" << std::endl;
						loop = 5000;
					}
				else if ((*it)->q == REJECT_STATE) {
						std::cout <<"\treject" << std::endl;
						loop = 5000;
					}
				if ((*it)->a == *itS) {
					std::cout << "->" << (*it)->q << std::endl;
					*itS = (*it)->b;
					if ((*it)->x == States::RIGHT) ++itS;
					else --itS;
					verify(&myString, &*itS);
				}
			}
			}
			++loop;

		}

	}
	else std::cerr << "Invalid arguments! Try running '--help' for more information" << std::endl;

	return 0;
}
