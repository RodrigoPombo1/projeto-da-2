#ifndef PROJETO_DA_2_REQUEST_H
#define PROJETO_DA_2_REQUEST_H

#include "csv_reader.h"
#include "node.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <math.h>
#include <functional>
#include <climits>
#include <utility>
#include <queue>
#include <stack>

class request {
private:
    // for the priority queue inside the primMST
    struct compare {
        bool operator()(const std::pair<int, double>& p1, const std::pair<int, double>& p2) {
            return p1.second > p2.second;
        }
    };

    csv_reader csvReader;
    int graph_type;
    int graph_type_to_read;

    int number_of_nodes; // the max id of the nodes
    std::vector<node> real_world_nodes;
    std::unordered_map<std::string, double> edges;

    // common to all algorithms
    double distance(int node1_id, int node2_id);
    double calculate_distance_between_two_nodes(node node1, node node2);

    // recursive backtracking
    std::pair<double, std::vector<int>> recursive_backtracking_start(int starting_node = 0);
    std::pair<double, std::vector<int>> recursive_backtracking(int previous_node, std::vector<std::pair<int, bool>> nodes_not_used_in_this_path, int starting_node);

    // common to heuristic algorithms
    std::vector<std::vector<int>> prim_MST(std::vector<std::pair<int, bool>> nodes);
    void pre_order_walk(int u, const std::vector<std::vector<int>>& mst, std::vector<bool>& visited, std::vector<int>& tour);

    // greedy heuristic
    std::vector<int> greedy_heuristic();

    // christophides heuristic (but the minimum weight perfect matching is brute force, so it is not efficient for large graphs)
    std::vector<int> christofides_heuristic();
    std::vector<std::pair<int, int>> minimum_weight_perfect_matching_brute_force(std::vector<int> odd_degree_vertices);
    std::vector<int> eulerian_tour(int starting_node, std::vector<std::vector<int>> multi_graph);

public:
    request();
    void setGraphTypeToRead(int graph_type); // returns 1 for toy graph, 2 for extra fully connected graph, 3 for real world graph
    int getGraphTypeToRead();
    void setGraphFile(int graph_file_index);
    int getGraphType(); // returns 1 for toy graph, 2 for extra fully connected graph, 3 for real world graph

    std::vector<std::string> print_result_backtracking(int starting_node = 0);
    std::vector<std::string> print_result_greedy_heuristic();
    std::vector<std::string> print_result_christofides_heuristic();
};


#endif //PROJETO_DA_2_REQUEST_H
