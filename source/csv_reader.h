//
// Created by rodri on 14/05/2024.
//

#ifndef PROJETO_DA_2_CSV_READER_H
#define PROJETO_DA_2_CSV_READER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "node.h"
#include <fstream>
#include <sstream>

class csv_reader {
private:
    int number_of_nodes; // the max id of the nodes (the real number of nodes is that + 1 since the ids start at 0)
    std::vector<node> real_world_nodes;
    std::unordered_map<std::string, double> edges;

    std::vector<std::string> toy_graph_files = {"shipping.csv", "stadiums.csv", "tourism.csv"};
    std::vector<std::string> extra_fully_connected_graph_files = {"edges_25.csv", "edges_50.csv", "edges_75.csv", "edges_100.csv", "edges_200.csv", "edges_300.csv", "edges_400.csv", "edges_500.csv", "edges_600.csv", "edges_700.csv", "edges_800.csv", "edges_900.csv"};
public:
    csv_reader();
    void read_toy_graphs(int file_index);
    void read_extra_fully_connected_graphs(int file_index);
    void read_real_world_graphs(int directory_index);
    int getNumberOfNodes();

    std::vector<node> getRealWorldNodes();
    std::unordered_map<std::string, double> getEdges();
};


#endif //PROJETO_DA_2_CSV_READER_H
