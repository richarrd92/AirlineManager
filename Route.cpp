/*****************************************
** File:    Route.cpp
** Project: CMSC 202 Project 3, Spring 2024
** Author:  Richard Maliyetu
** Date:    4/02/24
** Section: 33
** E-mail:  r215@gl.umbc.edu 
** E-mail:  r215@umbc.edu 
**
** This file contains the implementation of the route class
** the route class is the linked list of airports
** the file contains functions;
** To insert airport at the end of route
** To remove airport at any given index in the route
** To reverse the route and so much more
** more info in the project description.
***********************************************/

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "Airport.h"
#include "Route.h"
using namespace std;


  // Route
  // Creates Route Object
  Route::Route(){
     m_name = "Test"; 
     m_head = nullptr; 
     m_tail = nullptr; 
     m_size = 0; 
  }

  // SetName
  // Sets the name of the route 
  void  Route::SetName(string name){
    m_name = name; 
  }

  // ~Route
  // Given there is a route, Route is deallocated
 Route::~Route(){
    // pointer to point to m_head
    Airport *temp = m_head;  

    // deallocate until last airport in route
    while(m_head != nullptr){
      temp = m_head->GetNext(); 
      delete m_head;
      m_head = temp;
      temp = nullptr;
    }

    //Resets all of the static linked list pointers
    m_head = nullptr; 
    m_tail = nullptr; 
    m_size = 0; 
 }

  // InsertEnd 
  // Given airport, inserts airport at end of route
  void Route::InsertEnd(string code, string name, string city, string country, double north, double west){
    
    // dynamically creates new airport
    Airport *temp = new Airport(code, name, city, country, north, west); 
    
    // case 1: route is empty 
    if(m_head == nullptr){ 
      m_head = temp; 
      m_tail = temp; 
      Route::UpdateName();
    }

    // case 2: route contains 1 or more airports
    else{
      m_tail->Airport::SetNext(temp); 
      m_tail = temp;
      Route::UpdateName();
    }

    //Increments the size of the linked list    
    m_size++; 
  }

  // RemoveAirport
  // Given valid index and route has more than 2 airports
  // removes airport at given index, updates name (if necessary) and route size
  void Route::RemoveAirport(int airport){

        // temp pointer to point to m_head 
        Airport *tempAirport = m_head;

        // gets the airport in the route at given index
        for(int i = 0; i < m_size; i++){

          // compares passed integer (airport) to i          
          if(airport == i){ 
            break;
          }
          
          // iterates to next airport in route
          else{
               tempAirport = tempAirport->GetNext();  
          }
        }

        // Poiints to found airport after iteration
        Airport *temp = nullptr; 

        Airport *prev = m_head;
        Airport *curr = m_head->GetNext();

        // case 1: airport is found at the start of route
        if (m_head->GetCity() == tempAirport->GetCity())
        {
          cout <<endl << tempAirport->GetCity() << " AIRPORT REMOVED FROM ROUTE" << endl; 
          temp = curr;
          curr = nullptr;
          m_head = temp;
          delete prev;
          Route::UpdateName(); // re-updates route name
          m_size--;
          return;
        }

        // case 2: airport is found in the middle or end of route
        else
        {
          // iterates until end of route
          while (curr != nullptr)
          {

            // Case 1: last airport in route
            if(curr->GetNext() == nullptr){
                temp = prev;
                m_tail = temp;
                cout <<endl << curr->GetCity() << " AIRPORT REMOVED FROM ROUTE" << endl; 
                delete curr;
                prev->SetNext(nullptr);
                Route::UpdateName(); // re-updates route name
                m_size--;
                return;           
            }  


            // Case 2: airport in the middle
            else if (curr->GetCity() == tempAirport->GetCity()){
              cout <<endl << curr->GetCity() << " AIRPORT REMOVED FROM ROUTE" << endl; 
              prev->SetNext(curr->GetNext());
              delete curr;
              Route::UpdateName(); // re-updates route name
              m_size--;
              return;                
            }

            // keeps iterating through route
            prev = curr;
            curr = curr->GetNext();

          }
        }
  }

  // GetName
  // Given route, returns name of route
  string Route::GetName(){
    return m_name;
  }

  // UpdateName
  // Given route has 2 or more airports, updates name of route
  string Route::UpdateName(){

    string firstName, lastName, routeName;
    firstName = m_head->GetCity();
    lastName = m_tail->GetCity();
    
    // new updated name stored in RouteName 
    routeName = firstName + " to " + lastName;
    Route::SetName(routeName);
    m_name = routeName;

    return m_name; // updated route name
  }

  // GetSize
  // Given Route, Returns m_size
  int Route::GetSize(){
    return m_size;
  }

  // ReverseRoute
  // Given route, reverses route
  void Route::ReverseRoute(){

      // ptr1 -> ptr2 -> ptr3 ->
      Airport *ptr1, *ptr2, *ptr3; 

      ptr1 = m_head;
      ptr2 = ptr1->GetNext();
      ptr3 = ptr2->GetNext();
      ptr1->SetNext(nullptr);
      ptr2->SetNext(ptr1);

      // keeps iterating through route until last airport
      while (ptr3 != nullptr)
      {
          ptr1 = ptr2;
          ptr2 = ptr3;
          ptr3 = ptr3->GetNext();
          ptr2->SetNext(ptr1);         
      }

      // m_tail becomes is the original routes m_head
      m_tail = m_head; 

      // ptr2 points to m_tail of original route      
      m_head = ptr2;

      // re-updates route name
      Route::UpdateName(); 
  }

  // GetData
  // Given index, Returns the airport from specific route
  Airport* Route::GetData(int index){

    // points to found airport
    Airport* temp = nullptr; 

    Airport* curr = m_head; 

    for(int i = 0; i < m_size; i++){

        if(index == i){
          temp = curr; 

          // returns found airport
          return temp; 
        }

        // Keeps iterating through linked list
        curr = curr->GetNext();
    }

    // returns nullptr if airport not found
    return nullptr; 
  }

  // DisplayRoute
  // Given a Route, Displays all of the airports in a route
  // Formatted: Baltimore, Maryland (N39.209 W76.517)
  void Route::DisplayRoute(){

    // pointer to iterate over route
    Airport *temp = m_head; 
    
    for(int i = 0; i < m_size; i++){ 
      
        //Formatted: Baltimore, Maryland (N39.209 W76.517)
        cout << i+1 <<  ".  " << temp->GetCity()    << ", "
                              << temp->GetCountry() << " (W"
                              << temp->GetNorth()   << " N"
                              << temp->GetWest()    << ")" <<endl;

        //Moves to m_next (next airport)                            
        temp = temp->GetNext(); 
    }
  }