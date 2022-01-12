//
// Created by levigrenier on 11/20/2021.
//

#ifndef SANTAFE_NETWORK_H
#define SANTAFE_NETWORK_H
#include <map>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Network {
public:

    class Agent {
    public:
        void initialize(int ID, int startDegree);
        int maxDegree;
        vector<int> neighbors;
    protected:
        int _ID;

    };

    map<int,Agent> agents;
    Network(int size, string fileName, int startDegree);
    void print_network(int timeStep);
    void take_step(int a);
    void finish();

    void initialize_neighbors(int startDegree);
    void new_neighbor(int ID);
    void remove_neighbors(int ID, int ID2);
    void update(int ID);

protected:
    int _size;
    ofstream output;
};






#endif //SANTAFE_NETWORK_H
