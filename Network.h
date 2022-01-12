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

// Creating the network class
class Network {
public:
  // Creating the Agent sub-class
    class Agent {
    public:
        void initialize(int ID, int startDegree);
        int maxDegree;
        vector<int> neighbors;
    protected:
        int _ID;
    };

  // Constructor to initialize the network  
    Network(int size, string fileName, int startDegree);
  // Map to contain all of the network's agents and their IDs
    map<int,Agent> agents;  
  // Simulation functions
    void print_network(int timeStep);
    void take_step(int a);
    void finish();
  // Neighbor initialization and manipulation functions.
    void initialize_neighbors(int startDegree);
    void new_neighbor(int ID);
    void remove_neighbors(int ID, int ID2);
    void update(int ID);
    
protected:
  // Network size and output stream data members.
    int _size;
    ofstream output;
};


#endif //SANTAFE_NETWORK_H
