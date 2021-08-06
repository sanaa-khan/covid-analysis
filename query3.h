#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <limits.h>
#include "Vector.cpp"
using namespace std;

struct countryData3 {
	string day;
	string country;
	string countryName;
	int confirmed;

	int dayNo;

	countryData3() {
		day = country = countryName = "";
		confirmed = -1;
	}

	bool operator < (const countryData3& obj) const {
		return this->confirmed < obj.confirmed;
	}
};

class query3 {
	string country;

	vector<countryData3> countries;

	int* figures;
	int size_;

	string sDate;
	string eDate;

	int* spread; // will hold the final spread
	int spreadSize;

public:
	query3() {
		cout << "Enter the name of a country: ";
		cin >> country;

		for (int i = 0; i < country.size(); i++)
			country[i] = tolower(country[i]); 

		size_ = 0;
		spreadSize = 0;

		figures = NULL;
		spread = NULL;
	}

	void fileRead() {

		ifstream in("WHO-COVID-19.csv");

		if (in) {
			countryData3 temp;
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
				getline(in, str, ',');

				getline(in, str, ',');
				temp.confirmed = stoi(str);

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

	void findLongestSpread() {

		countryData3* temp = new countryData3[size_];
		figures = new int[size_];

		for (int i = 0; i < size_; i++) {
			figures[i] = -1;
			temp[i].confirmed = 1;
		}

		int index1 = 0;

		while (index1 < size_) {

			int index2 = 0;
			int prev = countries[index1].confirmed;

			while (index2 < index1) {

				if (prev > countries[index2].confirmed) {

					int next = temp[index2].confirmed + 1;

					if (temp[index1].confirmed < next) {

						temp[index1].confirmed = next;
						figures[index1] = index2;
					}
				}

				index2++;
			}

			index1++;
		}

		int max = INT_MIN;
		int index;

		for (int i = 0; i < size_; i++) {
			if (temp[i].confirmed > max) {
				max = temp[i].confirmed;
				index = i;
			}
		}

	/*	for (int i = 0; i < size_; i++) {
			cout << figures[i] << " ";
		} 

		cout << endl; */

		bool flag = true;
		for (int i = 0; i < size_; i++) {
			int index = figures[i];
			
			if (index >= 0) {
			//	cout << countries[index].confirmed << " ";
				
				if (flag) {
					sDate = countries[index].day;
					flag = false;
				}
			}
		}

	//	cout << countries[index].confirmed;
		eDate = countries[index].day;

		cout << endl;

		spread = new int[size_];

		while (index != -1) {
			spread[spreadSize] = countries[index].confirmed;
			spreadSize++;
			index = figures[index];
		}

		for (int i = 0; i < spreadSize / 2; i++) {
			int temp = spread[i];
			spread[i] = spread[spreadSize - 1 - i];
			spread[spreadSize - 1 - i] = temp;
		}

	/*	for (int i = 0; i < spreadSize; i++) {
			cout << spread[i] << " ";
		} */
	}

	void displayResults() {

		cout << "Longest spread period for " << country << ":\n";
		cout << "--------------------------------------------" << "\n";

		cout << "Starting date:\t" << sDate << endl;
		cout << "Ending date:\t" << eDate << endl;
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
			this->findLongestSpread();
			this->displayResults();
		}
	}
};
