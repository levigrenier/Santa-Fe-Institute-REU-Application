//
// Created by levigrenier on 11/20/2021.
//

#include "Network.h"

// Network constructor
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

// Print the current state of the network in the edge list format with timestamps (for transfer to Gephi)
void Network::print_network(int timeStep) {
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < agents.at(i).neighbors.size(); j++) {
            output << to_string(i) << "," << to_string(agents.at(i).neighbors.at(j)) << ",<[" << timeStep << "]>" << endl;
        }
    }
}

// Update every node and print the resulting network
void Network::take_step(int a) {
    for (int i = 0; i < _size; i++) {
        update(i);
    }
    print_network(a);
}

// Closes the file stream
void Network::finish(){
    output.close();
}


// THE CODE BENEATH HERE (AND ABOVE THE SISTER MESSAGE) MAY BE REPEATED TO CREATE MULTIPLE NETWORKS
//      (GIVEN A NEW NEIGHBOR VECTOR IN THE AGENT CLASS)

// Initializes the connections between agents on the network
void Network::initialize_neighbors(int startDegree) {
  // Cycle through all agents
    for (int i = 0; i < _size; i++) {

    // BENEATH HERE IS WHERE YOU CAN CHANGE HOW THE NETWORK IS STRUCTURED AT THE BEGINNING
      // If the agent's neighbor vector isn't filled, fill it.
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

// Helper function to create a new neighbor connection
void Network::new_neighbor(int ID) {
    if (agents.at(ID).neighbors.size() < agents.at(ID).maxDegree) {

        // BENEATH HERE IS WHERE YOU CAN ADD RULES TO ADJUST HOW THE NETWORK EVOLVES.
            int neighborID = -1;
            int secondNeighborSize = 0;
          // Find the 2nd degree neighbor with the most connections (that has not already reached their maximum neighborhood size)
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
              // If a suitable neighbor was found, connect the two nodes
                if (neighborID != -1){
                    agents.at(ID).neighbors.push_back(neighborID);
                    agents.at(neighborID).neighbors.push_back(ID);
                }
          // If the agent has no neighbors to look trough, add a random neighbor.      
            } else {
                do {
                    neighborID = rand()%_size;
                } while (neighborID == ID);
                agents.at(ID).neighbors.push_back(neighborID);
                agents.at(neighborID).neighbors.push_back(ID);
            }
        
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

// THE CODE ABOVE HERE (AND BENEATH THE SISTER MESSAGE) MAY BE REPEATED TO CREATE MULTIPLE NETWORKS
//      (GIVEN A NEW NEIGHBOR VECTOR IN THE AGENT CLASS)


// initialization code for each agent
void Network::Agent::initialize(int ID, int startDegree) {
    maxDegree = ((rand()%(3*startDegree))+(startDegree/2)); //This is an arbitrary calculation
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





