/** Victor Wu
  CS373 - Project 1
  02/12/2015  **/

#include <iostream>
#include <fstream>
#include <string>
#include <list>

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
		//Checking for the special states
		for (int i = 0; i < 3; i++) {
			if (!getline(myFile, myString)) std::cerr << "Error reading line" << i << " of the file, please verify the content of the input file." << std::endl;
			std::size_t found = myString.find("state\t");
			if (found != std::string::npos) {
				myString = myString.substr(found+6);
				int x = 0;
				while (isdigit(myString[x])) x++; //x holds the length of wanted string
				x = stoi(myString.substr(0, ++x)); //x holds the value of the state
				myString = myString.substr(found+x);
				if (myString.find("start")) START_STATE = x;
				else if (myString.find("accept")) ACCEPT_STATE = x;
				else if (myString.find("reject")) REJECT_STATE = x;
				//!-- Under the assumption that input file will cover all three unique states in the first three lines (basically no duplicates) --!
			}
			else std::cerr << "There is an error with the input file: line" << i << " doesn't have \"state\t\" in it" << std::endl;
		}
		//Reading up transitions
		while(std::getline(myFile, myString)) {
			std::size_t found = myString.find("transition\t");
			if (found != std::string::npos) {
				States* newState = new States();

				myString = myString.substr(found+11);
				int x = 0;
				while (isdigit(myString[x])) x++; //x holds the length of wanted string
				newState->q = stoi(myString.substr(0, ++x));
				myString = myString.substr(x);

				while (isdigit(myString[x])) x++; //x holds the length of wanted string
				newState->a = stoi(myString.substr(0, ++x));
				myString = myString.substr(x);

				while (isdigit(myString[x])) x++; //x holds the length of wanted string
				newState->r = stoi(myString.substr(0, ++x));
				myString = myString.substr(x);

				while (isdigit(myString[x])) x++; //x holds the length of wanted string
				newState->b = stoi(myString.substr(0, ++x));
				myString = myString.substr(x);

				while (isdigit(myString[x])) x++; //x holds the length of wanted string
				newState->x = (myString.substr(0, ++x).compare( "R")) ? States::RIGHT : States::LEFT;

				myStates.push_back(newState);
			}
			else std::cerr << "Thre was an error with the input file: one of the transitions did not match the format" << std::endl;
		}
		//Part 2
		myString = argv[2];
		char* myChar = &myString[0];
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
