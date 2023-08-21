// baed on logic from last weeks quiz as well as logic from Julia Harbord
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

class AdjacencyList {
private:
    //Think about what member variables you need to initialize
    std::unordered_map<std::string , std::vector<std::string>> graph;
    std::unordered_map<std::string , double> outCount;
    std::unordered_map<std::string , std::vector<std::pair<std::string , double>>> mVar;
    std::map<std::string , double> r0Var;

public:
    //Think about what helper functions you will need in the algorithm
    void PageRank(int n);
    void insertEdge(std::string from, std::string to);
    void outMap();
    void mMap();
    void r0Map();
    void multiplyMap();
    void printVals();
    int outDegree(std::string name);
};

void AdjacencyList::PageRank(int n){

    outMap();
    mMap();
    r0Map();

    if (n == 1){
        printVals();
    }
    else {

        while (n > 1){
            multiplyMap();
            n--;
        }

        printVals();
    }
}
/*prints the PageRank of all pages after p powerIterations in
ascending alphabetical order of webpages and rounding rank to two
        decimal places
*/
// This class and method are optional. To accept the input, you can use this method:

void AdjacencyList::insertEdge(std::string from, std::string to){
    graph[from].push_back(to);
    r0Var[from];
    r0Var[to];
    mVar[from];
    mVar[to];
}

int AdjacencyList::outDegree(std::string name){

    int out = 0;
    auto it = graph.find(name);

    
    if (it != graph.end()){
        for (int i = 0; i < it->second.size(); i++){
            out++;
        }
    }
    return out;
}

void AdjacencyList::outMap() {

    for (auto it = graph.begin(); it != graph.end() ; it++) {
        int outVal = outDegree(it->first);
        outCount[it->first] = outVal;
    }

}

void AdjacencyList::mMap() {

    for (auto it = graph.begin(); it != graph.end() ; it++) {
        for (int i = 0; i < it->second.size(); ++i) {
            if (outCount[it->first] == 0){
                mVar[it->second[i]].push_back(std::make_pair(it->first,0));
            }
            else {
                mVar[it->second[i]].push_back(std::make_pair(it->first,1/outCount[it->first]));
            }

        }
    }

}

void AdjacencyList::r0Map() {

    for (auto it = r0Var.begin(); it != r0Var.end() ; it++) {

        r0Var[it->first] = 1.0/r0Var.size();
    }
}

void AdjacencyList::multiplyMap() {

    double pr = 0;
    std::map<std::string , double> temp;

    for (auto it = mVar.begin(); it != mVar.end() ; it++) {

        for (int i = 0; i < it->second.size(); ++i) {
            pr += std::get<1>(it->second[i]) * r0Var[std::get<0>(it->second[i])];
        }
        temp[it->first] = pr;
        pr = 0;
    }

    for (auto it = r0Var.begin(); it != r0Var.end() ; it++) {

        r0Var[it->first] = temp[it->first];
    }
}

void AdjacencyList::printVals() {
    for (auto it = r0Var.begin(); it != r0Var.end() ; it++) {
        std::cout << it->first << " " << std::setprecision (2) << std::fixed << r0Var[it->first] << std::endl;
    }
}

int main()
{
    //Create a graph object
    AdjacencyList graph;
    int no_of_lines, power_iterations;
    std::string from, to;
    std::cin >> no_of_lines;
    std::cin >> power_iterations;
    for(int i = 0;i < no_of_lines; i++)
    {
        std::cin >> from;
        std::cin >> to;
        // Do Something
        graph.insertEdge(from, to);
    }

    graph.PageRank(power_iterations);
}
