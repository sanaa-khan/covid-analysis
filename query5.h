#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <queue>
using namespace std;

struct countryWeight {
	string country;
	int weight;
	int score;
};

class query5 {

	vector<countryWeight> countries;
	int limit;

	void display(int index) {
		if (index >= 0 and index < countries.size())
			cout << countries[index].weight << "\t|\t" << countries[index].score << "\t|\t" << countries[index].country << "\n";
	}

public:
	query5() {
		limit = 300;
	}

	void fileRead() {
		ifstream  in("WHO-COVID-19.csv");

		if (in) {
			string country, str;
			int active, deaths, total;
			int index = 0;
			countryWeight temp;

			getline(in, str); // reading the column headings of the csv

			while (!in.eof()) {

				getline(in, str, ','); // day

				if (str.size() == 0)
					break;

				getline(in, str, ','); // name

				// special case for reading "Bonaire, Sint Eustatius and Saba"
				// and "occupied Palestinian territory, including east Jerusalem"
				// as they have a comma ',' in the string
				if (str == "BQ" or str == "PS") {
					getline(in, str, ',');
					country = str;

					getline(in, str, ',');
					country += ',';
					country += str;
				}

				else {
					getline(in, str, ',');
					country = str;
				}

				temp.country = country;

				getline(in, str, ','); // region
				getline(in, str, ','); // deaths

				getline(in, str, ','); // cumulative deaths
				deaths = stoi(str);

				getline(in, str, ','); // new cases

				getline(in, str, '\n'); // total confirmed
				total = stoi(str);

				active = total - deaths;

				temp.score = active;

				if (!countries.size()) {
					countries.push_back(temp);
				}

				if (temp.country == countries[countries.size() - 1].country or countries[countries.size() - 1].country == "undefined") {
					countries[countries.size() - 1] = temp;
				}

				else {
					countries.push_back(temp);
				}
			}

			in.close();
		}

		in.open("CountryWeight.csv");

		if (in) {
			string str, country;
			int weight, index = 0;

			getline(in, str); // reading the column headings of the csv

			while (!in.eof()) {

				getline(in, str, ','); // country

				if (str.size() == 0)
					break;

				// special case for reading "Bonaire, Sint Eustatius and Saba"
				// and "occupied Palestinian territory, including east Jerusalem"
				// as they have a comma ',' in the string
				if (str == "\"Bonaire" or str == "\"occupied Palestinian territory") {
					country = str;

					getline(in, str, ',');
					country += ',';
					country += str;
				}

				else {
					country = str;
				}

				getline(in, str, '\n'); // weight
				weight = stoi(str);

				countries[index].weight = weight;
				index++;
			}

			in.close();
		}
	}

	void findHighestScore() {

		int size_ = countries.size();

		// allocating memory
		int** table = new int* [size_ + 1];

		for (int i = 0; i < size_ + 1; i++)
			table[i] = new int[limit + 1];

		// initially whole table is set to zero
		for (int i = 0; i <= size_; i++) {
			for (int j = 0; j <= limit; j++) {
				table[i][j] = 0;
			}
		}

		// now all possible options will be calculated

		int i = 1;

		while (i < size_ + 1) {
			int j = 0;
			int prevIndex = i - 1;

			while (j < limit + 1) {
				table[i][j] = table[prevIndex][j];

				int current = table[i][j];
				int prevScore = countries[prevIndex].score;
				int prevWeight = countries[prevIndex].weight;

				if (j >= countries[prevIndex].weight) {
					if (current < table[prevIndex][j - prevWeight] + prevScore)
						table[i][j] = table[prevIndex][j - prevWeight] + prevScore;
				}

				j++;
			}

			i++;
		}

		cout << "\nHighest possible score for a budget of " << this->limit << " = " << table[size_][limit] << endl;

		cout << "\nCountries selected:\n\n";

		cout << "Weight" << "\t|\t" << "Score" << "\t|\t" << "Country" << "\n";
		cout << "-----------------------------------------------------\n";

		for (int i = size_ - 1; i > 0; i--) {
			if (table[i + 1][limit] != table[i][limit]) {
				this->display(i);
				limit -= countries[i].weight;
			}
		}
	}

	void displayCountries() {
		for (int i = 0; i < countries.size(); i++)
			cout << countries[i].country << " - " << countries[i].weight << " - " << countries[i].score << endl;
	}

	void runAll() {
		this->fileRead();

		if (countries.size()) {
			//this->displayCountries();
			this->findHighestScore();
		}

		else {
			cout << "No data read for any country." << endl;
		}
	}
};