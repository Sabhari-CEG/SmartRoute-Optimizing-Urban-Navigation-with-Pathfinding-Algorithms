#include "map.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

//Struct structure for edges between cities
struct  Edge{
    std::string city;
    double distance;
};

//Struct for graph nodes
struct City{
    std::string name;
    std::vector<Edge> edges; 
};

//Now lets form a class for graph formation
class Graph{
    private:
        vector<City> Cities;
        int noOfCities = 0;
    public:

    void addCity(const std::string name){
        if (findCity(name) == Cities.end())
        {
            Cities.push_back({
                name,
                {}
            });
            noOfCities += 1;
        }
    }

    void addRoad(const std::string city1, const std::string city2, double distance){
        Edge edge1 = {
            city1,distance
        };
        Edge edge2 = {
            city2,distance
        };

        auto it1 = findCity(city1);
        auto it2 = findCity(city2);

        if (it1 != Cities.end() && it2 != Cities.end())
        {
            it1->edges.push_back(edge2);
            it2->edges.push_back(edge1);
        } else
        {
            cout << "Any one or both cities are not present in the map";
        }
        
        

    }

    void displayMap(){
        cout << "The number of cities is " + std::to_string(noOfCities) << '\n';
        for (const auto& city : Cities)
        {
            cout << city.name << '\n';
            for (const auto& neighbor : city.edges){
                cout << "\tis connected to " << neighbor.city << " and the distance is " << std::to_string(neighbor.distance) << "\n";
            }
            cout << "\n";
        }
        
    }

    void displayASCII() {
    for (const auto& city : Cities) {
        std::cout << city.name << " --> ";
        for (const auto& edge : city.edges) {
            std::cout << edge.city << "(" << edge.distance << ") ";
        }
        std::cout << std::endl;
    }
}

    private:
    vector<City>::iterator findCity(const string& name){
        return find_if(Cities.begin(),Cities.end(),[&name](const City& city){
            return city.name == name;
        });
    }
};

int main(){
    Graph map;

    map.addCity("Chicago");
    map.addCity("Aurora");
    map.addCity("Rockford");
    map.addCity("Joliet");
    map.addCity("Naperville");
    map.addCity("Springfield");
    map.addCity("Peoria");
    map.addCity("Elgin");
    map.addCity("Waukegan");
    map.addCity("Champaign");
    map.addCity("Bloomington");
    map.addCity("Decatur");
    map.addCity("Evanston");
    map.addCity("Schaumburg");
    map.addCity("Bolingbrook");
    map.addCity("Palatine");
    map.addCity("Skokie");
    map.addCity("Des Plaines");
    map.addCity("Orland Park");
    map.addCity("Tinley Park");


    map.addRoad("Chicago", "Aurora", 41);
    map.addRoad("Chicago", "Rockford", 88);
    map.addRoad("Chicago", "Joliet", 44);
    map.addRoad("Chicago", "Naperville", 33);
    map.addRoad("Chicago", "Elgin", 41);
    map.addRoad("Chicago", "Waukegan", 42);
    map.addRoad("Chicago", "Evanston", 14);
    map.addRoad("Chicago", "Schaumburg", 31);
    map.addRoad("Chicago", "Skokie", 16);
    map.addRoad("Chicago", "Des Plaines", 21);

    map.addRoad("Aurora", "Naperville", 9);
    map.addRoad("Aurora", "Joliet", 24);

    map.addRoad("Rockford", "Elgin", 63);

    map.addRoad("Joliet", "Bolingbrook", 17);
    map.addRoad("Joliet", "Orland Park", 27);
    map.addRoad("Joliet", "Tinley Park", 22);

    map.addRoad("Springfield", "Peoria", 74);
    map.addRoad("Springfield", "Decatur", 39);
    map.addRoad("Springfield", "Bloomington", 64);

    map.addRoad("Peoria", "Bloomington", 45);

    map.addRoad("Champaign", "Bloomington", 52);
    map.addRoad("Champaign", "Decatur", 48);

    map.addRoad("Bloomington", "Decatur", 44);

    map.addRoad("Evanston", "Skokie", 4);
    map.addRoad("Evanston", "Des Plaines", 11);

    map.addRoad("Schaumburg", "Palatine", 7);
    map.addRoad("Schaumburg", "Des Plaines", 11);

    map.addRoad("Bolingbrook", "Naperville", 9);
    map.addRoad("Bolingbrook", "Orland Park", 20);

    map.addRoad("Orland Park", "Tinley Park", 5);
    // map.displayMap();
    map.displayASCII();
    return 0;
}
