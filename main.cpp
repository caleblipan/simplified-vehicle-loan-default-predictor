#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>

using std::cout;
using std::string;
using std::ifstream;
using std::vector;
using std::stringstream;

int main() {
	cout << "======================= DATASET ========================\n";
   
       	// Open up training data and parse each row	
    	ifstream trainingData("training.csv");
    	string line;
    	vector<vector<string> > parsedCsv;
    	vector<string> parsedRow;
    
    	while(getline(trainingData, line)) {
		parsedRow.clear();
		std::stringstream lineStream(line);
		string cell;
		while(getline(lineStream, cell, ',')) {
			parsedRow.push_back(cell);
		}

		parsedCsv.push_back(parsedRow);
    	}

	// Print the dataset
	cout << "ID\tCost\tEmployment\tTotal\tActive\tDefault?\n";
	for (auto row = parsedCsv.begin(); row != parsedCsv.end(); ++row) {
		for (auto col = row->begin(); col != row->end(); ++col) {
			cout << *col << "\t";
		}
	    	cout << "\n";
	}

	// Turn the 'Cost' variable to categorical data
        // Below $60000	
	// Between $60000 and $70000
	// Between $70000 and $80000
	// Above $80000
	
	// Find probabilities

    	return 0;
}
