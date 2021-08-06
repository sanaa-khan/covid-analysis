#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
using namespace std;

struct countryData4 {
	string day;
	string country;
	string countryName;
	int deaths;

	countryData4() {
		day = country = countryName = "";
		deaths = -1;
	}

	bool operator < (const countryData4& obj) const {
		return this->deaths < obj.deaths;
	}
};

class query4 {
	string country;

	vector<countryData4> countries;

	int size_;

	string sDate;
	string eDate;

	int* spread;
	int spreadSize;
	
public:
	query4() {
		cout << "Enter the name of a country: ";
		cin >> country;

		for (int i = 0; i < country.size(); i++)
			country[i] = tolower(country[i]);

		size_ = 0;

		spread = NULL;
		spreadSize = 0;
	}

	void fileRead() {

		ifstream in("WHO-COVID-19.csv");

		if (in) {
			countryData4 temp;
			string str;

			getline(in, str); // reading the column headings of the csv

			while (!in.eof()) {

				getline(in, str, ',');
				temp.day = str;

				if (str.size() == 0)
					break;

				getline(in, str, ',');
				temp.country = str;

				// special case for reading "Bonaire, Sint Eustatius and Saba"
				// and "occupied Palestinian territory, including east Jerusalem"
				// as they have a comma ',' in the string
				if (temp.country == "BQ" or temp.country == "PS") {
					getline(in, str, ',');
					temp.countryName = str;

					getline(in, str, ',');
					temp.countryName += ',';
					temp.countryName += str;
				}

				else {
					getline(in, str, ',');
					temp.countryName = str;
				}

				getline(in, str, ',');

				getline(in, str, ',');
				temp.deaths = stoi(str);

				getline(in, str, ',');
				getline(in, str, ',');
				getline(in, str, '\n');

				string str;

				for (int i = 0; i < temp.countryName.size(); i++)
					str += tolower(temp.countryName[i]);

				if (str == country and str != "undefined") {
					countries.push_back(temp);
					size_++;
				}
			}

			in.close();
		}
	}

	void findLongestDeathToll() {

		vector<countryData4>* allDeathTolls;
		allDeathTolls = new vector<countryData4>[size_]; // will contain all the subsequences

		allDeathTolls[0].push_back(countries[0]);

		int index1 = 1;

		while (index1 < size_)  {
			
			int index2 = 0;

			while (index2 < index1) {

				if (allDeathTolls[index2].size() > allDeathTolls[index1].size()) { // next subsequence becoming larger than current one

					if (countries[index2].deaths > countries[index1].deaths) { // checking the deaths at these two indexes
						allDeathTolls[index1] = allDeathTolls[index2];
					}
				}

				index2++;
			}

			allDeathTolls[index1].push_back(countries[index1]);

			index1++;
		}

		// finding the index of the longest death spread

		int max = allDeathTolls[0].size();
		int index = 0;

		for (int i = 1; i < size_; i++) {
			if (max < allDeathTolls[i].size()) {
				max = allDeathTolls[i].size();
				index = i;
			}
		} 

		// passing longest spread to the spread array

		spread = new int[allDeathTolls[index].size()];

		for (int i = 0; i < allDeathTolls[index].size(); i++) {
			spread[spreadSize] = allDeathTolls[index][i].deaths;
			spreadSize++;
		}

		cout << endl;
	}

	void displayResults() {

		cout << "Longest  daily death toll decrease period for " << country << ":\n";
		cout << "-------------------------------------------------------------" << "\n";

	//	cout << "Starting date:\t" << sDate << endl;
	//	cout << "Ending date:\t" << eDate << endl;
		cout << "Size:\t" << spreadSize << "\n";

		cout << "Values:\t[";

		for (int i = 0; i < spreadSize; i++) {
			cout << spread[i];

			if (i == spreadSize - 1)
				cout << "]\n";
			else
				cout << ", ";
		}
	}

	void runAll() {

		this->fileRead();

		if (countries.size() == 0)
			cout << "No data found for '" << country << "'\n";

		else {
			this->findLongestDeathToll();
			this->displayResults();
		}
	}
};