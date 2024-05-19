#include "request.h"

using namespace std;

/// @brief Initializes the request constructor
/// complexity: O(1)
request::request() {
}

/// @brief Sets the graph type to read
/// complexity: O(1)
/// @param graph_type the graph type to read
void request::setGraphTypeToRead(int graph_type) {
    this->graph_type_to_read = graph_type;
}

/// @brief Sets the graph file
/// complexity: O(1)
/// @param graph_file_index the graph file index
void request::setGraphFile(int graph_file_index) {
    switch (graph_type_to_read) {
        case 1:
            csvReader.read_toy_graphs(graph_file_index);
            graph_type = 1;
            this->number_of_nodes = this->csvReader.getNumberOfNodes();
            this->edges = this->csvReader.getEdges();
            break;
        case 2:
            csvReader.read_extra_fully_connected_graphs(graph_file_index);
            graph_type = 2;
            this->number_of_nodes = this->csvReader.getNumberOfNodes();
            this->edges = this->csvReader.getEdges();
            break;
        case 3:
            csvReader.read_real_world_graphs(graph_file_index);
            graph_type = 3;
            this->real_world_nodes = this->csvReader.getRealWorldNodes();
            this->number_of_nodes = this->real_world_nodes.size();
            this->edges = this->csvReader.getEdges();
            break;
    }
}

/// @brief Gets the graph type
/// complexity: O(1)
/// @return the graph type
int request::getGraphType() {
    return this->graph_type;
}

/// @brief Gets the graph type to read
/// complexity: O(1)
/// @return the graph type to read
int request::getGraphTypeToRead() {
    return this->graph_type_to_read;
}

/// @brief Gets the distance between two nodes
/// complexity: O(1)
/// @param node1_id the ID of the first node
/// @param node2_id the ID of the second node
/// @return the distance between the two nodes
double request::distance(int node1_id, int node2_id) {
    string edge_code;
    if (node1_id < node2_id) {
        edge_code = to_string(node1_id) + "-" + to_string(node2_id);
    } else {
        edge_code = to_string(node2_id) + "-" + to_string(node1_id);
    }
    auto it = this->edges.find(edge_code);
    if (it != this->edges.end()) {
        return it->second;
    }
    if (this->graph_type == 3) {
        return calculate_distance_between_two_nodes(real_world_nodes[node1_id], real_world_nodes[node2_id]);
    }
    return -1; // caso em que é para considerar distancia infinita
}

/// @brief Calculates the distance between two nodes
/// complexity: O(1)
/// @param node1 the first node
/// @param node2 the second node
/// @return the distance between the two nodes
double request::calculate_distance_between_two_nodes(node node1, node node2) {
    double lat1 = node1.getLatitude();
    double lon1 = node1.getLongitude();
    double lat2 = node2.getLatitude();
    double lon2 = node2.getLongitude();

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);

    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

/// @brief Gets the result of the recursive backtracking algorithm from a starting node
/// complexity: O(n!) (n = number of nodes)
/// @param starting_node the starting node
/// @return the result of the recursive backtracking algorithm
std::pair<double, std::vector<int>> request::recursive_backtracking_start(int starting_node) {
    vector<pair<int, bool>> nodes_id_not_used_in_this_path;
    for (int i = 0; i < this->number_of_nodes; i++) {
        if (i == starting_node) {
            nodes_id_not_used_in_this_path.push_back(pair(i, true));
        }
        else {
            nodes_id_not_used_in_this_path.push_back(pair(i, false));
        }
    }
    return recursive_backtracking(starting_node, nodes_id_not_used_in_this_path, starting_node);
}

/// @brief Recursive backtracking algorithm to find the shortest path
/// complexity: O(n!) (n = number of nodes)
/// @param previous_node the previous node
/// @param nodes the nodes not used in this path
/// @param starting_node the starting node
/// @return the shortest path
std::pair<double, std::vector<int>> request::recursive_backtracking(int previous_node, vector<pair<int, bool>> nodes, int starting_node) {
    vector<pair<double, vector<int>>> vector_distances_and_their_paths;
    // connect to all nodes not used in this path
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        if (it->second == false) {
            int node_id = it->first;
            double distance_between_the_nodes = distance(previous_node, node_id);
            if (distance_between_the_nodes == -1) {
                continue;
            }
            it->second = true;
            pair<double, vector<int>> aux_pair = recursive_backtracking(node_id, nodes, starting_node);
            it->second = false;
            vector_distances_and_their_paths.push_back(
                    pair<double, vector<int>>(distance_between_the_nodes + aux_pair.first,
                                                          aux_pair.second));
        }
    }
    // in case there was no path: connect to origin (it's the base case where there is no node left that wasn't visited)
    if (vector_distances_and_their_paths.size() == 0) {
        double distance_between_the_nodes = distance(previous_node, starting_node);
        // if there was no connection from the previous node to the origin (then the path isn't valid)
        if (distance_between_the_nodes == -1) {
            vector_distances_and_their_paths.push_back(pair<double, vector<int>>(-1, vector<int>()));
        }
        // add the final edge to the path (add the origin at the end of the path) (as if it was the return of a recursive call to the case)
        vector_distances_and_their_paths.push_back(pair<double, vector<int>>(distance_between_the_nodes, vector<int>(0)));
    }
    // filter out -1 distances (the inccorrect paths)
    vector<pair<double, vector<int>>> filtered_vector_distances_and_their_paths;
    for (auto it = vector_distances_and_their_paths.begin(); it != vector_distances_and_their_paths.end(); it++) {
        if (it->first != -1) {
            filtered_vector_distances_and_their_paths.push_back(*it);
        }
    }
    // case where the path was a dead end (the only path was a -1 distance and it was removed from the vector)
    if (filtered_vector_distances_and_their_paths.size() == 0) {
        return pair<double, vector<int>>(-1, vector<int>());
    }
    // regular case where there are multiple paths and we need to get the minimum path
    pair<double, vector<int>> min_distance_and_path = filtered_vector_distances_and_their_paths[0];
    for (int i = 1; i < filtered_vector_distances_and_their_paths.size(); i++) {
        if (filtered_vector_distances_and_their_paths[i].first < min_distance_and_path.first) {
            min_distance_and_path = filtered_vector_distances_and_their_paths[i];
        }
    }
    // add the previous node to the path
    min_distance_and_path.second.insert(min_distance_and_path.second.begin(), previous_node);
    return min_distance_and_path;
}

/// @brief Gets the written result of the recursive backtracking algorithm from a starting node
/// complexity: O(n!) (n = number of nodes)
/// @param starting_node the starting node
/// @return the written result of the recursive backtracking algorithm
std::vector<std::string> request::print_result_backtracking(int starting_node) {
    pair<double, vector<int>> result = recursive_backtracking_start(starting_node);
    if (result.first == -1) {
        return vector<std::string>{"No path found."};
    }
    vector<int> path = result.second;
    vector<string> path_string;
    for (int i = 0; i < path.size(); i++) {
        path_string.push_back(to_string(path[i]) + " -> " + to_string(path[i+1]));
    }
    path_string.push_back("Total distance: " + to_string(result.first));
    return path_string;
}

/// @brief Gets Minimum Spanning Tree using Prim's MST algorithm
/// complexity: O(nlog(n)) (n = number of nodes)
/// @param nodes the nodes to be used in the MST
/// @return the Minimum Spanning Tree
vector<vector<int>> request::prim_MST(vector<pair<int, bool>> nodes) {
    // initialization
    vector<double> key(this->number_of_nodes, INT_MAX);
    priority_queue<pair<int, double>, vector<pair<int, double>>, compare> priority_queue_aux;
    vector<int> predecessor(this->number_of_nodes, -1);
    vector<vector<int>> mst(this->number_of_nodes);

    // start with node 0
    key[0] = 0;
    priority_queue_aux.push({0, 0.0});

    while (!priority_queue_aux.empty()) {
        int u = priority_queue_aux.top().first; // gets the vertex with the smallest key
        priority_queue_aux.pop();

        // skips nodes already included in the MST
        if (nodes[u].second) {
            continue;
        }

        nodes[u].second = true; // sets node has visited

        if (predecessor[u] != -1) {
            mst[predecessor[u]].push_back(u);
            mst[u].push_back(predecessor[u]);
        }

        // goes through all the nodes in the graph
        for (int v = 0; v < this->number_of_nodes; ++v) {
            if (!nodes[v].second) { // skips nodes already included in the MST
                double weight = distance(u, v);
                if (weight != -1 && key[v] > weight) {
                    key[v] = weight;
                    priority_queue_aux.push({v, key[v]});
                    predecessor[v] = u;
                }
            }
        }
    }
    return mst;
}

/// @brief Pre-order walk of the Minimum Spanning Tree
/// complexity: O(n) (n = number of nodes)
/// @param current_node the current node
/// @param mst the Minimum Spanning Tree
/// @param visited the visited nodes
/// @param tour the tour
void request::pre_order_walk(int current_node, const vector<vector<int>>& mst, vector<bool>& visited, vector<int>& tour) {
    visited[current_node] = true;
    tour.push_back(current_node);

    // visit all the adjacent nodes and call the function recursively on the ones that haven't been visited yet
    for (int adjacent_node : mst[current_node]) {
        if (!visited[adjacent_node]) {
            pre_order_walk(adjacent_node, mst, visited, tour);
        }
    }
}

/// @brief Gets the result of the greedy heuristic algorithm
/// complexity: O(nlog(n)) (n = number of nodes)
/// @return the result of the greedy heuristic algorithm
vector<int> request::greedy_heuristic() {
    vector<pair<int, bool>> nodes = vector<pair<int, bool>>(this->number_of_nodes, pair(0, false));
    vector<vector<int>> mst = prim_MST(nodes);
    vector<int> tour;
    vector<bool> visited(nodes.size(), false);

    // start the tour at node 0
    pre_order_walk(0, mst, visited, tour);

    // end the tour at node 0
    tour.push_back(tour[0]);

    return tour;
}

/// @brief Gets the written result of the greedy heuristic algorithm
/// complexity: O(nlog(n)) (n = number of nodes)
/// @return the written result of the greedy heuristic algorithm
std::vector<std::string> request::print_result_greedy_heuristic() {
    vector<int> tour = greedy_heuristic();
    vector<string> tour_string;
    double total_distance = 0;
    for (int i = 0; i < tour.size() - 1; i++) {
        double distance_between_the_nodes = distance(tour[i], tour[i+1]);
        total_distance += distance_between_the_nodes;
        tour_string.push_back(to_string(tour[i]) + " -> " + to_string(tour[i+1]) + " (" + to_string(distance_between_the_nodes) + ")");
    }
    tour_string.push_back("Total distance: " + to_string(total_distance));
    return tour_string;
}

/// @brief Gets the result of the Christofides heuristic algorithm
/// complexity: O(n!) (n = number of nodes) (the christofides heuristic algorithm is inefficient because of the minimum weight perfect matching brute force that could be done instead in polynomial time)
/// @return the result of the Christofides heuristic algorithm
vector<int> request::christofides_heuristic() {
    vector<pair<int, bool>> nodes = vector<pair<int, bool>>(this->number_of_nodes, pair(0, false));
    vector<vector<int>> mst = prim_MST(nodes);
    vector<int> odd_degree_vertices = {};
    for (int i = 0; i < mst.size(); i++) {
        if (mst[i].size() % 2 != 0) {
            odd_degree_vertices.push_back(i);
        }
    }
    vector<pair<int, int>> minimum_weight_perfect_matching_odd_degree_vertices = minimum_weight_perfect_matching_brute_force(odd_degree_vertices);
    // add the minimum weight perfect matching odd degree vertices to the MST (making so the mst now is a multigraph)
    for (auto it = minimum_weight_perfect_matching_odd_degree_vertices.begin(); it != minimum_weight_perfect_matching_odd_degree_vertices.end(); it++) {
        mst[it->first].push_back(it->second);
        mst[it->second].push_back(it->first);
    }
    vector<int> result_tour = eulerian_tour(0, mst);
    // remove repeated nodes from the tour
    vector<int> result_tour_with_no_repeated_nodes;
    for (int i = 0; i < result_tour.size(); i++) {
        if (find(result_tour_with_no_repeated_nodes.begin(), result_tour_with_no_repeated_nodes.end(), result_tour[i]) == result_tour_with_no_repeated_nodes.end()) {
            result_tour_with_no_repeated_nodes.push_back(result_tour[i]);
        }
    }
    // add starting node
    result_tour_with_no_repeated_nodes.push_back(result_tour_with_no_repeated_nodes[0]);
    return result_tour_with_no_repeated_nodes;
}

/// @brief Gets the minimum weight perfect matching using brute force
/// complexity: O(n!) (n = number of nodes) (there is a polynomial time algorithm that is better for this problem but it wasn't implemented here)
/// @param odd_degree_vertices the odd degree vertices
/// @return the minimum weight perfect matching
vector<pair<int, int>> request::minimum_weight_perfect_matching_brute_force(std::vector<int> odd_degree_vertices) {
    vector<pair<int, int>> result;
    double mininum_distance = INT_MAX;

    sort(odd_degree_vertices.begin(), odd_degree_vertices.end());
    do {
        double distance = 0;
        for (int i = 0; i < odd_degree_vertices.size(); i += 2) {
            distance += this->distance(odd_degree_vertices[i], odd_degree_vertices[i + 1]);
        }
        if (distance < mininum_distance) {
            mininum_distance = distance;
            result.clear();
            for (int i = 0; i < odd_degree_vertices.size(); i += 2) {
                result.push_back(pair(odd_degree_vertices[i], odd_degree_vertices[i + 1]));
            }
        }
    } while (next_permutation(odd_degree_vertices.begin(), odd_degree_vertices.end()));
    return result;
}

/// @brief Gets the Eulerian tour
/// complexity: O(n) (n = number of nodes)
/// @param starting_node the starting node
/// @param multi_graph the multi graph
/// @return the Eulerian tour
std::vector<int> request::eulerian_tour(int starting_node, std::vector<std::vector<int>> multi_graph) {
    stack<int> current_path;
    vector<int> circuit;

    current_path.push(starting_node);

    while (!current_path.empty()) {
        int current_node = current_path.top();

        if (!multi_graph[current_node].empty()) {
            int node = multi_graph[current_node].back();
            current_path.push(node);
            multi_graph[current_node].pop_back();

            // Remove the reverse edge
            auto it = find(multi_graph[node].begin(), multi_graph[node].end(), current_node);
            if (it != multi_graph[node].end()) {
                multi_graph[node].erase(it);
            }
        } else {
            circuit.push_back(current_node);
            current_path.pop();
        }
    }
    // circuit was in reverse order
    reverse(circuit.begin(), circuit.end());
    return circuit;
}

/// @brief Gets the written result of the Christofides heuristic algorithm
/// complexity: O(n!) (n = number of nodes)
/// @return the written result of the Christofides heuristic algorithm
std::vector<std::string> request::print_result_christofides_heuristic() {
    vector<int> tour = christofides_heuristic();
    vector<string> tour_string;
    double total_distance = 0;
    for (int i = 0; i < tour.size() - 1; i++) {
        double distance_between_the_nodes = distance(tour[i], tour[i+1]);
        total_distance += distance_between_the_nodes;
        tour_string.push_back(to_string(tour[i]) + " -> " + to_string(tour[i+1]) + " (" + to_string(distance_between_the_nodes) + ")");
    }
    tour_string.push_back("Total distance: " + to_string(total_distance));
    return tour_string;
}