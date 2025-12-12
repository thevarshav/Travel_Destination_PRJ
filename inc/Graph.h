#ifndef GRAPH_H
#define GRAPH_H

#include "LinkedList.h"
#include <ArrayList.h>
#include <HashTable.h>
#include <Queue.h>
#include <Stack.h>
#include <cstddef>
#include <ostream>
#include <string>

struct Edge;

struct Vertex {
    std::string data;
    ArrayList<Edge *> edgeList;

    Vertex(std::string data) { this->data = data; }
};

inline std::ostream &operator<<(std::ostream &os, Vertex *v) {
    os << v->data;

    return os;
}

struct Edge {
    Vertex *from;
    Vertex *to;
    int partialCost;
    float price;
    float time;

    Edge(Vertex *from, Vertex *to, float time, float price) {
        this->from = from;
        this->to = to;
        this->price = price;
        this->time = time;
    }
};

inline std::ostream &operator<<(std::ostream &os, Edge *e) {
    os << "(" << e->from << ", " << e->to << ") - " << e->to->data
        << ") price=" << e->price
        << "time=" << e->time;
    return os;
}

struct Waypoint {
    Waypoint *parent;
    Vertex *vertex;
    ArrayList<Waypoint *> children;
    float totalPrice;
    float totalTime;
    int partialCost;

    Waypoint(Vertex *v) {
        parent = nullptr;
        vertex = v;
        partialCost = 0;
        totalPrice = 0;
        totalTime = 0;
    }

    void expand(HashTable<std::string> &seen) {
        for (int i = 0; i < vertex->edgeList.size(); i++) {
            Vertex* neighbor = vertex->edgeList[i]->to;
            if (!seen.search(neighbor->data)) {
                Waypoint* temp = new Waypoint(neighbor);
                temp->parent = this;
                temp->totalPrice = this->totalPrice + vertex->edgeList[i]->price;
                temp->totalTime = this->totalTime + vertex->edgeList[i]->time;
                children.append(temp);
            }
        }
    }
};

inline std::ostream &operator<<(std::ostream &os, Waypoint *wp) {
    std::string p = "null";
    if (wp->parent != nullptr) {
        p = wp->parent->vertex->data;
    }

    os << p << " -> " << wp->vertex->data;

    return os;
}

struct Graph {
    ArrayList<Vertex *> vertices;

    Vertex* getOrCreateVertex(const std::string& name){
    for(int i = 0; i < vertices.size(); i++){
        if (vertices[i]->data == name){
            return vertices[i];
        }
    }
    Vertex* v = new Vertex(name);
    vertices.append(v);
    return v;
    }

    bool edgeExists(Vertex* a, Vertex* b) {
        for(int i = 0; i < a->edgeList.size(); i++)
            if(a->edgeList[i]->to == b) return true;
        return false;
    }

    void addEdge(Vertex *x, Vertex *y, float time, float price) {
        if(!edgeExists(x, y)) x->edgeList.append(new Edge(x, y, time, price));
        if(!edgeExists(y, x)) y->edgeList.append(new Edge(y, x, time, price));
    }

    void addDirectedEdge(Vertex *x, Vertex *y, float time, float price) {
        if(!edgeExists(x, y)) x->edgeList.append(new Edge(x, y, time, price));
    }

    /*void addVertex(Vertex *v) { vertices.append(v); }

    void addEdge(Vertex *x, Vertex *y, float time, float price) {
        x->edgeList.append(new Edge(x, y, time, price));
        y->edgeList.append(new Edge(y, x, time, price));
    }

    void addDirectedEdge(Vertex *x, Vertex *y, float time, float price) {
        x->edgeList.append(new Edge(x, y, time, price));
    }*/

    Waypoint *bfs(Vertex *start, Vertex *destination) {
        std::cout << "Running Breadth-First Search" << std::endl;
        Queue<Waypoint *> frontier;
        HashTable<std::string> seen;

        Waypoint *first = new Waypoint(start);

        frontier.enqueue(first);
        seen.insert(first->vertex->data);

        Waypoint *result = nullptr;

        while (!frontier.isEmpty()) {
            result = frontier.dequeue();

            if (result->vertex == destination) {
                return result;
            }

            result->expand(seen);
            // Get the neighbors of the current vertex
            // that we are on...

            // The neighbors are stored in the result->children array
            std::cout << std::endl
                      << "Expanding " << result->vertex->data << std::endl;

            for (int i = 0; i < result->children.size(); i++) {
                // For every child of the result node
                // If we have not seen it
                // We add it to the frontier (as a queue)
                // We mark it as seen
                if (!seen.search(result->children[i]->vertex->data)) {
                    std::cout << "Adding " << result->children[i]->vertex->data
                              << std::endl;
                    frontier.enqueue(result->children[i]);
                    seen.insert(result->children[i]->vertex->data);
                }
            }

            std::cout << std::endl << "Frontier" << std::endl;

            Link<Waypoint *> *temp = frontier.list.front;
            while (temp != nullptr) {
                std::cout << "(" << temp->data->vertex->data << ","
                          << temp->data->partialCost << ")";
                temp = temp->next;

                if (temp != nullptr) {
                    std::cout << ", ";
                } else {
                    std::cout << std::endl;
                }
            }
            std::cout << std::endl;
        }

        return nullptr;
    }

    Waypoint *dfs(Vertex *start, Vertex *destination) {
        std::cout << "Running Depth-First Search" << std::endl;

        Stack<Waypoint *> frontier;
        HashTable<std::string> seen;

        Waypoint *first = new Waypoint(start);

        frontier.push(first);
        seen.insert(first->vertex->data);

        Waypoint *result = nullptr;

        while (!frontier.isEmpty()) {
            result = frontier.pop();

            if (result->vertex == destination) {
                return result;
            }

            result->expand(seen);

            std::cout << std::endl
                      << "Expanding " << result->vertex->data << std::endl;

            for (int i = 0; i < result->children.size(); i++) {
                if (!seen.search(result->children[i]->vertex->data)) {
                    std::cout << "Adding " << result->children[i]->vertex->data
                              << std::endl;
                    frontier.push(result->children[i]);
                    seen.insert(result->children[i]->vertex->data);
                }
            }

            std::cout << std::endl << "Frontier" << std::endl;

            Link<Waypoint *> *temp = frontier.front;
            while (temp != nullptr) {
                std::cout << "(" << temp->data->vertex->data << ","
                          << temp->data->partialCost << ")";
                temp = temp->next;

                if (temp != nullptr) {
                    std::cout << ", ";
                } else {
                    std::cout << std::endl;
                }
            }
            std::cout << std::endl;
        }

        return nullptr;
    }

    Waypoint *ucsPrice(Vertex *start, Vertex *destination) {
    std::cout << "Running Uniform Cost Search" << std::endl;

    ArrayList<Waypoint *> frontier;
    HashTable<std::string> seen;

    Waypoint *first = new Waypoint(start);
    frontier.append(first);
    

    Waypoint *result = nullptr;

    while (frontier.size() != 0) {
        result = frontier.removeLast();

        // Mark as seen when we expand it
        if (seen.search(result->vertex->data)) {
            continue; 
        }
        seen.insert(result->vertex->data);

        if (result->vertex == destination) {
            return result;
        }

        result->expand(seen);

        std::cout << "Expanding " << result->vertex->data << std::endl;

        for (int i = 0; i < result->children.size(); i++) {
            // Look at each child
            if (!seen.search(result->children[i]->vertex->data)) {
                // Check if already in frontier with worse cost
                Waypoint *worsePath = nullptr;
                
                for (int k = 0; k < frontier.size(); k++) {
                    if (frontier[k]->vertex->data ==
                        result->children[i]->vertex->data) {
                        if (frontier[k]->totalPrice >
                            result->children[i]->totalPrice) {
                            worsePath = frontier[k];
                            break;
                        }
                    }
                }

                if (worsePath) {
                    // Replace worse path
                    std::cout << "Found another way to get to "
                              << result->children[i]->vertex->data << ". Was "
                              << worsePath->totalPrice << ", but now it is "
                              << result->children[i]->totalPrice << std::endl;

                    for (int k = 0; k < frontier.size(); k++) {
                        if (frontier[k]->vertex->data ==
                            result->children[i]->vertex->data) {
                            delete frontier[k];
                            frontier[k] = result->children[i];
                            break;
                        }
                    }

                    // Re-sort the entire frontier
                for (int a = 0; a < frontier.size() - 1; a++) {
                    for (int b = a + 1; b < frontier.size(); b++) {
                        if (frontier[b]->totalPrice > frontier[a]->totalPrice) {
                            Waypoint *temp = frontier[a];
                            frontier[a] = frontier[b];
                            frontier[b] = temp;
                        }
                    }
                }
                } else {
                    // Add new node
                    std::cout << "Adding " << result->children[i]->vertex->data
                              << std::endl;
                    frontier.append(result->children[i]);

                    // Sort the frontier
                    int j = frontier.size() - 1;
                    while (j > 0 && frontier.data[j]->totalPrice 
                                       > frontier.data[j - 1]->totalPrice) {
                        Waypoint *temp = frontier.data[j];
                        frontier.data[j] = frontier.data[j - 1];
                        frontier.data[j - 1] = temp;
                        j--;
                    }
                }
            }
        }

        std::cout << std::endl << "Frontier" << std::endl;

        for (int k = frontier.size() - 1; k >= 0; k--) {
            std::cout << "(" << frontier[k]->vertex->data << ", "
                      << frontier[k]->totalPrice << ") ";
            if (k > 0) {
                std::cout << ", ";
            } else {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }

    return nullptr;
}
    Waypoint* ucsTime(Vertex* start, Vertex* destination) {
    std::cout << "Running Uniform Cost Search (Time)" << std::endl;

    ArrayList<Waypoint*> frontier;
    HashTable<std::string> seen;

    Waypoint* first = new Waypoint(start);
    frontier.append(first);

    Waypoint* result = nullptr;

    while (frontier.size() != 0) {
        result = frontier.removeLast();
        std::cout << "*** Removed from frontier: " << result->vertex->data << " (time: " << result->totalTime << ") ***" << std::endl;

        // Mark as seen when we expand it
        if (seen.search(result->vertex->data)) {
            continue; 
        }
        seen.insert(result->vertex->data);

        if (result->vertex == destination) {
            return result;
        }

        result->expand(seen);

        std::cout << "Expanding " << result->vertex->data << std::endl;

        for (int i = 0; i < result->children.size(); i++) {
            // Look at each child
            if (!seen.search(result->children[i]->vertex->data)) {
                // Check if already in frontier with worse cost
                Waypoint *worsePath = nullptr;
                
                for (int k = 0; k < frontier.size(); k++) {
                    if (frontier[k]->vertex->data ==
                        result->children[i]->vertex->data) {
                        if (frontier[k]->totalTime >
                            result->children[i]->totalTime) {
                            worsePath = frontier[k];
                            break;
                        }
                    }
                }

                if (worsePath) {
                    // Replace worse path
                    std::cout << "Found another way to get to "
                              << result->children[i]->vertex->data << ". Was "
                              << worsePath->totalTime << ", but now it is "
                              << result->children[i]->totalTime << std::endl;

                    for (int k = 0; k < frontier.size(); k++) {
                        if (frontier[k]->vertex->data ==
                            result->children[i]->vertex->data) {
                            delete frontier[k];
                            frontier[k] = result->children[i];
                            break;
                        }
                    }

                    // Re-sort the entire frontier
                    for (int a = 0; a < frontier.size() - 1; a++) {
                        for (int b = a + 1; b < frontier.size(); b++) {
                            if (frontier[b]->totalTime > frontier[a]->totalTime) {
                                Waypoint *temp = frontier[a];
                                frontier[a] = frontier[b];
                                frontier[b] = temp;
                            }
                        }
                    }
                } else {
                    // Add new node
                    std::cout << "Adding " << result->children[i]->vertex->data
                              << std::endl;
                    frontier.append(result->children[i]);

                    // Sort the frontier
                    int j = frontier.size() - 1;
                    while (j > 0 && frontier[j]->totalTime > frontier[j - 1]->totalTime) {
                        Waypoint* temp = frontier[j];
                        frontier[j] = frontier[j - 1];
                        frontier[j - 1] = temp;
                        j--;
                    }
                }
            }
        }

        std::cout << std::endl << "Frontier" << std::endl;

        for (int k = frontier.size() - 1; k >= 0; k--) {
            std::cout << "(" << frontier[k]->vertex->data << ", "
                      << frontier[k]->totalTime << ") ";
            if (k > 0) {
                std::cout << ", ";
            } else {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }

    return nullptr;
}
};

        

inline std::ostream &operator<<(std::ostream &os, const Graph &g) {
    for (int i = 0; i < g.vertices.size(); i++) {
        os << g.vertices[i]->edgeList << std::endl;
    }

    return os;
}

#endif