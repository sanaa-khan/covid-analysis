# Covid Analysis
Compilation of several algorithms that answer queries regarding the COVID-19 pandemic, attempting to be as efficient as possible regarding space and time complexities.

## Problem Statement
The 2019–20 coronavirus pandemic is an ongoing pandemic of coronavirus disease 2019 (COVID-19) caused by severe acute respiratory syndrome coronavirus 2 (SARS-CoV-2). As of 13 April 2020, more than 1.84 million cases of COVID-19 have been reported in 210 countries and territories, resulting in more than 114,000 deaths. More than 421,000 people have recovered, although there may be a possibility of reinfection.

In this project, you are required to answer queries regarding the COVID-19 pandemic. You are provided with data regarding the pandemic containing information regarding the daily new cases and cumulative cases for each country.

All data was taken from [here](https://covid19.who.int/).

You must read the given dataset and answer the following queries. For each query, think very carefully about your approach in regards to both the time and space complexity of your solution.

- On a given day, find the top 20 countries with the most confirmed cases. (Efficiently)

- Find the country(s) with the highest new cases between two given dates. (Efficiently)

- Find the starting and ending days of the longest spread period for a given country. The spread period is defined as the period where daily new cases tend to increase. They may contain days where new confirmed cases were relatively lower or none at all.
<br><br>For example, [5, 2, 9, 16, 11, 27, 14, 45, 11] has a longest spread period elapsing 7 days from day 2 (2) to day 8 (45). (Efficiently)

- Find the longest daily death toll decrease period for a given country. They may contain days where new confirmed deaths were relatively higher.
<br><br>For example, [9, 5, 1, 16, 11, 23, 8, 3, 27, 14, 45, 11] has a longest daily death toll decrease period of 4 {16, 11, 8, 3} (Efficiently)

- You have decided to help with the relief effort by collaborating with an organization that distributes essential supplies to affected regions. However, they must consider the overhead cost for each country (distance, shipping etc.). They have assigned a score to each country, which is simply the total number of active cases on the latest day (they prefer to help countries with higher cases). A country may or may not be selected for aid. They have gathered their projected costs for each country and have tasked you with finding the highest possible score attainable as well as the countries selected given a budget of 300. (Efficiently)

## How to Run
This project is a menu-driven application. Compile main.cpp, run the resulting exe and select whichever query you wish to see.

## Contact
Need help? Got any queries? Feel free to hit me up at sanakahnn@gmail.com.
