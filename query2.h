#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <queue>
#include "Queue.h"
using namespace std;

struct countryData2 {
	string day;
	string country;
	string countryName;
	string region;
	int confirmed;
	int cumConfirmed;

	int dateDiff; // difference between two cumulatives
	int prevC; // this holds confirmed cases on the first date
	int nextC; // this holds confirmed cases on the second date

	countryData2() {
		day = country = countryName = region = "";
		confirmed = cumConfirmed = -1;
		prevC = nextC = 0;
	}

	bool operator() (countryData2 const& c1, countryData2 const& c2) {
		return c1.dateDiff > c2.dateDiff;
	}

	bool operator < (const countryData2& obj) const {
		return this->dateDiff > obj.dateDiff;
	}
};

class query2 {
	string date1;
	string date2;
	
	priority_queue<countryData2> countries;

public:
	query2() {
		cout << "Enter the first date (DD-MM-YY): ";
		cin >> date1;

		cout << "Enter the second date (DD-MM-YY): ";
		cin >> date2; 
	}

	void fileRead() {

		ifstream in("WHO-COVID-19.csv");

		countryData2 pendingCountry;
		
		if (in) {
			countryData2 temp;
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

				if (temp.countryName == "undefined")
					continue;

				getline(in, str, ',');
				temp.region = str;

				getline(in, str, ',');
				getline(in, str, ',');

				getline(in, str, ',');
				temp.confirmed = stoi(str);

				getline(in, str, '\n');
				temp.cumConfirmed = stoi(str);

				if (temp.day == date1) { // record for first date
					pendingCountry = temp;
					pendingCountry.prevC = temp.cumConfirmed;
				}

				if (temp.day == date2 and temp.country == pendingCountry.country) { // a match for second date + same country
					pendingCountry.nextC = temp.cumConfirmed;
					pendingCountry.dateDiff = pendingCountry.nextC - pendingCountry.prevC; // subtracting the two cumulatives
					pendingCountry.dateDiff += pendingCountry.confirmed;

					if (countries.empty())
						countries.push(pendingCountry);

					else {

						temp = countries.top(); // peeking to see if queue contains lesser priority items

						if (temp.dateDiff == pendingCountry.dateDiff) // if equal priorities
							countries.push(pendingCountry);

						else {
							bool flag = true;

							while (temp.dateDiff < pendingCountry.dateDiff) { // removing lower priority items from the queue
								countries.pop();

								if (flag) { // adding the new country just once
									countries.push(pendingCountry);
									flag = false;
								}

								temp = countries.top(); // extracting next country
							}
						}
					}
				}
			}

			in.close();
		}
	}

	void runAll() {

		this->fileRead();

		if (countries.empty()) {
			cout << "\nNo data available for these dates.\n";
			return;
		}


		cout << "\nMaximum new cases between '" << date1 << "' and " << date2 << "': " << countries.top().dateDiff << "\n";
		while (!countries.empty()) {

			countryData2 temp = countries.top();
			countries.pop();

			cout << "\n-------------------------" << "\n\n";
			cout << "Country: " << temp.country << "\n";
			cout << "Country Name: " << temp.countryName << "\n";
			cout << "Region: " << temp.region << "\n";
			cout << "Cases (" << date1 << "): " << temp.prevC << "\n";
			cout << "Cases (" << date2 << "): " << temp.nextC << "\n";
		}
	}
};
