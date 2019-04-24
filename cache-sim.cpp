#include <iostream>
#include <fstream>
#include <cstddef>
#include <string>
#include <sstream>
#include "Directmap.h"
#include "Setassociative.h"
#include "Testassociative.h"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Invalid number of arguments, needs 3." << std::endl;
	}
	
	else {	
		unsigned long long addr;
		std::string type;
		std::string line;
		Directmap * dmc1 = new Directmap(1024);
		Directmap * dmc2 = new Directmap(4096);
		Directmap * dmc3 = new Directmap(16384);
		Directmap * dmc4 = new Directmap(32768);
		Setassociative * set1 = new Setassociative(2);
		Setassociative * set2 = new Setassociative(4);
		Setassociative * set3 = new Setassociative(8);
		Setassociative * set4 = new Setassociative(16);
		Setassociative * full = new Setassociative(512);
		//Testassociative * t1 = new Testassociative(4);//

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
			set1->Cache(addr);
			set2->Cache(addr);
			set3->Cache(addr);
			set4->Cache(addr);
			full->Cache(addr);
			//t1->Cache(addr);//

			//Fill with other cache models as implemented//

		}
		
		outfile << dmc1->output() << dmc2->output() << dmc3->output() << dmc4->output() << std::endl;
		outfile << set1->output() << set2->output() << set3->output() << set4->output() << std::endl;
		outfile << full->output() << std::endl;
		//outfile << t1->output() << std::endl;//

			//Fill with other cache models as implemented//

		outfile.close();
	}
	return 0;
}
