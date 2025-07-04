#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class B_DistTree {
public:
	~B_DistTree(void);
	struct sePair_ {
		unsigned int start;
		unsigned int end;
		int way;
	};
	struct error_ {
		std::string msg;
		bool flag;
	};
	struct elem_ {
		unsigned int number;
		elem_* parent;
		unsigned int distToP;
		std::vector<elem_*> childs;
	};
	unsigned int stoi(std::string str);

	bool setFiles(std::string in, std::string out);
	bool fRead(void);
	bool fWrite(void);

	bool buldWay(elem_* elem, unsigned int* start, unsigned int* end,
			unsigned int n);
	bool sDist(sePair_* pair);
	bool main(void);

private:
	sePair_* sePairs;
	std::string inFile, outFile;
	std::map<int, elem_*> peaks;
	unsigned int* wayfrom, *wayto, loops, peaksSize, qElements, begin;
};

B_DistTree::~B_DistTree(void) {
	delete wayfrom;
	delete wayto;
	delete sePairs;
	peaks.clear();

	return;
}

unsigned int B_DistTree::stoi(std::string str) {
	unsigned int size = str.size(), number = 0;
	for (unsigned int i = 0; i < size; ++i) {
		number = number * 10 + str[i] - 48;
	}
	return number;
}

bool B_DistTree::setFiles(std::string in, std::string out) {
	inFile = in;
	outFile = out;
	if (inFile.empty())
		return false;
	if (outFile.empty())
		return false;
	return true;
}

bool B_DistTree::fRead(void) {
	unsigned int number, child, dist = 0;
	std::string str;
	std::ifstream in(inFile.c_str());
	if (in == NULL)
		return false;

	if (!(in >> number)) {
		peaksSize = 0;
		return true;
	} else
		qElements = number;

	if (!(in >> number) || !(in >> child) || !(in >> dist)) {
		peaksSize = 0;
		return false;
	}
	begin = number;
	peaks[number] = new elem_;
	peaks[number]->number = number;
	peaks[number]->parent = NULL;
	peaks[number]->distToP = 0;

	peaks[child] = new elem_;
	peaks[child]->number = child;
	peaks[child]->parent = peaks[number];
	peaks[child]->distToP = dist;
	peaks[number]->childs.push_back(peaks[child]);
	for (unsigned int i = 0; i < qElements - 2; ++i) {
		if (!(in >> number) || !(in >> child) || !(in >> dist))
			return false;
		peaks[child] = new elem_;
		peaks[child]->number = child;
		peaks[child]->parent = peaks[number];
		peaks[child]->distToP = dist;
		peaks[number]->childs.push_back(peaks[child]);
	}

	peaksSize = peaks.size();
	if (!(in >> loops))
		return false;
	sePairs = new sePair_[loops];
	for (unsigned int i = 0; i < loops; ++i) {
		if (!(in >> sePairs[i].start) || !(in >> sePairs[i].end)) {
			loops = 0;
			return false;
		}
	}

	return true;
}

bool B_DistTree::fWrite(void) {
	std::ofstream out(outFile.c_str());
	if (out == NULL)
		return false;
	if (peaksSize) {
		for (unsigned int i = 0; i < loops; ++i) {
			if (sePairs[i].way != -1)
				out << sePairs[i].way;
			else
				out << "!element";

			if (i < loops - 1)
				out << std::endl;
		}
	}

	out.close();
	return true;
}

bool B_DistTree::buldWay(elem_* elem, unsigned int* start, unsigned int* end,
		unsigned int n) {

	if (*start != 0) {
		if (*start == elem->number) {
			*start = 0;
		}
		wayfrom[n] = elem->number;
	}
	if (*end != 0) {
		if (*end == elem->number) {
			*end = 0;
		}
		wayto[n] = elem->number;
	}
	if (!*start && !*end)
		return true;

	if (!elem->childs.size())
		return false;
	for (int i = 0; i < (int) elem->childs.size(); ++i) {
		if (buldWay(elem->childs[i], start, end, n + 1))
			return true;
	}
	return false;
}

bool B_DistTree::sDist(sePair_* pair) {
	wayfrom = new unsigned int[qElements];
	wayto = new unsigned int[qElements];
	int i = 0, ii = 0;
	bool oneway = false;
	pair->way = 0;
	unsigned int sstart = pair->start, eend = pair->end;
	if (pair->start == pair->end) {
		pair->way = 0;
		return true;
	} else if (buldWay(peaks[begin], &sstart, &eend, 0)) {
		for (;;) {
			if (wayfrom[i] != wayto[i]) {
				ii = i;
				i = i - 1;
				break;
			}
			if ((wayfrom[i] == pair->start) || (wayto[i] == pair->end)) {
				ii = i + 1;
				oneway = true;
				break;
			}
			++i;
		}
		if (wayfrom[i] != pair->start || !oneway) {
			for (int n = ii; wayfrom[n]; ++n) {
				pair->way += peaks[wayfrom[n]]->distToP;
				if (peaks[wayfrom[n]]->number != pair->start) {
				} else
					break;
			}
		}
		if (wayto[i] != pair->end || !oneway) {
			for (int n = ii; wayto[n]; ++n) {
				pair->way += peaks[wayto[n]]->distToP;
				if (peaks[wayto[n]]->number != pair->end) {
				} else
					break;
			}
		}
	} else {
		pair->way = -1;
		return false;
	}
	return true;
}

bool B_DistTree::main(void) {
	if (!fRead())
		return false;
	if (peaksSize) {
		for (unsigned int i = 0; i < loops; ++i) {
			if (!sDist(&sePairs[i]))
				break;
		}
	}
	if (!fWrite())
		return false;
	return true;
}

int main(int argc, const char* argv[]) {
	B_DistTree disttree;
	std::string inFile, outFile;
	std::cout << "Data in file: ";
	std::cin >> inFile;
	std::cout << "Data out file: ";
	std::cin >> outFile;

	if (disttree.setFiles(inFile, outFile)) {
		disttree.main();
	}

	return 0;
}
