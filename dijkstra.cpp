// These are header files, they allow us to use and access premade functions
#include <bits/stdc++.h>

// To avoid repetition we specify that we'll be using the standard namespace
using namespace std;

// Driver code
int main() {
    // Declaring variables and assigning input to the variables
    int numVertices, numEdges;
    cin >> numVertices >> numEdges;

    // Declaring an empty array with the size numVertices. If we find the shortest path, we print this array.
    vector<int> previousNode(numVertices);

    // Declaring another array storing elements in pairs, representing neighboring vertices and edge weights
    vector<vector<pair<int, int>>> adjacencyList(numVertices);

    // Reading edge information and putting edge info into our adjacencyList
    for (int i = 0; i < numEdges; ++i) {
        // Declaring variables and storing input to them
        int src, dest, weight;
        cin >> src >> dest >> weight;
        --src; --dest; // Many graphs start from 0 instead of 1, so we decrement to make nodes 0-based
        adjacencyList[src].push_back({dest, weight});
        adjacencyList[dest].push_back({src, weight});
    }

    // Min-heap priority queue (sorts values in increasing order)
    // Custom type with tuple: (distance, vertex, predecessor)
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

    // Adding a starting tuple (distance, destination, predecessor) onto the priority queue
    pq.push({0, numVertices - 1, -1});

    // Creating a while loop that runs until our priority queue is empty
    while (!pq.empty()) {
        // Pop/remove the tuple from the top of the priority queue and store the values into three variables
        int currentDistance, currentNode, currentPreviousNode;
        tie(currentDistance, currentNode, currentPreviousNode) = pq.top();
        pq.pop();

        // If the predecessor of the current node is already set, skip this iteration
        if (previousNode[currentNode] != 0) {
            continue;
        }
        // Set the predecessor of the current node from the tuple
        previousNode[currentNode] = currentPreviousNode;
        
        // Populate the priority queue with neighboring nodes and their distances if they haven't been visited
        for (const auto& neighbor : adjacencyList[currentNode]) {
            int neighborNode = neighbor.first;
            int edgeWeight = neighbor.second;

            if (previousNode[neighborNode] == 0) {
                pq.push({currentDistance + edgeWeight, neighborNode, currentNode});
            }
        }
    }

    // Output the Result
    if (previousNode[0] == 0) {
        // Outputs -1 if no viable path
        cout << -1;
        return 0;
    }

    int currentNode = 0;
    while (true) {
        cout << currentNode + 1 << ' '; // Adding 1 to convert back to 1-based indexing
        if (currentNode == numVertices - 1) {
            break;
        }
        // Prints the shortest path
        currentNode = previousNode[currentNode];
    }
    // Signals to the computer that our program ends here
    return 0;
}





