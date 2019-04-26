#ifndef HCassociative_CJM
#define HCassociative_CJM
#include <vector>
#include <string>
#include <cassert>
#include <ctgmath>

class HCassociative {
	public:
		unsigned int blocks;
		unsigned int indexlen;
		unsigned int ways;
		unsigned int sets;
		std::vector<std::vector<bool>> valid;
		std::vector<std::vector<unsigned long>> tag;
		std::vector<std::vector<bool>> HC;
		long correct = 0;
		long overall = 0;
		HCassociative (unsigned int);
		void Cache(long);
		void Update(int, int);
		void Evict(long, int);
		std::string output();

}; 

HCassociative::HCassociative(unsigned int assoc) {
	this->blocks = 16384/32;	
	this->ways = assoc;
	this->sets = blocks/assoc;
	std::vector<unsigned long> temptag;
	std::vector<bool> tempvalid;
	std::vector<bool> tempHC;
	std::vector<unsigned long> tcopy;
	std::vector<bool> vcopy;
	std::vector<bool> hcopy;
	for (unsigned int i = 0; i < this->sets; i++) {
		for (unsigned int j = 0; j < this->ways; j++) {
			temptag.push_back(0);
			tempHC.push_back(false);
			tempvalid.push_back(false);
		}
		tcopy = temptag;
		vcopy = tempvalid;
		hcopy = tempHC;
		this->valid.push_back(tempvalid);
		this->tag.push_back(temptag);
		this->HC.push_back(tempHC);
		temptag.clear();
		tempvalid.clear();
		tempHC.clear();
	}
	this->indexlen = log2(sets);
}

void HCassociative::Cache(long addr) {
	long blockaddr = addr / 32;
	int index = blockaddr % this->sets;
	unsigned long ttemp = blockaddr >> indexlen;
	unsigned int counter = 0;
	for (unsigned int i = 0; i < this->ways; i++) {
		if(this->valid[index][i] && ttemp == this->tag[index][i]) {
			correct++;
			Update(index, i);
			break;
		} else if (this->valid[index][i]) {
			counter++;
		} else {
			this->valid[index][i] = true;
			this->tag[index][i] = ttemp;
			Update(index, i);
			break;
		}
	}
	if (counter == this->ways) {
		Evict(ttemp, index);
	}
	overall++;
}

void HCassociative::Update(int index, int way) {
	int temp = 0;
	int spot = 0;	
	std::vector<bool> rev;
	while (way > 0) {
		temp = way % 2;
		if (temp == 1) {
			rev.push_back(true);
		} else {
			rev.push_back(false);
		}
		way = way >> 1;
	}
	for (int i = rev.size()-1; i > -1; i--){
		if (rev[i]) {
			this->HC[index][spot] = true;
			spot = 2*spot+2;
		} else {
			this->HC[index][spot] = false;
			spot = 2*spot+1;
		}
	}
}

void HCassociative::Evict(long tag, int index) {
	unsigned int spot = 0;
	while (spot <= this->HC[index].size()) {
		if(this->HC[index][spot] == true) {
			spot = 2*spot+2;
		} else {
			spot = 2*spot+1;
		}
	}
	this->tag[index][spot] = tag;
	Update(index, spot);
}

std::string HCassociative::output() {
	std::string ret = "";
	ret.append(std::to_string(correct));
	ret.append(",");
	ret.append(std::to_string(overall));
	ret.append("; ");
	return ret;
}

#endif
