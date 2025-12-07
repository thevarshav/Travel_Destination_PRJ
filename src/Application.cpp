#include <Application.h>
#include <bobcat_ui/bobcat_ui.h>
#include <bobcat_ui/button.h>
#include <bobcat_ui/checkbox.h>
#include <bobcat_ui/dropdown.h>
#include <bobcat_ui/window.h>
#include <iostream>
#include <Graph.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace bobcat;
using namespace std;

Application::Application(){
    // App's constructor
    window = new Window(100, 100, 400, 500, "Destination Flight Planner");

    start = new Dropdown(20, 40, 360, 25, "Starting Point");
    dest = new Dropdown(20, 100, 360, 25, "Destination");
    
    cheapest = new Checkbox(20, 160, 150, 25, "Cheapest Price");
    shortestTime = new Checkbox(20, 190, 150, 25, "Shortest Time");
    leastStops = new Checkbox(20, 220, 150, 25, "Fewest Stops");

    search = new Button(20, 260, 360, 25, "Search");

    outputBuffer = new Fl_Text_Buffer();

    outputDisplay = new Fl_Text_Display(20, 320, 360, 150, "Flight Results:");
    outputDisplay->buffer(outputBuffer);
    outputDisplay->textsize(14);

    loadVerticesFromFile("assets/vertices.csv");
    loadGraphFromFile("assets/edges.csv");
    populateDropdowns();


    window->show();
}
//Load airports from vertices.csv
void Application::loadVerticesFromFile(const std::string& filename){
    ifstream file(filename);
    if (!file.is_open()){
        cout << "Could not open vertices file: " << filename << endl;
        return;
    }

    string line;
    while(getline(file, line)){
        if(line.empty()) continue;
        graph.getOrCreateVertex(line);
    }
    file.close();

}
//Load edges from edges.csv
void Application::loadGraphFromFile(const string& filename){
    ifstream file(filename);
    if (!file.is_open()){
        cout << "Could not open edges file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        int fromIndex, toIndex;
        double time, price;
        char comma;

        ss >> fromIndex >> comma >> toIndex >> comma >> time >> comma >> price;

        if (fromIndex >= 0 && fromIndex < graph.vertices.size() &&
            toIndex >= 0 && toIndex < graph.vertices.size()) {
            Vertex* vFrom = graph.vertices[fromIndex];
            Vertex* vTo   = graph.vertices[toIndex];
            graph.addDirectedEdge(vFrom, vTo, price, time);
        }
    }


    file.close();
}

void Application::populateDropdowns() {
    start->clear();
    dest->clear();

    for (int i = 0; i < graph.vertices.size(); i++) {
        Vertex* v = graph.vertices[i];
        start->add(v->data.c_str());
        dest->add(v->data.c_str());
    }
}