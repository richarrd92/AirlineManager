
#include "Airport.h"
#include "Route.h"
#include "Navigator.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
using namespace std;


  // Navigator 
  // Given file name, creates navigator object to manage routes and airports
  Navigator::Navigator(string fileName){
    m_fileName = fileName; 
  }

  // Navigator
  // given routes and airports, clears all routes and airports
  Navigator::~Navigator(){

    // iterates through vector m_airports
    for(unsigned int i = 0; i < m_airports.size(); i++){
      delete m_airports[i]; 
    }

    // iterates through vector m_routes
    for(unsigned int i = 0; i < m_routes.size(); i++){
      delete m_routes[i]; 
    }


    // memory check prompts at end of program
    cout << "Routes removed from memory" <<endl;
    cout << "Deleting Airports" <<endl;
    cout << "Deleting Routes" <<endl;
    cout << "_____________________________________________________________________" <<endl;
  }

  // Start
  // calls ReadFile and MainMenu functions
  void Navigator::Start(){
    Navigator::ReadFile(); 
    Navigator::MainMenu(); 
  }

  // DisplayAirports
  // Given vector of at least one airport or more, displays all airports in vector
  // Uses overloaded << provided in Airport.h
  void Navigator::DisplayAirports(){
    cout <<endl;
    for(unsigned int i = 0; i < m_airports.size(); i++){
      cout << i+1 << ".  "<< *m_airports[i] <<endl;
    }   
  }

  // ReadFile
  // given Valid file name of airports, reads file
  // Dynamically allocates each airport and enters it into m_airports
  void Navigator::ReadFile(){

    fstream myFile;

    // opens file
    myFile.open(m_fileName); 
     
    // iterates through file line by line 
    string line; 

    if (myFile.is_open())
    {
      cout << "FILE LOADED SUCCESSFULLY..." <<endl;

      while (getline(myFile, line)) 
      {
          // Find the positions of commas
          int pos1 = line.find(',');
          int pos2 = line.find(',', pos1 + 1);
          int pos3 = line.find(',', pos2 + 1);
          int pos4 = line.find(',', pos3 + 1);
          int pos5 = line.find(',', pos4 + 1);


          // Extract substrings based on comma positions
          string code = line.substr(0, pos1);
          string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
          string city = line.substr(pos2 + 1, pos3 - pos2 - 1);
          string country = line.substr(pos3 + 1, pos4 - pos3 - 1);
          double north = stod(line.substr(pos4 + 1, pos5 - pos4 - 1));
          double west = stod(line.substr(pos5 + 1));

          // Dynamically allocates airports
          Airport* airport = new Airport(code,name,city,country,north,west); 

          // Add airports to vector of all airports
          m_airports.push_back(airport); 
      }

      cout << "Airports loaded: 40" <<endl; 
    }  

    // Close the file
    myFile.close(); 
  }

  // InsertNewRoute
  // Dynamically allocates a new route of 2 or more airports 
  void Navigator::InsertNewRoute(){

    Navigator::DisplayAirports(); 
    cout <<endl;

    // stores user selected airports
    vector<int> userRouteChoices; 
    int userInput;

    do
    {
      cout << "Enter the number of the airport to add to your Route (Enter -1 to end): ";
      cin >> userInput;

      // validates userInput
      while((userInput < 1 || userInput > 40) && userInput != -1){
          cout << "\nERROR: OUT OF BOUNDS!" <<endl << "Enter the number of the airport to add to your Route (Enter -1 to end): ";
          cin >> userInput;
      }

      // ignores -1 UserInput
      if (userInput != -1){
        userRouteChoices.push_back(userInput-1); 
      }
      
    }while(userInput != -1);

    cout <<endl;

    // validates route size
    if(userRouteChoices.size() > 1){

        // Dynamically creates new route object
        Route* route = new Route;

        for(unsigned int i = 0; i < userRouteChoices.size(); i++){
          string code = m_airports[userRouteChoices[i]]->Airport::GetCode();
          string name = m_airports[userRouteChoices[i]]->Airport::GetName(); 
          string city = m_airports[userRouteChoices[i]]->Airport::GetCity();
          string country = m_airports[userRouteChoices[i]]->Airport::GetCountry();
          double north = m_airports[userRouteChoices[i]]->Airport::GetNorth();
          double west = m_airports[userRouteChoices[i]]->Airport::GetWest();

          // inserts and updates route name
          route->InsertEnd(code, name, city, country, north, west); 
        }

        // stores route into m_route
        m_routes.push_back(route); 
        cout << "DONE BUILDING ROUTE: " << route->Route::GetName() <<endl; 
    }

    else{
      cout << "NEED A MINIMUM OF 2 AIRPORTS IN A ROUTE" <<endl;
    }
  }

  // MainMenu
  // Displays the main menu and manages exiting
  void Navigator::MainMenu(){

    int userChoice;
    do
    {
      cout <<endl;
      cout << "What would you like to do?:" <<endl <<endl;
      cout << "1. Create New Route" <<endl;
      cout << "2. Display Route" <<endl;
      cout << "3. Remove Airport From Route" <<endl;
      cout << "4. Reverse Route" <<endl; 
      cout << "5. Exit" <<endl;
      cout << "Option: ";
      cin >> userChoice;

      // validates userChoice
      while(userChoice < 1 && userChoice > 5)
      {
        cout << "\nERROR: ERROR: OUT OF BOUNDS" <<endl;
        Navigator::MainMenu();
      }

      switch(userChoice)
      {
            case 1:   Navigator::InsertNewRoute();          break;
            case 2:   Navigator::DisplayRoute();            break; 
            case 3:   Navigator::RemoveAirportFromRoute();  break; 
            case 4:   Navigator::ReverseRoute();            break;

            // Sets userChoice -> 5 
            case 5:   userChoice = 5;                       break; 
      }

    }while(userChoice != 5);

    cout <<endl;
  }

  // ChooseRoute
  // User chooses a specific route to work with, Returns the index of the selected route
  int Navigator::ChooseRoute(){

    int userChoice; 
    cout << "Which route would you like to use?" <<endl; 

    // prints out all routes in m_routes
    for(unsigned int i = 0; i < m_routes.size(); i++){
      cout << i+1 << ".  " << m_routes[i]->GetName() <<endl;                       
    }  

    cout << "Route: ";
    // Route selected by user
    cin >> userChoice; 

    // validates user input
    while(userChoice < 1 || userChoice > int(m_routes.size())){
        cout << endl << "ERROR: OUT OF BOUNDS! " <<endl << "Which route would you like to use?" <<endl; 

        // prints out all routes in m_routes
        for(unsigned int i = 0; i < m_routes.size(); i++){
          cout << i+1 << ".  " << m_routes[i]->GetName() <<endl;                       
        }  

        cout << "Route: ";
        // Route selected by user
        cin >> userChoice; 
    }

    // Returns the index of the selected route
    return (userChoice-1); 
  }

  // DisplayRoute
  // Displays all airports in the selected route with the total distance
  void Navigator::DisplayRoute(){

    cout << endl;
    if(m_routes.size() == 0){
      cout << "ROUTE IS EMPTY!" <<endl;
    } 
    
    // route contains airports
    else {

      // calls ChooseRoute and stores the index it returns
      int selectedRoute = Navigator::ChooseRoute(); 

      // pointer to point to the selected route
      Route* tempRoute = nullptr; 

      // stores user selected route in tempRoute 
      tempRoute = m_routes[selectedRoute]; 

      // prints selected route name
      cout << endl << tempRoute->GetName() <<endl; 
      tempRoute->DisplayRoute(); 

      // outputs total distance of route
      cout <<endl << "TOTAL ROUTE DISTANCE: " << RouteDistance(tempRoute) << " miles" <<endl; 

    }
  }

  // RemoveAirportFromRoute
  // Given route has more than 2 airports
  // Removes airport at selected index in route, then updates route name
  void Navigator::RemoveAirportFromRoute(){
    cout << endl;
    if(m_routes.size() == 0){
      cout << "ROUTE IS EMPTY!" <<endl;
    }
    
    // route contains airports
    else {

      // pointer to point to selected route
      Route* tempRoute = nullptr; 

      // calls ChooseRoute and stores the index it returns
      int selectedRoute = Navigator::ChooseRoute(); 

      // stores user selected route in tempRoute       
      tempRoute = m_routes[selectedRoute]; 

      // Validates route size
      if(tempRoute->GetSize() > 2)
      {
        cout << endl << tempRoute->GetName() <<endl; 
        tempRoute->DisplayRoute(); 

        int indexOfAirport; 
        cout << "\nWhich airport would you like to remove?" <<endl;
        cout << "Airport: ";
        cin >> indexOfAirport;

        // validates index of selected airport
        while(indexOfAirport < 1 || indexOfAirport > int(tempRoute->GetSize())){
        cout << endl << "ERROR: OUT OF BOUNDS! " <<endl << "Which airport would you like to remove?" <<endl; 
        cout << "Airport: ";
        cin >> indexOfAirport;
        }

        // passes the index into RemoveAirport function 
        tempRoute->RemoveAirport(indexOfAirport-1);
      } 
      
      // routes has 2 airports
      else{
        cout << "\nROUTE CAN'T HAVE LESS THAN 2 AIRPORTS" <<endl;
      }
    }
  }

  // RouteDistance
  // Given route has 2 or more routes
  // Calculates and returns the total distance of route
  double Navigator::RouteDistance(Route* route){

    // sum of route distance
    double routeDistance = 0; 

    for(int i = 0; i < route->GetSize()-1; i++){
        routeDistance += CalcDistance( route->Route::GetData(i)->GetNorth(), 
                                       route->Route::GetData(i)->GetWest(), 
                                       route->Route::GetData(i+1)->GetNorth(), 
                                       route->Route::GetData(i+1)->GetWest()   );
    }

    // returns total route distance
    return routeDistance; 
  }

  // ReverseRoute
  // Given ropute has two or more airports 
  // reverse the route and updates name of route
  void Navigator::ReverseRoute(){
    cout << endl;
    if(m_routes.size() == 0){
      cout << "ROUTE IS EMPTY!" <<endl;
    } 

    // route contain airports
    else {

      // pointer to point to selected route
      Route* tempRoute = nullptr;  

      // calls ChooseRoute and stores the index it returns
      int selectedRoute = Navigator::ChooseRoute(); 

      // stores user selected route in tempRoute 
      tempRoute = m_routes[selectedRoute]; 

      // reverses selected route
      tempRoute->ReverseRoute();
      cout << "\nDone reversing Route " << tempRoute->GetName() <<endl; 

    }  
  }

  // CalcDistance 
  //  Given two airports with their N (in degrees) and W (in degrees)
  // Returns distance in miles between two airports
  double CalcDistance(double airport1_north, double airport1_west,
		      double airport2_north, double airport2_west) {
    double lat_new = airport2_north * DEG_2_RAD;
    double lat_old = airport1_north * DEG_2_RAD;
    double lat_diff = (airport1_north-airport2_north) * DEG_2_RAD;
    double lng_diff = (airport1_west-airport2_west) * DEG_2_RAD;

    double a = sin(lat_diff/2) * sin(lat_diff/2) +
      cos(lat_new) * cos(lat_old) *
      sin(lng_diff/2) * sin(lng_diff/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    return double(EARTH_RADIUS) * c;
  }
