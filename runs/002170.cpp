#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>

const int inf = std::numeric_limits<int>::max();

int main (int argc, char * const argv[]) {
	
	std::string line;
	// get vertices count
	getline(std::cin, line, '\n');
	int vertices = atoi(line.c_str());
	
	std::vector<std::vector<int> > weights(vertices, std::vector<int>(vertices, inf));
	
	for(int i = 0; i < vertices - 1; i++){
		getline(std::cin, line, '\n');
		int f, t, w;
		sscanf(line.c_str(), "%i %i %i\n", &f, &t, &w);
		weights[f - 1][t - 1] = w;
		weights[t - 1][f - 1] = w;
		weights[i][i] = 0;
	}
	weights[vertices - 1][vertices - 1] = 0;
	
	// execute Floyd-Warshall
	for(int k = 0; k < vertices; ++k) {
		for(int i = 0; i < vertices; ++i) {
			for(int j = 0; j < vertices; ++j) {
				if(weights[i][k] < inf){
					if(weights[k][j] < inf) {
						int sum = weights[i][k] + weights[k][j];
						weights[i][j] = weights[i][j] > sum ? sum : weights[i][j];
					}
				}
			}
		}
	}
	
	// get pairs count
	getline(std::cin, line, '\n');
	int pairs_count = atoi(line.c_str());
	
	// get pairs
	for(int i = 0; i < pairs_count; i++){
		getline(std::cin, line, '\n');
		int f, t;
		sscanf(line.c_str(), "%i %i\n", &f, &t);
		
		std::cout << weights[f - 1][t - 1] << std::endl;
		
	}
	
    return 0;
}
