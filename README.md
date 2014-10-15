# Curves
### a simple vector graphics editor in C++

uses deprecated versions of GLUT and OpenGL
to draw various line geometries in the 2d plane.


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


## Scoring

### Points
55 pts for a D,
65 pts for a C,
75 pts for a B,
85 pts for an A.

###
- When an object is selected, the user may hold down 'A' to add control points to the selected object by clicking. [5 pts]
- Support Catmull-Clark subdivision curves, created by clicking control points while holding key 'C'. [20 pts]
- Support dragging control points of the selected curve. [10 pts]