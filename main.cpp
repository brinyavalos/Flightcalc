#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

const double EARTH_RADIUS_MILES = 3958.8;
const double AVERAGE_AIR_SPEED_MPH = 550.0;

struct Location {
    string name;
    double latitude;
    double longitude;
};

vector<Location> locations = {
    {"Miami Beach, FL, USA", 25.793449, -80.139198},
    {"Fargo, ND, USA", 46.877186, -96.789803},
    {"Idaho City, ID, USA", 43.828850, -115.837860},
    {"Washington, GA, USA",	33.740253,	-82.745857},
    {"Austin, TX, the US"	,30.266666	,-97.733330},
    {"Palm Springs, CA, USA",	33.830517,	-116.545601},
    {"Hot Springs, AR, USA",	34.496212,	-93.057220},
    {"Cary, NC, USA",	35.791538,	-78.781120},
    {"St. Louis, MO, USA",	38.627003,	-90.199402},
    {"Las Vegas, NV, USA",	36.188110,	-115.176468},
};

double degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

double haversine(double lat1, double long1, double lat2, double long2, double radius) {
    double dLat = degreesToRadians(lat2 - lat1);
    double dLong = degreesToRadians(long2 - long1);
    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(degreesToRadians(lat1)) * cos(degreesToRadians(lat2)) * sin(dLong / 2) * sin(dLong / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = radius * c;
    return distance;
}

double getFlightTime(double lat1, double long1, double lat2, double long2) {
    double distance = haversine(lat1, long1, lat2, long2, EARTH_RADIUS_MILES);
    double flightTime = distance / AVERAGE_AIR_SPEED_MPH;
    return flightTime;
}

void printLocations(const vector<Location>& locs) {
    cout << "Choose a location:\n";
    for (int i = 0; i < locs.size(); ++i) {
        cout << i + 1 << ". " << locs[i].name << " (" << locs[i].latitude << ", " << locs[i].longitude << ")" << endl;
    }
}
int main(){
    cout << "Welcome to Flight Time Calculator!" << endl;
    cout<<"This calculator will compute the distance between two locations of your choice from the list below."<<endl;
    printLocations(locations);

    int departureChoice, destinationChoice;
    do {
        cout << "Enter your departure choice (1-" << locations.size() << "): ";
        cin >> departureChoice;
    } while (departureChoice < 1 || departureChoice > locations.size());

    Location departure = locations[departureChoice - 1];

    vector<Location> updatedLocations = locations;
    updatedLocations.erase(updatedLocations.begin() + departureChoice - 1);

    printLocations(updatedLocations);

    do {
        cout << "Enter your destination choice (1-" << updatedLocations.size() << "): ";
        cin >> destinationChoice;
    } while (destinationChoice < 1 || destinationChoice > updatedLocations.size());

    Location destination = updatedLocations[destinationChoice - 1];

    double flightTime = getFlightTime(departure.latitude, departure.longitude,
                                      destination.latitude, destination.longitude);

    cout << "Flight time from " << departure.name << " to " << destination.name
         << " is approximately " << flightTime << " hours." << endl;

    return 0;
}
