#ifndef BUTTON_H
#define BUTTON_H
#include <string>
#include <algorithm>
using namespace std;

class Button {
public:
    double topLeftX;
    double topLeftY;
    double bottomRightX;
    double bottomRightY;
    string buttonLabel;
    void (*onHoverFunc)(void);
    void (*onClickFunc)(void);
    /**
        Default constructor, returns a pointer to an empty Button object
        @param void
        @param a pointer to a new Button object
    */
    Button();
    /**
        Function to render the button
        @param void
        @return void
    */
    render();
}
#endif
