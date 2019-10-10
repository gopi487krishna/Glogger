#include <iostream>
#include "glogger.h"
#include<string>
int main()
{
	Glogger logger("test.txt",false );
	logger.log("Hello", "main()", &std::cout);
	logger.flush(std::cout );

	std::cin.get( );
	return true;

}

