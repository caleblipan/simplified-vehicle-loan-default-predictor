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

	// Find GINI(Employment)
	double salaried = 0;
	double selfEmployed = 0;
	for (int i = 0; i < 20; i++) {
		// Index 2 is employment type
		if (parsedCsv[i][2] == "Salaried")
			salaried++;
		else
			selfEmployed++;
	}

	double noDefaultGivenSalaried = 0;
	double defaultGivenSalaried = 0;
	double noDefaultGivenSelfEmployed = 0;
	double defaultGivenSelfEmployed = 0;
	for (int i = 0; i < 20; i++) {
		// Index 5 is default boolean
		if (parsedCsv[i][2] == "Salaried" && parsedCsv[i][5] == "0")
			noDefaultGivenSalaried++;
		else if (parsedCsv[i][2] == "Salaried" && parsedCsv[i][5] == "1")
			defaultGivenSalaried++;
		else if (parsedCsv[i][2] == "Self employed" && parsedCsv[i][5] == "0")
			noDefaultGivenSelfEmployed++;
		else if (parsedCsv[i][2] == "Self employed" && parsedCsv[i][5] == "1")
			defaultGivenSelfEmployed++;
	}
	
	cout << "\nP(noDefault|Salaried): " << (double)(noDefaultGivenSalaried/salaried) << "\n";
	cout << "P(default|Salaried): " << (double)(defaultGivenSalaried/salaried) << "\n";
	double giniSalaried = 1 - (pow((double)(noDefaultGivenSalaried/salaried), 2) + pow((double)(defaultGivenSalaried/salaried), 2));
	cout << "GINI(Salaried): " << giniSalaried << "\n";
	cout << "\nP(noDefault|SelfEmployed): " << (double)(noDefaultGivenSelfEmployed/selfEmployed) << "\n";
	cout << "P(default|SelfEmployed): " << (double)(defaultGivenSelfEmployed/selfEmployed) << "\n";
	double giniSelfEmployed = 1 - (pow((double)(noDefaultGivenSelfEmployed/selfEmployed), 2) + pow((double)(defaultGivenSelfEmployed/selfEmployed), 2));
	cout << "GINI(SelfEmployed): " << giniSelfEmployed << "\n";

	cout << "\nGINI(EmploymentType): " << giniSalaried * (double)(salaried/(salaried+selfEmployed)) + giniSelfEmployed * (double)(selfEmployed/(salaried+selfEmployed)) << "\n";

	// Turn the 'Cost' variable to categorical data
        // Below $60000	
	// Between $60000 and $70000
	// Between $70000 and $80000
	// Above $80000
	
	// Find probabilities

    	return 0;
}
