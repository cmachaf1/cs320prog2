#ifndef DIRECTMAP_CJM
#define DIRECTMAP_CJM
#include <vector>
#include <string>
#include <cassert>
#include <ctgmath>

class Directmap {
	public:
		unsigned int blocks;
		unsigned int indexlen;
		long correct = 0;
		long overall = 0;
		std::vector<bool> valid;
		std::vector<unsigned long> tag;
		Directmap(unsigned int);
		void Cache(long);
		std::string output();
};

Directmap::Directmap(unsigned int csize) {
	this->blocks = csize / 32;
	for (unsigned int i = 0; i < blocks; i++) {
		this->valid.push_back(false);
		this->tag.push_back(0);
	}
	this->indexlen = log2(blocks);

}

void Directmap::Cache(long addr) {
	long blockaddr = addr / 32;
	int index = blockaddr % blocks;
	unsigned long ttemp = blockaddr >> indexlen;
	if (this->valid[index] && ttemp == this->tag[index]) {
		correct++;
	}
	else if (this->valid[index]) {
		this->tag[index] = ttemp;
	}
	else {
		this->valid[index] = true;		
		this->tag[index] = ttemp;
	}
	overall++;
}

std::string Directmap::output() {
	std::string ret = "";
	ret.append(std::to_string(correct));
	ret.append(",");
	ret.append(std::to_string(overall));
	ret.append("; ");
	return ret;
}
		
#endif
