#include "node.h"

/// @brief Initializes the node constructor
/// complexity: O(1)
/// @param id the ID of the node
/// @param longitude the longitude of the node
/// @param latitude the latitude of the node
node::node(int id, double longitude, double latitude) {
    this->id = id;
    this->longitude = longitude;
    this->longitude = latitude;
    this->visited = false;
}

/// @brief Gets the ID of the node
/// complexity: O(1)
/// @return the ID of the node
int node::getId() {
    return this->id;
}

/// @brief Gets the longitude of the node
/// complexity: O(1)
/// @return the longitude of the node
double node::getLongitude() {
    return this->longitude;
}

/// @brief Gets the latitude of the node
/// complexity: O(1)
/// @return the latitude of the node
double node::getLatitude() {
    return this->latitude;
}

/// @brief Checks if the node has been visited
/// complexity: O(1)
/// @return true if the node has been visited, false otherwise
bool node::hasBeenVisited() {
    return this->visited;
}

/// @brief Sets the node as visited or not visited
/// complexity: O(1)
/// @param visited true if the node has been visited, false otherwise
void node::setVisited(bool visited) {
    this->visited = visited;
}

/// @brief Defines an operator to check if two nodes are the same
/// complexity: O(1)
/// @param other the other node to compare
/// @return true if the nodes are the same, false otherwise
bool node::operator==(const node &other) const {
    return this->id == other.id;
}