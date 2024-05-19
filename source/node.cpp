//
// Created by rodri on 17/05/2024.
//

#include "node.h"

node::node(int id, double longitude, double latitude) {
    this->id = id;
    this->longitude = longitude;
    this->longitude = latitude;
    this->visited = false;
}

int node::getId() {
    return this->id;
}

double node::getLongitude() {
    return this->longitude;
}

double node::getLatitude() {
    return this->latitude;
}

bool node::hasBeenVisited() {
    return this->visited;
}

void node::setVisited(bool visited) {
    this->visited = visited;
}

bool node::operator==(const node &other) const {
    return this->id == other.id;
}