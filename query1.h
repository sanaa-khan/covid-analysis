#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
using namespace std;

struct countryData {
	string day;
	string country;
	string countryName;
	string region;
	int deaths;
	int cumDeaths;
	int confirmed;
	int cumConfirmed;

	countryData() {
		day = country = countryName = region = "";
		deaths = cumDeaths = confirmed = cumConfirmed = -1;
	}

	bool operator() (countryData const& c1, countryData const& c2) {
		return c1.cumConfirmed < c2.cumConfirmed;
	}

	bool operator < (const countryData& obj) const {
		return this->cumConfirmed < obj.cumConfirmed;
	}

	void display() {
		cout << day << "\t|\t"
			<< country << "\t|\t"
			<< region << "\t|\t"
			<< deaths << "\t|\t"
			<< cumDeaths << "\t\t|\t"
			<< confirmed << "\t\t|\t"
			<< cumConfirmed << "\t\t|\t"
			<< countryName << "\n";
	}
};

class query1 {
	string targetDate;
	priority_queue<countryData> countries;

public:

	query1() {
		cout << "Enter the target date (DD-MM-YY): ";
		cin >> targetDate;
	}

	void fileRead() {

		ifstream in("WHO-COVID-19.csv");

		if (in) {
			countryData temp;
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
				temp.region = str;

				getline(in, str, ',');
				temp.deaths = stoi(str);

				getline(in, str, ',');
				temp.cumDeaths = stoi(str);

				getline(in, str, ',');
				temp.confirmed = stoi(str);

				getline(in, str, '\n');
				temp.cumConfirmed = stoi(str);

				if (temp.countryName != "undefined") {
					if (temp.day == targetDate)
						countries.push(temp);
				}
			}

			in.close();
		}
	}

	void runAll() {

		this->fileRead();

		if (!countries.size()) {
			cout << "\nNo record of any data on " << targetDate << "\n";
			return;
		}

		cout << "\nTop 20 countries with the most confirmed cases on " << targetDate << ":\n\n";
		cout << "\t" << "Day" << "\t|\t" << "Country" << "\t|\t" << "Region" << "\t|\t" << "Deaths" << "\t|\t" << "cumDeaths" << "\t|\t" << "Confirmed" << "\t|\t" << "cumConfirmed" << "\t|\t" << "Country Name" << "\t|";
		cout << "\n\n----------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n";

		int count = 1;
		while (!countries.empty() and count <= 20) {
			countryData temp = countries.top();
			countries.pop();

			cout << count << ":  ";
			temp.display();
			count++;
		}
	}
};