#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/bobcat_ui.h>
#include <bobcat_ui/button.h>
#include <bobcat_ui/dropdown.h>
#include <bobcat_ui/window.h>
#include <bobcat_ui/checkbox.h>

#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>

class Application : public bobcat::Application_ {
    bobcat::Window *window;
    bobcat::Dropdown *start;
    bobcat::Dropdown *dest;
    bobcat::Checkbox *cheapest;
    bobcat::Checkbox *shortestTime;
    bobcat::Checkbox *leastStops;

    bobcat::Button *search;

    Fl_Text_Display *outputDisplay;
    Fl_Text_Buffer *outputBuffer;

public:
    Application(); // Constructor for the app
};

#endif