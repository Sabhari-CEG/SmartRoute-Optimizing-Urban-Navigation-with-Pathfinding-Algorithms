#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <chrono>
#include <stack>
#include <iomanip>
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
        std::set<std::string> allAvailableCities;

    void addCity(const std::string name){
        if (findCity(name) == Cities.end())
        {
            Cities.push_back({
                name,
                {}
            });
            allAvailableCities.insert(name);
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

    public:
    std::vector<Edge> getNeighbors(const std::string& cityName) const {
        auto it = std::find_if(Cities.begin(), Cities.end(),
                               [&cityName](const City& city) { return city.name == cityName; });
        if (it != Cities.end()) {
            return it->edges;
        }
        return {};
    }
};

struct PathInfo{
    std::vector<std::string> path;
    double cost;
    int nodesVisited;
};

PathInfo breadthFirstSearch(const std::string& source, const std::string& destination, const Graph& map){
    bool foundSource = false;
    bool foundDestination = false;
    for(const auto& city : map.allAvailableCities){
        if (!foundSource && (city == source))
        {
            foundSource = true;
        } else if (!foundDestination && (city == destination))
        {
            foundDestination = true;
        }
    }
        if (!foundSource || !foundDestination)
        {
            cout << "Entered Source or destination not found!\n";
            return PathInfo{{}, -1};
        }
        std::queue<std::string> queue;
    std::unordered_map<std::string, std::string> parent;
    std::unordered_map<std::string, double> distance;
    std::unordered_set<std::string> visited;
    int count = 0;


    queue.push(source);
    visited.insert(source);
    distance[source] = 0;
    

    while (!queue.empty()) {
        std::string current = queue.front();
        queue.pop();
        count++;

        if (current == destination) {
            // Reconstruct path
            std::vector<std::string> path;
            double totalCost = distance[current];
            while (current != source) {
                path.push_back(current);
                current = parent[current];
            }
            path.push_back(source);
            std::reverse(path.begin(), path.end());

            return {path, totalCost,count};
        }

        for (const auto& edge : map.getNeighbors(current)) {
            if (visited.find(edge.city) == visited.end()) {
                visited.insert(edge.city);
                queue.push(edge.city);
                parent[edge.city] = current;
                distance[edge.city] = distance[current] + edge.distance;
            }
        }
    }
    return {{}, -1};

};

PathInfo depthFirstSearch(const std::string& source, const std::string& destination, const Graph& map){
    bool foundSource = false;
    bool foundDestination = false;
    for(const auto& city : map.allAvailableCities){
        if (!foundSource && (city == source))
        {
            foundSource = true;
        } else if (!foundDestination && (city == destination))
        {
            foundDestination = true;
        }
    }
        if (!foundSource || !foundDestination)
        {
            cout << "Entered Source or destination not found!\n";
            return PathInfo{{}, -1};
        }
        std::stack<std::string> stack;
        std::unordered_map<std::string, std::string> parent;
        std::unordered_map<std::string, double> distance;
        std::unordered_set<std::string> visited;
        int count = 0;

        stack.push(source);
        visited.insert(source);
        distance[source] = 0;

        while (!stack.empty())
        {
            std::string current = stack.top();
            stack.pop();
            count++;

            if (current == destination)
            {
                std::vector<std::string> path;
                double totalCost = distance[current];
                while (current != source)
                {
                    path.push_back(current);
                    current = parent[current];
                }
                path.push_back(source);
                std::reverse(path.begin(), path.end());
                return {path,totalCost,count};
                
            }
            for (const auto& edge : map.getNeighbors(current)){
                if (visited.find(edge.city) == visited.end())
                {
                    stack.push(edge.city);
                    visited.insert(edge.city);
                    parent[edge.city] = current;
                    distance[edge.city] = distance[current] + edge.distance;
                }
                
            }
            

        }
        return {{}, -1};
}

struct QueueNode {
    std::string city;
    double cost;
    std::vector<std::string> path;

    bool operator>(const QueueNode& other) const {
        return cost > other.cost;
    }
};

PathInfo uniformCostSearch(const std::string& source, const std::string& destination, const Graph& map) {
    bool foundSource = false;
    bool foundDestination = false;
    for(const auto& city : map.allAvailableCities){
        if (!foundSource && (city == source))
        {
            foundSource = true;
        } else if (!foundDestination && (city == destination))
        {
            foundDestination = true;
        }
    }
        if (!foundSource || !foundDestination)
        {
            cout << "Entered Source or destination not found!\n";
            return PathInfo{{}, -1};
        }
    std::priority_queue<QueueNode, std::vector<QueueNode>, std::greater<QueueNode>> pq;
    std::unordered_set<std::string> visited;
    int count = 0;

    pq.push({source, 0, {source}});

    while (!pq.empty()) {
        QueueNode current = pq.top();
        pq.pop();
        count++;

        if (current.city == destination) {
            return {current.path, current.cost,count};
        }

        if (visited.find(current.city) != visited.end()) {
            continue;
        }

        visited.insert(current.city);

        for (const auto& edge : map.getNeighbors(current.city)) {
            if (visited.find(edge.city) == visited.end()) {
                std::vector<std::string> newPath = current.path;
                newPath.push_back(edge.city);
                double newCost = current.cost + edge.distance;
                pq.push({edge.city, newCost, newPath});
            }
        }
    }

    return {{}, -1}; 
}

struct AStarNode {
    std::string city;
    double g_cost;  
    double h_cost;  
    std::vector<std::string> path;

    double f_cost() const { return g_cost + h_cost; }

    bool operator>(const AStarNode& other) const {
        return f_cost() > other.f_cost();
    }
};

double heuristic(const std::string& current, const std::string& goal, const Graph& map) {
    return map.allAvailableCities.size() * 0.1; 
}

PathInfo aStarSearch(const std::string& source, const std::string& destination, const Graph& map) {
    std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> pq;
    std::unordered_map<std::string, double> g_score;
    std::unordered_set<std::string> closed_set;
    int count = 0;

    pq.push({source, 0, heuristic(source, destination, map), {source}});
    g_score[source] = 0;

    while (!pq.empty()) {
        AStarNode current = pq.top();
        pq.pop();
        count++;

        if (current.city == destination) {
            return {current.path, current.g_cost,count};
        }

        if (closed_set.find(current.city) != closed_set.end()) {
            continue;
        }

        closed_set.insert(current.city);

        for (const auto& edge : map.getNeighbors(current.city)) {
            if (closed_set.find(edge.city) != closed_set.end()) {
                continue;
            }

            double tentative_g_score = current.g_cost + edge.distance;

            if (g_score.find(edge.city) == g_score.end() || tentative_g_score < g_score[edge.city]) {
                g_score[edge.city] = tentative_g_score;
                std::vector<std::string> new_path = current.path;
                new_path.push_back(edge.city);
                double h_score = heuristic(edge.city, destination, map);
                pq.push({edge.city, tentative_g_score, h_score, new_path});
            }
        }
    }

    return {{}, -1}; 
}

int main(){
    Graph map;

    map.addCity("Chicago");
    map.addCity("Aurora");
    map.addCity("Rockford");
    map.addCity("Joliet");
    map.addCity("Peoria");
    map.addCity("Waukegan");
    map.addCity("Champaign");
    map.addCity("Bloomington");
    map.addCity("Decatur");
    map.addCity("Evanston");
    map.addCity("DeKalb");
    map.addCity("Rochelle");
    map.addCity("Dixon");
    map.addCity("Sterling");
    map.addCity("Moline");
    map.addCity("Galesburg");
    map.addCity("Ottawa");
    map.addCity("LaSalle");
    map.addCity("Pontiac");
    map.addCity("Kankakee");
    map.addCity("Watseka");
    map.addCity("Hoopeston");
    map.addCity("Danville");
    map.addCity("Zion");
    map.addCity("Kenosha");
    map.addCity("Racine");
    map.addCity("Milwaukee");
    map.addCity("Madison");
    map.addCity("Morris");
    map.addCity("Dwight");
    map.addCity("Chenoa");
    map.addCity("Lexington");
    map.addCity("Sycamore");
    map.addCity("Genoa");
    map.addCity("Belvidere");
    map.addCity("Streator");
    map.addCity("Momence");
    map.addCity("Rensselaer");
    map.addCity("Lafayette");
    map.addCity("Crawfordsville");
    map.addCity("Lincoln");

    // Major hubs
map.addRoad("Chicago", "Rockford", 88);
map.addRoad("Chicago", "Joliet", 44);
map.addRoad("Chicago", "Aurora", 41);
map.addRoad("Chicago", "Evanston", 14);

// Northern routes
map.addRoad("Rockford", "DeKalb", 42);
map.addRoad("DeKalb", "Aurora", 30);
map.addRoad("DeKalb", "Rochelle", 25);
map.addRoad("Rochelle", "Dixon", 35);
map.addRoad("Dixon", "Sterling", 15);
map.addRoad("Sterling", "Moline", 40);
map.addRoad("Moline", "Galesburg", 50);

// Western routes
map.addRoad("Galesburg", "Peoria", 50);
map.addRoad("Peoria", "Bloomington", 45);
map.addRoad("Bloomington", "Champaign", 52);

// Central routes
map.addRoad("Aurora", "Ottawa", 45);
map.addRoad("Ottawa", "LaSalle", 15);
map.addRoad("LaSalle", "Pontiac", 60);
map.addRoad("Pontiac", "Bloomington", 35);

map.addRoad("Joliet", "Kankakee", 40);
map.addRoad("Kankakee", "Watseka", 35);
map.addRoad("Watseka", "Hoopeston", 40);
map.addRoad("Hoopeston", "Danville", 30);
map.addRoad("Danville", "Champaign", 35);

// Eastern routes
map.addRoad("Evanston", "Waukegan", 28);
map.addRoad("Waukegan", "Zion", 10);
map.addRoad("Zion", "Kenosha", 15);  // Crossing into Wisconsin
map.addRoad("Kenosha", "Racine", 10);
map.addRoad("Racine", "Milwaukee", 25);
map.addRoad("Milwaukee", "Madison", 80);
map.addRoad("Madison", "Rockford", 70);

// Southern routes
map.addRoad("Joliet", "Morris", 25);
map.addRoad("Morris", "Dwight", 30);
map.addRoad("Dwight", "Pontiac", 25);
map.addRoad("Pontiac", "Chenoa", 20);
map.addRoad("Chenoa", "Lexington", 10);
map.addRoad("Lexington", "Bloomington", 15);

// Additional cross-connections
map.addRoad("DeKalb", "Sycamore", 5);
map.addRoad("Sycamore", "Genoa", 10);
map.addRoad("Genoa", "Belvidere", 20);
map.addRoad("Belvidere", "Rockford", 15);

map.addRoad("Ottawa", "Streator", 25);
map.addRoad("Streator", "Pontiac", 30);

map.addRoad("Kankakee", "Momence", 15);
map.addRoad("Momence", "Rensselaer", 35);  // Crossing into Indiana
map.addRoad("Rensselaer", "Lafayette", 45);
map.addRoad("Lafayette", "Crawfordsville", 30);
map.addRoad("Crawfordsville", "Danville", 45);  // Back to Illinois

map.addRoad("Peoria", "Lincoln", 40);
map.addRoad("Lincoln", "Decatur", 40);
map.addRoad("Decatur", "Champaign", 50);
    map.displayASCII();


    string source;
    string destination;

    cout << "Enter Source city\n";
    getline(cin,source);
    cout << "Enter Destination city\n";
    getline(cin,destination);
    PathInfo bfsPath;
    auto startbfs = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; i++)
    {
        bfsPath = breadthFirstSearch(source,destination,map);
    }
    
    
    auto endbfs = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> durationbfs = endbfs - startbfs;
    if (!bfsPath.path.empty()) {
        std::cout << "\nPath found by BFS:\n";
        for (const auto& city : bfsPath.path) {
            std::cout << city;
            if (city != bfsPath.path.back()) {
                std::cout << " -> ";
            }
        }
        std::cout << "\n\nSummary of BFS:";
        std::cout << "\nTotal distance: " << bfsPath.cost << " miles";
        std::cout << "\nNumber of cities in path: " << bfsPath.path.size();
        std::cout << "\nNumber of cities visited before finding the path: " << bfsPath.nodesVisited;
        std::cout << "\nTime taken to find path: " << std::fixed << std::setprecision(9) << durationbfs.count() << " nanoseconds\n";
    } else {
        std::cout << "No path found between " << source << " and " << destination << "\n";
        std::cout << "Time taken for search: " << std::fixed << std::setprecision(9) << durationbfs.count() << " nanoseconds\n";
    }
    PathInfo dfsPath;
    auto startdfs = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; i++)
    {
        dfsPath = depthFirstSearch(source,destination,map);
    }
    
    
    auto enddfs = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> durationdfs = enddfs - startdfs;
    if (!dfsPath.path.empty()) {
        std::cout << "\nPath found by DFS:\n";
        for (const auto& city : dfsPath.path) {
            std::cout << city;
            if (city != dfsPath.path.back()) {
                std::cout << " -> ";
            }
        }
        std::cout << "\n\nSummary of DFS:";
        std::cout << "\nTotal distance: " << dfsPath.cost << " miles";
        std::cout << "\nNumber of cities in path: " << dfsPath.path.size();
        std::cout << "\nNumber of cities visited before finding the path: " << dfsPath.nodesVisited;
        std::cout << "\nTime taken to find path: " << std::fixed << std::setprecision(9) << durationdfs.count() << " nanoseconds\n";
    } else {
        std::cout << "No path found between " << source << " and " << destination << "\n";
        std::cout << "Time taken for search: " << std::fixed << std::setprecision(9) << durationdfs.count() << " nanoseconds\n";
    }
    PathInfo ucsPath;
    auto startUcs = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; i++)
    {
        ucsPath = uniformCostSearch(source, destination, map);
    }
    auto endUcs = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> durationUcs = endUcs - startUcs;

    if (!ucsPath.path.empty()) {
        std::cout << "Path found by UCS:\n";
        for (const auto& city : ucsPath.path) {
            std::cout << city;
            if (city != ucsPath.path.back()) {
                std::cout << " -> ";
            }
        }
        std::cout << "\n\nSummary of UCS:";
        std::cout << "\nTotal distance: " << ucsPath.cost << " miles";
        std::cout << "\nNumber of cities in path: " << ucsPath.path.size();
        std::cout << "\nNumber of cities visited before finding the path: " << ucsPath.nodesVisited;
        std::cout << "\nTime taken to find path: " << std::fixed << std::setprecision(9) 
                  << durationUcs.count() << " nanoseconds\n";
    } else {
        std::cout << "No path found between " << source << " and " << destination << "\n";
        std::cout << "Time taken for search: " << std::fixed << std::setprecision(9) 
                  << durationUcs.count() << " nanoseconds\n";
    }
    PathInfo aStarPath;
    auto startAStar = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; i++)
    {
        aStarPath = aStarSearch(source, destination, map);
    }
    auto endAStar = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> durationAStar = endAStar - startAStar;

    if (!aStarPath.path.empty()) {
        std::cout << "Path found by A*:\n";
        for (const auto& city : aStarPath.path) {
            std::cout << city;
            if (city != aStarPath.path.back()) {
                std::cout << " -> ";
            }
        }
        std::cout << "\n\nSummary of A*:";
        std::cout << "\nTotal distance: " << aStarPath.cost << " miles";
        std::cout << "\nNumber of cities in path: " << aStarPath.path.size();
        std::cout << "\nNumber of cities visited before finding the path: " << aStarPath.nodesVisited;

        std::cout << "\nTime taken to find path: " << std::fixed << std::setprecision(9) 
                  << durationAStar.count() << " nanoseconds\n";
    } else {
        std::cout << "No path found between " << source << " and " << destination << "\n";
        std::cout << "Time taken for search: " << std::fixed << std::setprecision(9) 
                  << durationAStar.count() << " nanoseconds\n";
    }

    return 0;
}