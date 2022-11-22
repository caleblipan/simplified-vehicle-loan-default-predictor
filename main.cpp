#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>

using std::cout;
using std::ifstream;
using std::iterator;
using std::max_element;
using std::stoi;
using std::string;
using std::stringstream;
using std::vector;

struct Tree
{
	string data;
	struct Tree *left;
	struct Tree *right;
};

struct Tree *newNode(string data)
{
	struct Tree *tree = new struct Tree();

	tree->data = data;

	tree->left = NULL;
	tree->right = NULL;

	return tree;
}

// Find GINI(AssetCost)
double calculateGiniAssetCost(vector<vector<string>> &parsedCsv)
{
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

	double giniAssetCost = giniBetween50kAnd65k * (double)(between50kAnd65k / (between50kAnd65k + between65kAnd90k)) + giniBetween65kAnd90k * (double)(between65kAnd90k / (between50kAnd65k + between65kAnd90k));
	cout << "\nGINI(AssetCost): " << giniAssetCost << "\n";

	return giniAssetCost;
}

// Find GINI(EmploymentType)
double calculateGiniEmploymentType(vector<vector<string>> &parsedCsv)
{
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

	double giniEmploymentType = giniSalaried * (double)(salaried / (salaried + selfEmployed)) + giniSelfEmployed * (double)(selfEmployed / (salaried + selfEmployed));
	cout << "\nGINI(EmploymentType): " << giniEmploymentType << "\n";

	return giniEmploymentType;
}

// Find GINI(TotalLoans)
double calculateGiniTotalLoans(vector<vector<string>> &parsedCsv)
{
	double between0to5 = 0;
	double between5to10 = 0;
	double between10to15 = 0;
	for (int i = 0; i < 20; i++)
	{
		std::stringstream lineStream(parsedCsv[i][3]);
		// Index 3 is total loans
		if (stoi(parsedCsv[i][3]) >= 0 && stoi(parsedCsv[i][3]) < 5)
			between0to5++;
		else if (stoi(parsedCsv[i][3]) >= 5 && stoi(parsedCsv[i][3]) < 10)
			between5to10++;
		else
			between10to15++;
	}

	double noDefaultGivenBetween0to5 = 0;
	double defaultGivenBetween0to5 = 0;
	double noDefaultGivenBetween5to10 = 0;
	double defaultGivenBetween5to10 = 0;
	double noDefaultGivenBetween10to15 = 0;
	double defaultGivenBetween10to15 = 0;
	for (int i = 0; i < 20; i++)
	{
		// Index 5 is default boolean
		if (stoi(parsedCsv[i][3]) >= 0 && stoi(parsedCsv[i][3]) < 5 && parsedCsv[i][5] == "0")
			noDefaultGivenBetween0to5++;
		else if (stoi(parsedCsv[i][3]) >= 0 && stoi(parsedCsv[i][3]) < 5 && parsedCsv[i][5] == "1")
			defaultGivenBetween0to5++;
		else if (stoi(parsedCsv[i][3]) >= 5 && stoi(parsedCsv[i][3]) < 10 && parsedCsv[i][5] == "0")
			noDefaultGivenBetween5to10++;
		else if (stoi(parsedCsv[i][3]) >= 5 && stoi(parsedCsv[i][3]) < 10 && parsedCsv[i][5] == "1")
			defaultGivenBetween5to10++;
		else if (stoi(parsedCsv[i][3]) >= 10 && stoi(parsedCsv[i][3]) < 15 && parsedCsv[i][5] == "0")
			noDefaultGivenBetween10to15++;
		else if (stoi(parsedCsv[i][3]) >= 10 && stoi(parsedCsv[i][3]) < 15 && parsedCsv[i][5] == "1")
			defaultGivenBetween10to15++;
	}

	cout << "\n================ TOTAL LOANS ======================";
	cout << "\nP(noDefault|0<x<5): " << (double)(noDefaultGivenBetween0to5 / between0to5) << "\n";
	cout << "P(default|0<x<5): " << (double)(defaultGivenBetween0to5 / between0to5) << "\n";
	double giniBetween0to5 = 1 - (pow((double)(noDefaultGivenBetween0to5 / between0to5), 2) + pow((double)(defaultGivenBetween0to5 / between0to5), 2));
	cout << "GINI(0<x<5): " << giniBetween0to5 << "\n";
	cout << "\nP(noDefault|5<x<10): " << (double)(noDefaultGivenBetween5to10 / between5to10) << "\n";
	cout << "P(default|5<x<10): " << (double)(defaultGivenBetween5to10 / between5to10) << "\n";
	double giniBetween5to10 = 1 - (pow((double)(noDefaultGivenBetween5to10 / between5to10), 2) + pow((double)(defaultGivenBetween5to10 / between5to10), 2));
	cout << "GINI(SelfEmployed): " << giniBetween5to10 << "\n";
	cout << "\nP(noDefault|10<x<15): " << (double)(noDefaultGivenBetween10to15 / between10to15) << "\n";
	cout << "P(default|10<x<15): " << (double)(defaultGivenBetween10to15 / between10to15) << "\n";
	double giniBetween10to15 = 1 - (pow((double)(noDefaultGivenBetween10to15 / between10to15), 2) + pow((double)(defaultGivenBetween0to5 / between0to5), 2));
	cout << "GINI(10<x<15): " << giniBetween10to15 << "\n";

	double giniTotalLoans = giniBetween0to5 * (double)(between0to5 / (between0to5 + between5to10 + between10to15)) + giniBetween5to10 * (double)(between5to10 / (between0to5 + between5to10 + between10to15)) + giniBetween10to15 * (double)(between10to15 / (between0to5 + between5to10 + between10to15));
	cout << "\nGINI(TotalLoan): " << giniTotalLoans << "\n";

	return giniTotalLoans;
}

// Find GINI(ActiveLoans)
double calculateGiniActiveLoans(vector<vector<string>> &parsedCsv)
{
	double between0to5 = 0;
	double between5to10 = 0;
	for (int i = 0; i < 20; i++)
	{
		std::stringstream lineStream(parsedCsv[i][3]);
		// Index 4 is active loans
		if (stoi(parsedCsv[i][4]) >= 0 && stoi(parsedCsv[i][4]) < 5)
			between0to5++;
		else if (stoi(parsedCsv[i][4]) >= 5 && stoi(parsedCsv[i][4]) < 10)
			between5to10++;
	}

	double noDefaultGivenBetween0to5 = 0;
	double defaultGivenBetween0to5 = 0;
	double noDefaultGivenBetween5to10 = 0;
	double defaultGivenBetween5to10 = 0;
	for (int i = 0; i < 20; i++)
	{
		// Index 5 is default boolean
		if (stoi(parsedCsv[i][4]) >= 0 && stoi(parsedCsv[i][4]) < 5 && parsedCsv[i][5] == "0")
			noDefaultGivenBetween0to5++;
		else if (stoi(parsedCsv[i][4]) >= 0 && stoi(parsedCsv[i][4]) < 5 && parsedCsv[i][5] == "1")
			defaultGivenBetween0to5++;
		else if (stoi(parsedCsv[i][4]) >= 5 && stoi(parsedCsv[i][4]) < 10 && parsedCsv[i][5] == "0")
			noDefaultGivenBetween5to10++;
		else if (stoi(parsedCsv[i][4]) >= 5 && stoi(parsedCsv[i][4]) < 10 && parsedCsv[i][5] == "1")
			defaultGivenBetween5to10++;
	}

	cout << "\n================ ACTIVE LOANS ======================";
	cout << "\nP(noDefault|0<x<5): " << (double)(noDefaultGivenBetween0to5 / between0to5) << "\n";
	cout << "P(default|0<x<5): " << (double)(defaultGivenBetween0to5 / between0to5) << "\n";
	double giniBetween0to5 = 1 - (pow((double)(noDefaultGivenBetween0to5 / between0to5), 2) + pow((double)(defaultGivenBetween0to5 / between0to5), 2));
	cout << "GINI(0<x<5): " << giniBetween0to5 << "\n";
	cout << "\nP(noDefault|5<x<10): " << (double)(noDefaultGivenBetween5to10 / between5to10) << "\n";
	cout << "P(default|5<x<10): " << (double)(defaultGivenBetween5to10 / between5to10) << "\n";
	double giniBetween5to10 = 1 - (pow((double)(noDefaultGivenBetween5to10 / between5to10), 2) + pow((double)(defaultGivenBetween5to10 / between5to10), 2));
	cout << "GINI(5<x<10): " << giniBetween5to10 << "\n";

	double giniActiveLoans = giniBetween0to5 * (double)(between0to5 / (between0to5 + between5to10)) + giniBetween5to10 * (double)(between5to10 / (between0to5 + between5to10));
	cout << "\nGINI(ActiveLoan): " << giniActiveLoans << "\n";

	return giniActiveLoans;
}

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

	// Calculate main GINI
	double noDefault = 0;
	double defaulted = 0;
	for (int i = 0; i < 20; i++)
	{
		// Index 2 is employment type
		if (stoi(parsedCsv[i][5]) == 0)
			noDefault++;
		else
			defaulted++;
	}

	cout << "\n================ DEFAULT RISK ======================\n";
	double giniDefaultRisk = 1 - (pow((double)(noDefault / (noDefault + defaulted)), 2) + pow((double)(noDefault / (noDefault + defaulted)), 2));
	cout << "GINI(DefaultRisk): " << giniDefaultRisk << "\n";

	// Run the GINI calculations
	double giniAssetCost = calculateGiniAssetCost(parsedCsv);
	double giniEmploymentType = calculateGiniEmploymentType(parsedCsv);
	double giniTotalLoans = calculateGiniTotalLoans(parsedCsv);
	double giniActiveLoans = calculateGiniActiveLoans(parsedCsv);

	// Find the highest information gain
	cout << "\n================ INFORMATION GAIN ======================\n";
	vector<double> infoGain;
	double infoGainAssetCost = giniDefaultRisk - giniAssetCost;
	infoGain.push_back(infoGainAssetCost);
	cout << "IG(AssetCost): " << infoGainAssetCost << "\n";

	double infoGainEmploymentType = giniDefaultRisk - giniEmploymentType;
	infoGain.push_back(infoGainEmploymentType);
	cout << "IG(EmploymentType): " << infoGainEmploymentType << "\n";

	double infoGainTotalLoans = giniDefaultRisk - giniTotalLoans;
	infoGain.push_back(infoGainTotalLoans);
	cout << "IG(TotalLoans): " << infoGainTotalLoans << "\n";

	double infoGainActiveLoans = giniDefaultRisk - giniActiveLoans;
	infoGain.push_back(infoGainActiveLoans);
	cout << "IG(ActiveLoans): " << infoGainActiveLoans << "\n\n";

	// Create root of the tree
	double largestInfoGain = *max_element(infoGain.begin(), infoGain.end());
	auto it = find(infoGain.begin(), infoGain.end(), largestInfoGain);
	int index = it - infoGain.begin();

	cout << "\nIndex: " << index << "\n";

	if (index == 0)
	{
		struct Tree *root = newNode("AssetCost");

		cout << "Decision Tree:"
			 << "\n";
		cout << "\t\t\t " << root->data << "\n";
		cout << "\t\t\t "
			 << "/ "
			 << "\\"
			 << "\n";
	}
	else if (index == 1)
	{
		struct Tree *root = newNode("EmploymentType");

		cout << "Decision Tree:"
			 << "\n";
		cout << "\t\t\t " << root->data << "\n";
		cout << "\t\t\t "
			 << "/ "
			 << "\\"
			 << "\n";
	}
	else if (index == 2)
	{
		struct Tree *root = newNode("TotalLoans");

		cout << "Decision Tree:"
			 << "\n";
		cout << "\t\t\t " << root->data << "\n";
		cout << "\t\t\t "
			 << "/ "
			 << "\\"
			 << "\n";
	}
	else
	{
		struct Tree *root = newNode("ActiveLoans");

		cout << "Decision Tree:"
			 << "\n";
		cout << "\t\t\t " << root->data << "\n";
		cout << "\t\t\t "
			 << "/ "
			 << "\\"
			 << "\n";
	}

	return 0;
}
