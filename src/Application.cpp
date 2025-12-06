#include <Application.h>
#include <bobcat_ui/button.h>
#include <bobcat_ui/checkbox.h>
#include <bobcat_ui/dropdown.h>
#include <bobcat_ui/window.h>

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

    window->show();
}