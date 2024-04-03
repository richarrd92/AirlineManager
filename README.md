# AirlineManager ( Using LinkedList )

This project aims to develop a tool for designing routes for a new airline, considering the cost of fuel by calculating distances between airports. 
The tool utilizes provided files including Airport.h, Route.h, Navigator.h, makefile, proj3.cpp, and an input file (proj3_data.txt). 
The project must be implemented in C++ using only specified libraries and data structures taught in class.

# Description:

The assignment requires building an application enabling users to create multiple routes, each comprising at least two airports.

# Requirements:

The project must be implemented in C++ using only specified libraries and data structures.
The provided function prototypes in Airport.h, Route.h, and Navigator.h header files must be used without editing them.
Input is facilitated through a file (proj3_data.txt) containing airport information.

# Key Components:

Airport Class:
Represents an airport with data including code, name, city, country, latitude, longitude, and a pointer to the next airport.
Provides constructors, setters, getters, and an overloaded << operator.

Route Class:
Manages routes composed of airports, tracking route name, start, end, and size.
Offers methods for route manipulation such as insertion, reversal, removal, and distance calculation.

Navigator Class:
Handles file loading, user input, and route management.
Utilizes vectors to store routes and airports, and manages the input file.
Provides a menu for creating, displaying, modifying, and calculating routes.

# User Interaction:

Users interact with the application through a menu-driven interface offering options for creating routes, displaying routes, removing airports, reversing routes, and exiting.
All user inputs are assumed to be of the correct data type, and input validation is enforced.
This project emphasizes adherence to specified guidelines, utilization of provided classes and functions, and implementation of route management functionalities within the designated programming paradigm.
