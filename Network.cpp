//
// Created by levigrenier on 11/20/2021.
//

#include "Network.h"

Network::Network(int size, string fileName, int startDegree) {
    // Set _size
        _size = size;
    // Initialize Output
        output.open(fileName + ".csv");
    // Initialize each agent
        for (int i = 0; i < size; i++) { agents[i].initialize(i,startDegree); }
    // Create the random network links
        initialize_neighbors(startDegree);
    // Add the initial conditions to the output file
        output << "Source,Target,Timeset" << endl;
        print_network(0);
}

void Network::print_network(int timeStep) {
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < agents.at(i).neighbors.size(); j++) {
            output << to_string(i) << "," << to_string(agents.at(i).neighbors.at(j)) << ",<[" << timeStep << "]>" << endl;
        }
    }
}

void Network::take_step(int a) {
    for (int i = 0; i < _size; i++) {
        update(i);
    }
    print_network(a);
}


void Network::finish(){
    output.close();
}



// TODO: THE CODE BENEATH HERE (AND ABOVE THE SISTER MESSAGE) MAY BE REPEATED TO CREATE MULTILAYER NETWORKS
//      (GIVEN A NEW NEIGHBOR VECTOR IN THE AGENT CLASS)

void Network::initialize_neighbors(int startDegree) {
    for (int i = 0; i < _size; i++) {

    // BENEATH HERE IS WHERE YOU CAN CHANGE HOW THE NETWORK IS STRUCTURED AT THE BEGINNING
        if (agents.at(i).neighbors.size()<startDegree) {
            for (int k = 0; k < startDegree-agents.at(i).neighbors.size(); k++) {
                if (agents.at(i).neighbors.size() < agents.at(i).maxDegree) {
                    int newID;
                    do { newID = rand() % _size; }
                    while (newID == i);
                    agents.at(i).neighbors.push_back(newID);
                    agents.at(newID).neighbors.push_back(i);
                }
            }
        }
    // ABOVE HERE IS WHERE YOU CAN CHANGE HOW THE NETWORK IS STRUCTURED AT THE BEGINNING

    }
}


void Network::new_neighbor(int ID) {
    if (agents.at(ID).neighbors.size() < agents.at(ID).maxDegree) {

        // BENEATH HERE IS WHERE YOU CAN ADD RULES TO ADJUST HOW THE NETWORK EVOLVES.
            int newID;
            int numTries = 0;
            int neighborID = -1;
            int secondNeighborSize = 0;
            if (agents.at(ID).neighbors.size() > 0) {
                for (int i = 0; i < agents.at(ID).neighbors.size(); i++) {
                    for (int j = 0; j < agents.at(agents.at(ID).neighbors.at(i)).neighbors.size(); j++) {
                        if (agents.at(agents.at(agents.at(ID).neighbors.at(i)).neighbors.at(j)).neighbors.size() > secondNeighborSize && agents.at(agents.at(ID).neighbors.at(i)).neighbors.at(j) != ID) {
                            if (agents.at(agents.at(agents.at(ID).neighbors.at(i)).neighbors.at(j)).neighbors.size() < agents.at(agents.at(agents.at(ID).neighbors.at(i)).neighbors.at(j)).maxDegree) {
                                neighborID = agents.at(agents.at(ID).neighbors.at(i)).neighbors.at(j);
                                secondNeighborSize = agents.at(agents.at(agents.at(ID).neighbors.at(i)).neighbors.at(j)).neighbors.size();
                            }
                        }
                    }
                }
                if (neighborID != -1){
                    agents.at(ID).neighbors.push_back(neighborID);
                    agents.at(neighborID).neighbors.push_back(ID);
                }
            } else {
                do {
                    neighborID = rand()%_size;
                } while (neighborID == ID);
                agents.at(ID).neighbors.push_back(neighborID);
                agents.at(neighborID).neighbors.push_back(ID);
            }
            /*do {
                newID = agents.at(neighborID).neighbors.at(rand() % agents.at(neighborID).neighbors.size());
                numTries++;
                if (numTries >= 10) {break;}
            } while (newID == ID || agents.at(newID).neighbors.size() > agents.at(newID).maxDegree-2);*/
        // ABOVE HERE IS WHERE YOU CAN ADD RULES TO ADJUST HOW THE NETWORK EVOLVES.


    }
}


void Network::remove_neighbors(int ID, int ID2) {

    // BENEATH HERE IS WHERE YOU CAN CHANGE HOW CONNECTIONS IN THE NETWORK ARE TERMINATED (HOW THE NETWORK DECAYS)
    if (agents.at(ID).neighbors.size() > 1 && agents.at(ID2).neighbors.size() > 1) {
        // Remove from the first
        int i_Pos_in_J = 0;
        while (agents.at(ID).neighbors.at(i_Pos_in_J) != ID2) {
            i_Pos_in_J++;
        }
        agents.at(ID).neighbors.erase(agents.at(ID).neighbors.begin()+i_Pos_in_J);
        // Remove from the second
        int j_Pos_in_I = 0;
        while (agents.at(ID2).neighbors.at(j_Pos_in_I) != ID) {
            j_Pos_in_I++;
        }
        agents.at(ID2).neighbors.erase(agents.at(ID2).neighbors.begin()+j_Pos_in_I);
    }
    // ABOVE HERE IS WHERE YOU CAN CHANGE HOW CONNECTIONS IN THE NETWORK ARE TERMINATED (HOW THE NETWORK DECAYS)
}

// TODO: THE CODE ABOVE HERE (AND BENEATH THE SISTER MESSAGE) MAY BE REPEATED TO CREATE MULTILAYER NETWORKS
//      (GIVEN A NEW NEIGHBOR VECTOR IN THE AGENT CLASS)



void Network::Agent::initialize(int ID, int startDegree) {
    maxDegree = ((rand()%(3*startDegree))+(startDegree/2));
    int _ID = ID;
}


void Network::update(int ID) {
    int leastConnectedNeighborID;
    int leastConnectedNeighborValue = _size;
    for (int i = 0; i < agents.at(ID).neighbors.size(); i++) {
        if (agents.at(agents.at(ID).neighbors.at(i)).neighbors.size() < leastConnectedNeighborValue) {
            leastConnectedNeighborID = agents.at(ID).neighbors.at(i);
            leastConnectedNeighborValue = agents.at(agents.at(ID).neighbors.at(i)).neighbors.size();
        }
    }
    remove_neighbors(ID, leastConnectedNeighborID);
    new_neighbor(ID);
}





