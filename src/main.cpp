#include <stdio.h>
#include <curl/curl.h>

#include "parser.h"

#include <iostream>

int main() {
	std::string res = request();
	std::cout << res << std::endl;
	
	return EXIT_SUCCESS;
}
