#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using std::cout;
using std::ifstream;
using std::stoi;
using std::string;
using std::stringstream;
using std::vector;

int main()
{
	cout << "======================= DATASET ========================\n";

	// Open up training data and parse each row
	ifstream trainingData("training.csv");
	string line;
	vector<vector<string>> parsedCsv;
	vector<string> parsedRow;

	while (getline(trainingData, line))
	{
		parsedRow.clear();
		std::stringstream lineStream(line);
		string cell;
		while (getline(lineStream, cell, ','))
		{
			parsedRow.push_back(cell);
		}

		parsedCsv.push_back(parsedRow);
	}

	// Print the dataset
	cout << "ID\tCost\tEmployment\tTotal\tActive\tDefault?\n";
	for (auto row = parsedCsv.begin(); row != parsedCsv.end(); ++row)
	{
		for (auto col = row->begin(); col != row->end(); ++col)
		{
			cout << *col << "\t";
		}
		cout << "\n";
	}

	// Find GINI(Asset Cost)
	double between50kAnd65k = 0;
	double between65kAnd90k = 0;
	for (int i = 0; i < 20; i++)
	{
		std::stringstream lineStream(parsedCsv[i][1]);
		// Index 1 is asset cost
		if (stoi(parsedCsv[i][1]) >= 50000 && stoi(parsedCsv[i][1]) < 65000)
			between50kAnd65k++;
		else if (stoi(parsedCsv[i][1]) >= 65000 && stoi(parsedCsv[i][1]) < 90000)
			between65kAnd90k++;
	}

	double noDefaultGivenBetween50kAnd65k = 0;
	double defaultGivenBetween50kAnd65k = 0;
	double noDefaultGivenBetween65kAnd90k = 0;
	double defaultGivenBetween65kAnd90k = 0;
	for (int i = 0; i < 20; i++)
	{
		// Index 5 is default boolean
		if (stoi(parsedCsv[i][1]) >= 50000 && stoi(parsedCsv[i][1]) < 65000 && parsedCsv[i][5] == "0")
			noDefaultGivenBetween50kAnd65k++;
		else if (stoi(parsedCsv[i][1]) >= 50000 && stoi(parsedCsv[i][1]) < 65000 && parsedCsv[i][5] == "1")
			defaultGivenBetween50kAnd65k++;
		else if (stoi(parsedCsv[i][1]) >= 65000 && stoi(parsedCsv[i][1]) < 90000 && parsedCsv[i][5] == "0")
			noDefaultGivenBetween65kAnd90k++;
		else if (stoi(parsedCsv[i][1]) >= 65000 && stoi(parsedCsv[i][1]) < 90000 && parsedCsv[i][5] == "1")
			defaultGivenBetween65kAnd90k++;
	}

	cout << "\n================ ASSET COST ======================";
	cout << "\nP(noDefault|50k<x<65k): " << (double)(noDefaultGivenBetween50kAnd65k / between50kAnd65k) << "\n";
	cout << "P(default|50k<x<65k): " << (double)(defaultGivenBetween50kAnd65k / between50kAnd65k) << "\n";
	double giniBetween50kAnd65k = 1 - (pow((double)(noDefaultGivenBetween50kAnd65k / between50kAnd65k), 2) + pow((double)(defaultGivenBetween50kAnd65k / between50kAnd65k), 2));
	cout << "GINI(50k<x<65k): " << giniBetween50kAnd65k << "\n";

	cout << "\nP(noDefault|65k<x<90k): " << (double)(noDefaultGivenBetween65kAnd90k / between65kAnd90k) << "\n";
	cout << "P(default|65<x<90k): " << (double)(defaultGivenBetween65kAnd90k / between65kAnd90k) << "\n";
	double giniBetween65kAnd90k = 1 - (pow((double)(noDefaultGivenBetween65kAnd90k / between65kAnd90k), 2) + pow((double)(defaultGivenBetween65kAnd90k / between65kAnd90k), 2));
	cout << "GINI(65k<x<90k): " << giniBetween65kAnd90k << "\n";

	cout << "\nGINI(AssetCost): " << giniBetween50kAnd65k * (double)(between50kAnd65k / (between50kAnd65k + between65kAnd90k)) + giniBetween65kAnd90k * (double)(between65kAnd90k / (between50kAnd65k + between65kAnd90k)) << "\n";

	// Find GINI(Employment)
	double salaried = 0;
	double selfEmployed = 0;
	for (int i = 0; i < 20; i++)
	{
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
	for (int i = 0; i < 20; i++)
	{
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

	cout << "\n================ EMPLOYMENT TYPE ======================";
	cout << "\nP(noDefault|Salaried): " << (double)(noDefaultGivenSalaried / salaried) << "\n";
	cout << "P(default|Salaried): " << (double)(defaultGivenSalaried / salaried) << "\n";
	double giniSalaried = 1 - (pow((double)(noDefaultGivenSalaried / salaried), 2) + pow((double)(defaultGivenSalaried / salaried), 2));
	cout << "GINI(Salaried): " << giniSalaried << "\n";
	cout << "\nP(noDefault|SelfEmployed): " << (double)(noDefaultGivenSelfEmployed / selfEmployed) << "\n";
	cout << "P(default|SelfEmployed): " << (double)(defaultGivenSelfEmployed / selfEmployed) << "\n";
	double giniSelfEmployed = 1 - (pow((double)(noDefaultGivenSelfEmployed / selfEmployed), 2) + pow((double)(defaultGivenSelfEmployed / selfEmployed), 2));
	cout << "GINI(SelfEmployed): " << giniSelfEmployed << "\n";

	cout << "\nGINI(EmploymentType): " << giniSalaried * (double)(salaried / (salaried + selfEmployed)) + giniSelfEmployed * (double)(selfEmployed / (salaried + selfEmployed)) << "\n";

	// Turn the 'Cost' variable to categorical data
	// Below $60000
	// Between $60000 and $70000
	// Between $70000 and $80000
	// Above $80000

	// Find probabilities

	return 0;
}
