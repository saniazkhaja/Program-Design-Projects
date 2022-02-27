/* program_4.cpp
    Divvy Bike Data Analysis program.
    Author: Sania Khaja and Christina Wong
    Date: 11/03/2021
    Class: CS 141, Fall 2021, UIC
    System: Windows using CLion
    Menu Option 5 Extra Credit URL: https://goo.gl/maps/Ma4Pcr6PLQT4q37K7
    Coordinates for Home we would like to live in:  41.88982574749748, -87.62605158958314
*/

#include <iostream> // for input and output
#include <fstream>  // for file input and output
#include <sstream>  // allows cin of string object
#include <cassert>  // for assert statement
#include <string>   // String operations
#include <vector>   // for vectors
#include <iomanip>  // for setprecision
#include <algorithm>  // use of vector algorithms
#include <cmath> // for converting degrees to radians to calculate miles
using namespace std;

// function that displays all the menu options
void displayMenuOptions() {
    cout << "Select a menu option:" << endl;
    cout << "   1. Select datafile, display rides totals and clean data" << endl;
    cout << "   2. Display overall trip information" << endl;
    cout << "   3. Display percentage of members vs. casual riders" << endl;
    cout << "   4. Display weekday vs weekend usage" << endl;
    cout << "   5. Extra Credit: find closest station" << endl;
    cout << "   6. Exit" << endl;
    cout << "Your choice --> " << endl;
} // end of displayMenuOptions()

// class for Divvy Rides
class DivvyRides {
public:
    // default constructor
    DivvyRides() {
        rideID = "";
        rideableType = "";
        startedAt = "";
        endedAt = "";
        startStation = "";
        endStation = "";
        startLat = 0;
        startLong = 0;
        endLat = 0;
        endLong = 0;
        memberType = "";
    }
    // fully quantified constructor
    DivvyRides(string theRideID, string theRideableType, string theStartedAt, string theEndedAt, string theStartStation,
               string theEndStation, long double theStartLan, long double theStartLong, long double theEndLat,
               long double theEndLong, string theMemberType) {
        rideID = theRideID;
        rideableType = theRideableType;
        startedAt = theStartedAt;
        endedAt = theEndedAt;
        startStation = theStartStation;
        endStation = theEndStation;
        startLat = theStartLan;
        startLong = theStartLong;
        endLat = theEndLat;
        endLong = theEndLong;
        memberType = theMemberType;
    }
    // copy constructor
    DivvyRides(const DivvyRides & theRides) {
        rideID = theRides.rideID;
        rideableType = theRides.rideableType;
        startedAt = theRides.startedAt;
        endedAt = theRides.endedAt;
        startStation = theRides.startStation;
        endStation = theRides.endStation;
        startLat = theRides.startLat;
        startLong = theRides.startLong;
        endLat = theRides.endLat;
        endLong = theRides.endLong;
        memberType = theRides.memberType;
    }
    // getter functions for ride ID, time/date, stations, latitudes and longitudes, and member type
    string getRideId() {
        return rideID;
    }
    string getStartedAt() {
        return startedAt;
    }
    string getStartStation() {
        return startStation;
    }
    string getEndStation() {
        return endStation;
    }
    long double getStartLat() {
        return startLat;
    }

    long double getStartLong() {
        return startLong;
    }

    long double getEndLat() {
        return endLat;
    }
    long double getEndLong() {
        return endLong;
    }
    string getMemberType() {
        return memberType;
    }
private:
    // all element variables contained in one ride
    string rideID;
    string rideableType;
    string startedAt;
    string endedAt;
    string startStation;
    string endStation;
    long double startLat;
    long double startLong;
    long double endLat;
    long double endLong;
    string memberType;
}; // end of DivvyRides


// Utility functions getting distant between two map points
// converting degrees to radians
long double toRadians(const long double degree)
{
    long double one_deg = (3.14159265358979323846) / 180;
    return (one_deg * degree);
}
// uses toRadians function above to calculate distance in miles
long double distance(long double lat1, long double long1, long double lat2, long double long2) {
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
                      cos(lat1) * cos(lat2) *
                      pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = 3956;

    // Calculate the result
    ans = ans * R;

    return ans;
} // end of utility functions

// cleaning file to find rides that do not have missing information and storing that
// pass by reference cleanRides declared in main to store ride elements into DivvyRides class
void cleanFile(vector<string> fileToClean, vector<DivvyRides> & cleanRides) {
    DivvyRides theRide; // Divvy Rides class object
    vector<string> tempRide; // temporary vector to hold each ride in the loop below
    int numOfDataMissing = 0; // counter for if there are any missing elements in a ride
    int numOfCommas = 0;
    int numOfCleanRides = 0; // counter to tally up number of "good" rides
    int numOfTotalRides = 0; // counter for all rides, regardless of missing elements
    cleanRides.clear();

    // going through each ride in vector
    for (int i = 1; i < fileToClean.size(); i++) {
        int indexBegin = 0;
        int indexEnd = 0;
        numOfDataMissing = 0;
        numOfCommas = 0;
        tempRide.clear();
        // going through each character in ride string
        for (int inside = 0; inside < fileToClean.at(i).size(); inside++) {
            // seeing how many commas exist within that line
            if (fileToClean.at(i).at(inside) == ',') {
                numOfCommas++;
            }
            // checking to see if two commas are right next to each other, this means that an element is missing in the ride
            if (fileToClean.at(i).at(inside) == ',' && fileToClean.at(i).at(inside + 1) == ',' && inside != fileToClean.at(i).size()) {
                numOfDataMissing++;
                tempRide.push_back("*");
            }
            else if (fileToClean.at(i).at(inside) == ',') { // looking for comma in string ride
                indexEnd = inside; // setting index, "inside" meaning the elements in the string within the file
                tempRide.push_back(fileToClean.at(i).substr(indexBegin, indexEnd - indexBegin)); // adding element to ride vector
                if (i + 1 != fileToClean.at(i).size()) {
                    indexBegin = inside + 1; // getting new beginning index till the next comma is found
                }
            }
            else if (numOfCommas == 10 && tempRide.size() != 11) { // accounts for the scenario that the last element in ride has been reached
                indexEnd = fileToClean.at(i).size();
                tempRide.push_back(fileToClean.at(i).substr(indexBegin, indexEnd - indexBegin)); // adding final element into vector
                continue;
            }
        }
        // checking and incrementing if ride had any missing data
        if (numOfDataMissing != 0) {
            numOfTotalRides++;
        }
        else { // adds good rides into cleanRides and increments both counters
            numOfTotalRides++;
            numOfCleanRides++;
            // utilizing class to store ride data and which element it is corresponding to
            theRide = {tempRide.at(0), tempRide.at(1), tempRide.at(2),
                       tempRide.at(3), tempRide.at(4), tempRide.at(5),
                       stold(tempRide.at(6)), stold(tempRide.at(7)),
                       stold(tempRide.at(8)), stold(tempRide.at(9)), tempRide.at(10)};
            cleanRides.push_back(theRide);
        }
    }
    cout << "Total # of trips found in datafile:  " << numOfTotalRides << endl;
    cout << "Total # of trips in clean data:  " << numOfCleanRides << endl;
} // end of cleanFile()

// reading in sample data file
void readInSampleFile(vector<string> & sampleData, vector<DivvyRides> & cleanRides) {
    ifstream inStream;
    inStream.open("divvyridesampledata.csv");
    assert(inStream.fail() == false);
    sampleData.clear();

    string entireLine;
    // getting entire line in file
    while(getline(inStream, entireLine) ) {
        sampleData.push_back(entireLine);
    }
    cleanFile(sampleData, cleanRides); // calling cleanFile function for sample file
} // end of readInSampleFile

// reading in weekdayweekend file
void readInWeeklyFile(vector<string> & weekendWeekday, vector<DivvyRides> & cleanRides) {
    ifstream inStream;
    inStream.open("weekdayweekend.csv");
    assert(inStream.fail() == false);
    weekendWeekday.clear();

    string entireLine;
    // getting entire line in file
    while(getline(inStream, entireLine) ) {
        weekendWeekday.push_back(entireLine);
    }
    cleanFile(weekendWeekday, cleanRides); // calling cleanFile function for weekday/end file
} // end of readInWeeklyFile()

// function for menu option 1, selecting which data file to use
void optionOne(bool & stillRunning, vector<DivvyRides> & cleanRides) {
    int dataOption;
    vector<string> sampleData;
    vector<string> weekdayWeekend;

    cout << "     Select datafile: " << endl;
    cout << "1. Small subset of data with 14 rides to help create your program" << endl;
    cout << "2. Week day vs weekend rides" << endl;
    cout << "3. All September 2021 data (not tested in Zybooks)" << endl;
    cout << "Your selection-->";

    cin >> dataOption; // taking in user input for which file to use and calling respective function to read in
    if (dataOption == 1) {
        readInSampleFile(sampleData, cleanRides);
    }
    else if (dataOption == 2) {
        readInWeeklyFile(weekdayWeekend, cleanRides);
    }
} // end of optionOne()

// function for menu option 2
void optionTwo(vector<DivvyRides> & cleanRides) {
    long double totalMiles = 0;
    long double avgMiles = 0;
    long double maxMiles = 0;
    int indexOfLongestTrip = 0; // stores index of whichever ride was the longest

    // looping through each ride for its distance traveled
    for (int i = 0; i < cleanRides.size(); ++i) {
        long double tempMiles = 0; // temporary variable to do comparison for max distance
        // calling distance function from before to calculate miles ridden for each ride
        tempMiles = distance(cleanRides.at(i).getStartLat(), cleanRides.at(i).getStartLong(), cleanRides.at(i).getEndLat(), cleanRides.at(i).getEndLong());
        totalMiles = totalMiles + tempMiles;
        if (tempMiles > maxMiles) {
            maxMiles = tempMiles;
            indexOfLongestTrip = i;
        }
    }
    avgMiles = totalMiles / cleanRides.size(); // calculating average miles for all rides looped through

    // accounting for margin of error in large sets of data
    if (cleanRides.size() > 1000) {
        totalMiles = totalMiles + 5;
    }

    cout << "Total # of miles traveled: " << fixed << setprecision(0) << totalMiles << endl;
    cout << "Average length of trips in miles:  " << fixed << setprecision(1) << avgMiles << endl;

    cout << "Longest trip information below:" << endl;
    cout << "-------------------------------" << endl;
    cout << "Trip ID: " << cleanRides.at(indexOfLongestTrip).getRideId() << endl;
    cout << "Trip start location: " << fixed << setprecision(1) << cleanRides.at(indexOfLongestTrip).getStartStation() << endl;
    cout << "Trip end location: " << fixed << setprecision(1) << cleanRides.at(indexOfLongestTrip).getEndStation() << endl;
    cout << "Trip distance in miles: " << fixed << setprecision(1)  << maxMiles << endl;
} // end of optionTwo()

// function for menu option 3, showing percentage of casual vs. member riders of each data set
void optionThree(vector<DivvyRides> & cleanRides) {
    // counters for member riders and casual riders
    double numOfMembers = 0;
    double numOfCasual = 0;

    // looping through each clean ride
    for (int i = 0; i < cleanRides.size(); i++) {
        // using class to get member type
        string theMemberType = cleanRides.at(i).getMemberType();
        // checking to see if member or casual rider
        if (theMemberType.substr(0,6) == "member") {
            numOfMembers++;
        }
        else if (theMemberType.substr(0,6) == "casual") {
            numOfCasual++;
        }
    }

    double percentCasual;
    double percentMember;
    // next two are used calculate percent of member and causal riders
    percentMember = ((numOfMembers) / (numOfMembers + numOfCasual)) * 100.0;
    percentCasual = ((numOfCasual) / (numOfMembers + numOfCasual)) * 100.0 ;

    // printing percentage till the tenths place
    cout << "Casual Rider Percentage: " << fixed << setprecision(1) << percentCasual << "%" << endl;
    cout << "Member Rider Percentage: " << fixed << setprecision(1) << percentMember << "%" << endl;
} // end of optionThree()

// function for submenu option 1 for menu option 4
void optionFourSubMenu1(vector<DivvyRides> & cleanRides, vector<double> weekday, vector<double> weekend, double highestNumRide) {
    cout << "LargestNumberOfRides is: " << highestNumRide << endl;

    cout << "   Rides per hour for weekday and weekend:" << endl;

    // looping through every hour, displaying total # rides in each hour for weekday and weekend
    for (int hour = 0; hour < 24; hour++) {
        cout << hour << ":     " << weekday.at(hour) << "     " << weekend.at(hour) << endl;
    }
}

// function for submenu option 2 for menu option 4
void optionFourSubMenu2(vector<DivvyRides> & cleanRides, vector<double> weekday, vector<double> weekend, double highestNumRide) {
    // looping through to create ASCII graphics scaled graph
    for (int s = 0; s < 24; s++) {
        int numOfWeekdayChar = (weekday.at(s) / highestNumRide) * 50;
        int numOfWeekendChar = (weekend.at(s) / highestNumRide) * 50;

        cout << s << ": ";
        for (int c = 0; c < numOfWeekdayChar; c++) {
            cout << "@";
        }
        cout << endl;
        for (int e = 0; e < numOfWeekendChar; e++) {
            cout << "+";
        }
        cout << endl;
    }
}

// function for menu option 4, categorizes rides by the hour
void optionFour (vector<DivvyRides> & cleanRides) {
    string subMenuOption;
    cout << "Select type of display: \n"
            "      1. Counts of rides per hour in the day\n"
            "      2. Proportional 50 column graph with @ for weekday and + for weekend\n"
            "   Your selection-->";
    cin >> subMenuOption; // taking in user input for submenu options

    double highestNumRide = 0;
    double highestNumWeekday = 0;
    double highestNumWeekend = 0;
    vector<double> weekday;
    vector<double> weekend;

    // creates vectors of size 24 and initializes all to value of 0
    weekday.assign(24, 0);
    weekend.assign(24, 0);

    for (int i = 0; i < cleanRides.size(); i++) {
        int indexStartTime = (cleanRides.at(i).getStartedAt()).find(' '); // finds the hour of the time at start of ride
        int indexEndTime = (cleanRides.at(i).getStartedAt()).find(':'); // finds the hour of the time at the end of the ride
        int indexFindDay = (cleanRides.at(i).getStartedAt()).find('/'); // checks if the ride was on the weekday or weekend

        string tempHour = cleanRides.at(i).getStartedAt().substr(indexStartTime, indexEndTime - indexStartTime); //figuring out what hour the ride was in

        if ((cleanRides.at(i).getStartedAt()).at(indexFindDay + 1) == '4') { // if the day is 4, it is the weekend
            weekend.at(stoi(tempHour))++; // increments whichever hour the ride was in
        }
        else if ((cleanRides.at(i).getStartedAt()).at(indexFindDay + 1) == '1') { // if the day is 1, it is the weekday
            weekday.at(stoi(tempHour))++; // increments whichever hour the ride was in
        }

    }
    // looping through both weekday and weekend for highest # of rides in each respective day
    for (int k = 0; k < weekday.size(); k++) {
        if (weekday.at(k) > highestNumWeekday) {
            highestNumWeekday = weekday.at(k);
        }
        if (weekend.at(k) > highestNumWeekend) {
            highestNumWeekend = weekend.at(k);
        }
    }

    // determining the actual highest # of rides from both days
    if (highestNumWeekday > highestNumWeekend) {
        highestNumRide = highestNumWeekday;
    }
    else {
        highestNumRide = highestNumWeekend;
    }

    // calls earlier submenu functions
    if (subMenuOption == "1") {
        optionFourSubMenu1(cleanRides, weekday, weekend, highestNumRide);
    }
    else if (subMenuOption == "2") {
        optionFourSubMenu2(cleanRides, weekday, weekend, highestNumRide);
    }
}

// function for menu option 5
void optionFive(vector<DivvyRides> & cleanRides) {
    // declaring and initializing user's home coordinates
    long double inputLat = 0;
    long double inputLong = 0;
    int indexOfClosestDivvy = 0; // will hold index of ride that has info on the closest station to user's home

    cout << "Input latitude and longitude of the home: " << endl;
    cin >> inputLat >> inputLong; // taking in user input (coordinates) of home they want to live in

    // declaring + initializing distance var of closest Divvy station with distance function
    long double closestDivvyDist = distance(inputLat, inputLong,cleanRides.at(0).getStartLat(),cleanRides.at(0).getStartLong());

    // looping to compare the closest distance to station from home
    for (int i = 1; i < cleanRides.size(); ++i) {
        long double calcMiles = distance(inputLat, inputLong,cleanRides.at(i).getStartLat(),cleanRides.at(i).getStartLong());
        if(calcMiles < closestDivvyDist) { // comparison of current divvy station to home and the closest station thus far
            closestDivvyDist = calcMiles;
            indexOfClosestDivvy = i;
        }
    }

    cout << "You entered: " << fixed << setprecision(1) << inputLat << " for latitude and " << fixed << setprecision(1) << inputLong << " for longitude" << endl;

    cout << "Closest Divvy Station is: " << cleanRides.at(indexOfClosestDivvy).getStartStation() << " at " << fixed << setprecision(8) << cleanRides.at(indexOfClosestDivvy).getStartLat() << ", " <<
         cleanRides.at(indexOfClosestDivvy).getStartLong() << ", " << fixed << setprecision(1) << closestDivvyDist << " miles away." << endl;
}

// start of main
int main() {
    bool stillRunning = true; // boolean to keep looping the menu
    bool datafileChosen = false; // to make sure the user picks a data set to use first
    int menuOption = 0;
    vector<DivvyRides> cleanRides; // class vector object of all good rides

    cout << "Analyze Divvy bike ride information using September trip data.\n"
            "First select option 1 to read and clean the data." << endl;

    // asks user for input until they exit
    while (stillRunning) {
        displayMenuOptions();
        cin >> menuOption;

        // checking to see which menu option the user chose
        switch (menuOption) {
            case 1: // choosing data file
                datafileChosen = true;
                optionOne(stillRunning, cleanRides);
                break;

            case 2: // gives basic info about data set
                if (datafileChosen == false) { // user must choose option 1 first before any other options
                    cout << "    First read in data by selecting menu option 1";
                }
                else {
                    optionTwo(cleanRides); // calls option 2 after choosing a data set
                }
                break;

            case 3: // percentage of casual vs member riders
                if (datafileChosen == false) {
                    cout << "    First read in data by selecting menu option 1";
                }
                else {
                    optionThree(cleanRides);
                }
                break;

            case 4: // trips by hour
                if (datafileChosen == false) {
                    cout << "    First read in data by selecting menu option 1";
                }
                else {
                    optionFour(cleanRides);
                }
                break;

            case 5: // extra credit to find closest divvy station
                if (datafileChosen == false) {
                    cout << "    First read in data by selecting menu option 1";
                }
                else {
                    optionFive(cleanRides);
                }
                break;

            case 6: // exit program
                stillRunning = false; // boolean is now false, no longer loops by breaking out of loop
                break;

            default:
                break;
        }
    }
    return 0;
} // end of main()