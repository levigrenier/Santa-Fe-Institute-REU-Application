# Santa Fe Institute REU Application Code Sample
### Introduction
This repository contains code to supplement my application the the Santa Fe Institute's REU program. 
The program contained simulates an evolving network and it is written in C++.

### Results
I simulated two networks of 200 agents for 200 time-steps where each agent has an average of 20 edges. 

#### First network: 
For each time-step, every node terminated the connection with its least-connected neighbor and then randomly connected to a new node.
The resulting network and the progression of the clustering coefficient are pictured below.

![NetworkSimulation1](https://user-images.githubusercontent.com/74566341/148861260-711d534b-8d22-44fd-b843-b375ddeaf71c.gif)

![Network1](https://user-images.githubusercontent.com/74566341/148860836-df513b9d-f447-40a8-9310-fc06966cab2d.PNG)


#### Second network: 
For each time-step, every node terminated the connection with its least-connected neighbor and then connected with the most-connected neighbor of its neighbors (but not to itself).
The resulting network and the progression of the clustering coefficient are pictured below.

![NetworkSimulation2](https://user-images.githubusercontent.com/74566341/148861481-a5894426-7fae-418e-b45a-8fb91908e4aa.gif)

![Network2](https://user-images.githubusercontent.com/74566341/148861477-1e5bdff8-e606-4296-a4a7-5c3e8cbd636c.PNG)


Notice how the clustering coefficient peaks and then stabilizes in this network. I assume this is because the dynamics of this network are essentially a sorting algorithm (adding highly-connected neighbors and discarding the lowly-connected). The reason the network doesn't dissolve entirely is because I've included a lower bound of connections per node. 

(This gif cuts off the last 50 time-steps as they were the same as the final frames.)


The visuals are courtesy of the Gephi software.
