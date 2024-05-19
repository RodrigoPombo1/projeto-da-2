#include "csv_reader.h"

using namespace std;

/// @brief Initializes the csv reader
/// complexity: 0(1)
csv_reader::csv_reader() {
}

/// @brief Reads a said csv file from the toy graphs folder
/// complexity: O(n*m) (n = number of lines in the file, m = number of cells in each line)
/// @param file_index the index of the file to be read
void csv_reader::read_toy_graphs(int file_index) {
    this->number_of_nodes = 0;
    std::string file_name = this->toy_graph_files[file_index-1];
    this->edges = {};
    ifstream file("data/Toy-Graphs/" + file_name);
    string line;
    getline(file, line); // skip the first line
    while (getline(file, line)) {
        stringstream ss(line);
        string node1, node2, weight;
        getline(ss, node1, ',');
        getline(ss, node2, ',');
        getline(ss, weight, ',');
        this->edges.insert({node1 + "-" + node2, stod(weight)});
        this->number_of_nodes = max(this->number_of_nodes, stoi(node1));
        this->number_of_nodes = max(this->number_of_nodes, stoi(node2));
    }
    this->number_of_nodes++;
}

/// @brief Reads a said csv file from the extra fully connected graphs folder
/// complexity: O(n*m) (n = number of lines in the file, m = number of cells in each line)
/// @param file_index the index of the file to be read
void csv_reader::read_extra_fully_connected_graphs(int file_index) {
    this->number_of_nodes = 0;
    std::string file_name = this->extra_fully_connected_graph_files[file_index-1];
    this->edges = {};
    ifstream file("data/Extra_Fully_Connected_Graphs/" + file_name);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string node1, node2, weight;
        getline(ss, node1, ',');
        getline(ss, node2, ',');
        getline(ss, weight, ',');
        this->edges.insert({node1 + "-" + node2, stod(weight)});
        this->number_of_nodes = max(this->number_of_nodes, stoi(node1));
        this->number_of_nodes = max(this->number_of_nodes, stoi(node2));
    }
    this->number_of_nodes++;
}

/// @brief Reads a said folder with csv files from the real world graphs folder
/// complexity: O(n*m) (n = number of lines in the file, m = number of cells in each line)
/// @param directory_index the index of the folder to be read
void csv_reader::read_real_world_graphs(int directory_index) {
    this->number_of_nodes = 0;
    this->real_world_nodes = {};
    string directory_name = "data/Real-World Graphs/graph" + to_string(directory_index);
    ifstream file(directory_name + "/nodes.csv");
    string line;
    getline(file, line); // skip the first line
    while (getline(file, line)) {
        stringstream ss(line);
        string id, x, y;
        getline(ss, id, ',');
        getline(ss, x, ',');
        getline(ss, y, ',');
        this->real_world_nodes.push_back(node(stoi(id), stod(x), stod(y)));
        this->number_of_nodes = max(this->number_of_nodes, stoi(id));
    }
    file.close();
    this->edges = {};
    file.open(directory_name + "/edges.csv");
    getline(file, line); // skip the first line
    while (getline(file, line)) {
        stringstream ss(line);
        string node1, node2, weight;
        getline(ss, node1, ',');
        getline(ss, node2, ',');
        getline(ss, weight, ',');
        this->edges.insert({node1 + "-" + node2, stod(weight)});
    }
    this->number_of_nodes++;
}

/// @brief gets the number of nodes in the graph
/// complexity: O(1)
/// @return the number of nodes in the graph
int csv_reader::getNumberOfNodes() {
    return this->number_of_nodes;
}

/// @brief gets a vector with the nodes of the real world graph
/// complexity: O(1)
/// @return a vector with the nodes of the real world graph
std::vector<node> csv_reader::getRealWorldNodes() {
    return this->real_world_nodes;
}

/// @brief gets a map with the edges of the graph
/// complexity: O(1)
/// @return a map with the edges of the graph
std::unordered_map<std::string, double> csv_reader::getEdges() {
    return this->edges;
}