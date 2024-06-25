#include <stdlib.h>
#include <iostream>

#include "app.hpp"
#include "color.hpp"

int main(void)
{
	std::cout << "Starting... " << std::endl;
	
	App app(6789);
	app.run();
	
	return EXIT_SUCCESS;    
}
