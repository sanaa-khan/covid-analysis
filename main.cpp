#include "query1.h"
#include "query2.h"
#include "query3.h"
#include "query4.h"
#include "query5.h"

int main()
{
	int opt;

	menu:
		do {
			opt = 0;

			cout << "1. On a given day, find the top 20 countries with the most confirmed cases." << endl;

			cout << "2. Find the country(s) with the highest new cases between two given dates." << endl;

			cout << "3. Find the starting and ending days of the longest spread period for a given country." << endl;

			cout << "4. Find the longest daily death toll decrease period for a given country." << endl;

			cout << "5. An organization is distributing essential supplies to affected regions. "
				<< "They have gathered their projected costs for each country and have to find the highest "
				<< "possible score attainable as well as the countries selected given a budget of 300." << endl;

			cout << endl << "Press 0 to exit the program." << endl;

			cout << "\nYour option: ";
			cin >> opt;
			cout << endl;

			if (opt == 0)
				break;

			switch (opt) {
				case 1:
				{
					cout << "Running query 1:\n";
					cout << "----------------\n";
					query1 q1;
					q1.runAll();
					break;
				}

				case 2:
				{
					cout << "Running query 2:\n";
					cout << "----------------\n";
					query2 q2;
					q2.runAll();
					break;
				}

				case 3:
				{
					cout << "Running query 3:\n";
					cout << "----------------\n";
					query3 q3;
					q3.runAll();
					break;
				}

				case 4:
				{
					cout << "Running query 4:\n";
					cout << "----------------\n";
					query4 q4;
					q4.runAll();
					break;
				}

				case 5:
				{
					cout << "Running query 5:\n";
					cout << "----------------\n";
					query5 q5;
					q5.runAll();
					break;
				}

				default:
					cout << "Option not valid." << endl;
			}

			opt = 0;

			while (opt != 1 and opt != 2) {
				cout << "\nDo you want to run another query?\nPress 1 for yes\nPress 2 for no" << endl;
				cout << "Your option: ";
				cin >> opt;
			}

		} while (opt != 2); 
	
		cout << "\nExiting the program." << endl;

		return 0;
}