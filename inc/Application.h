#ifndef APPLICATION_H
#define APPLICATION_H

#include <FL/Fl_Radio_Button.H>
#include <bobcat_ui/bobcat_ui.h>
#include <bobcat_ui/button.h>
#include <bobcat_ui/dropdown.h>
#include <bobcat_ui/window.h>
#include <bobcat_ui/checkbox.h>
#include <Graph.h>

#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>

class Application : public bobcat::Application_ {
    bobcat::Window *window;
    bobcat::Dropdown *start;
    bobcat::Dropdown *dest;
    bobcat::Button *search;

    Fl_Text_Display *outputDisplay;
    Fl_Text_Buffer *outputBuffer;

    Fl_Radio_Button *cheapest;
    Fl_Radio_Button *shortestTime;
    Fl_Radio_Button *leastStops;

    Graph graph;

public:
    Application(); // Constructor for the app

    void loadVerticesFromFile(const std::string& filename);

    void loadGraphFromFile(const std::string& filename);

    void populateDropdowns();

    void enforceOneFilter(Fl_Radio_Button* selected);

    void onSearchClicked(bobcat::Widget* sender);
};

#endif