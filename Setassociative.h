#ifndef SETASSOCIATIVE_CJM
#define SETASSOCIATIVE_CJM
#include <vector>
#include <string>
#include <cassert>
#include <ctgmath>

class Setassociative {
	public:
		unsigned int blocks;
		unsigned int indexlen;
		unsigned int ways;
		unsigned int sets;
		std::vector<std::vector<bool>> valid;
		std::vector<std::vector<unsigned long>> tag;
		std::vector<std::vector<unsigned long>> lru;
		long correct = 0;
		long overall = 0;
		Setassociative (unsigned int);
		void Cache(long);
		void Evict(long, int);
		std::string output();

}; 

Setassociative::Setassociative(unsigned int assoc) {
	this->blocks = 16384/32;	
	this->ways = assoc;
	this->sets = blocks/assoc;
	std::vector<unsigned long> temptag;
	std::vector<bool> tempvalid;
	std::vector<unsigned long> templru;
	std::vector<unsigned long> tcopy;
	std::vector<bool> vcopy;
	std::vector<unsigned long> lcopy;
	for (unsigned int i = 0; i < this->sets; i++) {
		for (unsigned int j = 0; j < this->ways; j++) {
			temptag.push_back(0);
			templru.push_back(0);
			tempvalid.push_back(false);
		}
		tcopy = temptag;
		vcopy = tempvalid;
		lcopy = templru;
		this->valid.push_back(tempvalid);
		this->tag.push_back(temptag);
		this->lru.push_back(templru);
		temptag.clear();
		tempvalid.clear();
		templru.clear();
	}
	this->indexlen = log2(sets);
}

void Setassociative::Cache(long addr) {
	long blockaddr = addr / 32;
	int index = blockaddr % this->sets;
	unsigned long ttemp = blockaddr >> indexlen;
	unsigned int counter = 0;
	for (unsigned int i = 0; i < this->ways; i++) {
		if(this->valid[index][i] && ttemp == this->tag[index][i]) {
			correct++;
			this->lru[index][i] = overall;
			break;
		} else if (this->valid[index][i]) {
			counter++;
		} else {
			this->valid[index][i] = true;
			this->tag[index][i] = ttemp;
			this->lru[index][i] = overall;
			break;
		}
	}
	if (counter == this->ways) {
		Evict(ttemp, index);
	}
	overall++;
}

void Setassociative::Evict(long tag, int index) {
	unsigned long min = this->lru[index][0];
	int replace = 0;
	for (unsigned int i = 1; i < this->ways; i++) {
		if (this->lru[index][i] < min) {
			min = this->lru[index][i];
			replace = i;
		}
	}
	this->tag[index][replace] = tag;
	this->lru[index][replace] = overall;
}
		

std::string Setassociative::output() {
	std::string ret = "";
	ret.append(std::to_string(correct));
	ret.append(",");
	ret.append(std::to_string(overall));
	ret.append("; ");
	return ret;
}

#endif
