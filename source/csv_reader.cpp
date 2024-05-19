//
// Created by rodri on 14/05/2024.
//

#include "csv_reader.h"

using namespace std;

csv_reader::csv_reader() {
}

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

int csv_reader::getNumberOfNodes() {
    return this->number_of_nodes;
}

std::vector<node> csv_reader::getRealWorldNodes() {
    return this->real_world_nodes;
}

std::unordered_map<std::string, double> csv_reader::getEdges() {
    return this->edges;
}