#include <iostream>

int main (int argc, char* argv[]) {
	std::string x = "asdf";
std::string* y = &x;

y+=9;
*y = 5;

std::cout << *y << std::endl;

return 0;
}
