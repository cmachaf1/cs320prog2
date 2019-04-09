#include <iostream>
#include <fstream>
#include <cstddef>
#include <string>
#include <sstream>
#include "DirectMap.h"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Invalid number of arguments, needs 3." << std::endl;
	}
	
	else {	
		unsigned long long addr;
		std::string type;
		std::string line;
		DirectMap * dmc1 = new Directmap(1024);
		DirectMap * dmc2 = new Directmap(4096);
		DirectMap * dmc3 = new Directmap(16384);
		DirectMap * dmc4 = new Directmap(65536);

		//Fill with other cache models as implemented//
	
		std::ifstream infile(argv[1]);
		std::ofstream outfile(argv[2], std::ofstream::out);

		while (getline(infile,line)) { 
			std::stringstream str(line);
			str >> type >> std::hex >> addr;
			dmc1->Cache(addr);
			dmc2->Cache(addr);
			dmc3->Cache(addr);
			dmc4->Cache(addr);

			//Fill with other cache models as implemented//

		}
		
		outfile << dmc1->output() << dmc2->output() << dmc3->output() << dmc4->output();

			//Fill with other cache models as implemented//

		outfile.close();
	}
	return 0;
}
