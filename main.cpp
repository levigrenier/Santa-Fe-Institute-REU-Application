#include <iostream>
#include "Network.h"

using namespace std;

int main() {
    // Seeding the random number function
        srand(time(NULL));
    // User interface to set up parameters
        cout << "Complex System Agent-Based Model" << endl
             << "By: Levi Grenier" << endl << endl;
        cout << "We will be simulating a co-evolving network of agents." << endl
             << "All you need to do is set some parameters." << endl << endl;
        int size;
        string filename;
        int degree;
        cout << "Please input a filename to export our data to:";
        cin >> filename;
        cout << "\nHow many agents do you want to simulate?" << endl
                         << "Enter:";
        cin >> size;
        cout << "\nPlease enter the average node's degree:";
        cin >> degree;
        Network system(size,filename,degree);
        int steps;
        cout << "\nFinally, how many time steps would you like to simulate?" << endl
             << "Enter: ";
        cin >> steps;

        cout << "\nWonderful! We will now being the calculations. This may take a while..." << endl;

    // Running the simulation
        for (int a = 1; a <= steps; a++) {
            system.take_step(a);
        }

    // Closing output file
        system.finish();

    return 0;
}
