/*
Name : Bishop Brandstetter
Course : CSC222
Project: Marathon Runners Structured Data
This program will read runner mileage data from a file then calculate each runners total,
and average mileage, and displays the results in a formatted table.
*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int max_runners = 50;
const int num_days = 7;

struct Runner
{
	string name;
	double miles[num_days];
	double total;
	double average;
};

int readrunnerData(Runner runners[]);
void calculatetotals(Runner runners[], int runnerCount);
void displayresults(Runner runners[], int runnerCount);

int main()
{

	Runner runners[max_runners];
	int runnerCount;

	runnerCount = readrunnerData(runners);
	calculatetotals(runners, runnerCount);
	displayresults(runners, runnerCount);


	return 0;
}




int readrunnerData(Runner runners[])
{
	int runnerCount = 0;

	ifstream inputFile;

	inputFile.open("runners.txt");

	if (!inputFile)
	{
		cout << "Error opening runners.txt" << endl;
		return 0;
	}
	while (runnerCount < max_runners && inputFile >> runners[runnerCount].name)
	{
		bool completeRecord = true;

		for (int day = 0; day < num_days; day++)
		{
			if (!(inputFile >> runners[runnerCount].miles[day]))
			{
				completeRecord = false;
				break;
			}
		}

		if (!completeRecord)
		{
			break;
		}

		runnerCount++;
	}
	inputFile.close();
	return runnerCount;
}

void calculatetotals(Runner runners[], int runnerCount)
{
	for (int runner = 0; runner < runnerCount; runner++)
	{
		runners[runner].total = 0;

		for (int day = 0; day < num_days; day++)
		{
			runners[runner].total += runners[runner].miles[day];
		}
		runners[runner].average = runners[runner].total / num_days;
	}
}

void displayresults(Runner runners[], int runnerCount)
{
	cout << fixed << setprecision(2);

	cout << left << setw(12) << "Runner";

	for (int day = 0;day < num_days;day++)
	{
		cout << setw(8) << "Day " + to_string(day + 1);
	}
	cout << setw(10) << "Total";
	cout << setw(10) << "Average";
	cout << endl;

	for (int runner = 0; runner < runnerCount; runner++)
	{
		cout << setw(12) << runners[runner].name;

		for (int day = 0; day < num_days;day++)
		{
			cout << setw(8) << runners[runner].miles[day];
		}
		cout << setw(10) << runners[runner].total;
		cout << setw(10) << runners[runner].average;
		cout << endl;
	}
}
