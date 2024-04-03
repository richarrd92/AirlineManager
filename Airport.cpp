
#include "Airport.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

  // Airport
  // creates default airport object
  Airport::Airport(){
    m_north = 0;
    m_west = 0;
    m_next = nullptr;
  }

  // Airport
  // Creates an airport object
  Airport::Airport(string code, string name, string city, string country, double north, double west){
    m_code = code; 
    m_name = name; 
    m_city = city; 
    m_country = country; 
    m_north = north; 
    m_west = west;
    m_next = nullptr;
  }

  // ~Airport
  // Deallocate dynamically allocated airport objects
 Airport::~Airport(){
  // Left Empty on purpose   
 }

  // GetCode
  // Given airport, Returns the three letter code of the airport
  string Airport::GetCode(){
    return m_code;
  }

  // GetName
  // Given airport, Returns the name of the airport
  string Airport::GetName(){
    return m_name;
  }

  // Name: GetNext
  // Given aiport, Returns m_next
  Airport* Airport::GetNext(){
    return m_next;
  }

  // GetNorth
  // given airport, Returns the N coordinates of the airport
  double Airport::GetNorth(){
    return m_north;
  }

  // GetWest
  // given airport, Returns the W coordinates of the airport
  double Airport::GetWest(){
    return m_west;
  }

  // GetCity
  // given airport, Returns the city of where the airport is located
  string Airport::GetCity(){
    return m_city;
  }

  // GetCountry
  // given airport, Returns the country of where the airport is located
  string Airport::GetCountry(){
    return m_country;
  }

  // SetNext
  // given airport, Sets the next airport
  void Airport::SetNext(Airport* airport){
    m_next = airport;
  }

