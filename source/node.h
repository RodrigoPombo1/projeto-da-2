//
// Created by rodri on 17/05/2024.
//

#ifndef PROJETO_DA_2_NODE_H
#define PROJETO_DA_2_NODE_H


class node {
private:
    int id;
    double longitude;
    double latitude;
    bool visited;
public:
    node(int id, double longitude, double latitude);
    int getId();
    double getLongitude();
    double getLatitude();
    bool hasBeenVisited();
    void setVisited(bool visited);
    bool operator==(const node &other) const;
};


#endif //PROJETO_DA_2_NODE_H
