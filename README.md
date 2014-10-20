# Curves
### a simple vector graphics editor in C++

uses deprecated versions of GLUT and OpenGL
to draw various line geometries in the 2d plane.

## Implementation details

I pursed the implementation of this project a bit differently from the specifications on the original assignment. Rather than sticking to the stateless, key-press based control scheme, I decided to create a staeful manager for the application as well as a wondw manager in order to play around with things such as buttons and tool bars in a way similar to the implementation I have seen in actual systems.
All the key-based controls and changes in state are handled by the ToolWindow class.Curves for the application and other application-wide state information is encapsulated by the StateManager class. The Mindow Manager keeps a stack of Windows that it draws iteratively on each idle of the application (it would be more efficient to implement a polling-based redrawing rather than forcing it to happen on every call to on-idle). Views are transformed to fit their origin and scale and are drawn by windows that encapsulate them.

## Class Structure
- WindowManager
    - handles maintaining the window stack and passing glut function calls to the window stack
- StateManager
    - keeps track of the various application states that need to be accessed across multiple pieces of the application
    - also will keep track of the curves in the application currently
- Window
    - superclass of all the windows, contains functionality to transform the contents to fit within the origin and scale
    - contains virtual function definitions for the methods which handle GLUT events coming from the WindowManager
    - DrawWindow
        - displays the curves and lines held by the state manager, allows for their editing by interfacing with the methods on the curves
    - ToolWindow
        - displays the various tools available within the application
        - modifies application state on button clicks
- View
    - superclass of all the various views within the application
    - provides bounding functionality based on origin and scale values
    - ToolView
        - is associated with a `ToolType` value and displays its associated text representation
- Curve
    - pure virtual superclass of all curves, provides basic drawing functionality based on virtual methods
    - Freeform
        - virtual superclass of all the curves that contain control points


## Scoring

### Points
55 pts for a D,
65 pts for a C,
75 pts for a B,
85 pts for an A.

### Scoring metrics
- Select control points through clicks. [5 pts]
- Object at the mouse cursor becomes selected if clicked. [15 pts if this works approximately, (*) 25 pts if this works exactly]
    - implement line clipping, and clip objects to a small window around the cursor (knowledge-hungry student's way)
    - use OpenGL selection mode (OpenGL expert way)
- Support Catmull-Clark subdivision curves, created by clicking control points while holding key 'C'. [20 pts]
- Support Catmull-Rom splines, created by clicking control points while holding key 'R'. [25 pts]
- Support cubic Hermite interpolation splines. Derivatives at control points should be manually editable. Extra controls should be displayed to allow the user to adjust derivatives. [(*) 35 pts]
- Support dragging control points of the selected curve. [10 pts]
- When an object is selected, pressing the 'F' key to fill it. [5 pts if it works for convex shapes, (*) 20 pts if it works for non-self-intersecting curves, (*) 25 points if it works for any curve]
- Display the current number of curves in the corner using Bezier curves to form the numbers (steal control points from http://jackf.net/bezier-clock/) [20 pts]
