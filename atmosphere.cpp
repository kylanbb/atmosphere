/*
 * Author: Kylan Byrd
 * Date: V-1.0: 10/18/2017
 * Compile with g++ -std=c++11 -Wall -o atmosphere_functions atmosphere_functions.cpp
 *
 * Find the level of the atmosphere for a given altitude. Accepts miles or kilometers.
 */

//Include libraries
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#define NDEBUG
#include <cassert>
#include "atmosphere.h"


int main()
{
    using namespace std;

    atexit( onExit );

    //Set output format to be xx.xx.
    cout.setf( ios::fixed );
    cout.setf( ios::showpoint );
    cout.precision( 2 );
    
    int unit; //Declare variable to store the users unit choice.
    float height; //Declare vairable to store the users height input.
    
    if( GetUnit( unit ) ); //Retrieve preferred unit of measure.
    {
        cout << "Thank you for selecting a unit." << endl; //If successful, thank the user and continue.
    }
    else
    {
        exit( EXIT_FAILURE ); //If unsuccessful, exit the program.
    }
    
    if( GetHeight( height ) ); //Retreive Altitude.
    {
        cout << "Thank you for choosing a valid height. Now calculating the atmospheric layer." << endl; //If successful, thank the user and continue.
    }
    else
    {
        exit( EXIT_FAILURE ); //If unsuccessful, exit the program.
    }

    cout << height << GetLayer( unit, height ) << endl; //Inform the user the atmospheric layer based on the unit type and height they selected.
    
    exit( EXIT_SUCCESS ); //Exit the program.
}

//Event handler for application exit.
void onExit()
{
    using namespace std;

    cout << "Exiting the application now." << endl; //Print the message to user when the program closes.
}

//Declare function to choose unit of measure.
bool GetUnit(int& unit)
{
    //Allow user to choose unit of measure, max five attempts.
    for( int i = 0; i < 5; i++ ) 
    {
        bool isValid; //Declare a variable to store whether the input is valid or not.
        std::cout << messages::unit::REQUEST << std::endl; //Request unit of measure.
        std::cin >> unit; //Collect user's choice.
        
        if( cin_test() ) //Tests whether the user input a number or not.
        {
            isValid = false; //If user did not put in a number, set isValid to false.
        }
        else if( unit != values::unit::MILES && unit != values::unit::KILOMETERS ) //Test to see if the number corresponds to either unit of measurement.
        {
            isValid = false; //If user put in an invalid number, set isValid to false.
        }
        else if( unit == values::unit::MILES || unit == values::unit::KILOMETERS ) //Double check that user did indeed put in a valid number.
        {
            isValid = true; //If the number corresponds to miles or kilometers, set isValid to true.
        }
        else
        {
            std::exit( EXIT_FAILURE ); //Should never get here, but just in case have a back up.
        }

        if( isValid ) //Check if user selected a valid unit of measure.
        {
            return isValid; //If user did select a valid unit of measure, return true.
        }
        else
        {
            if( i == 4 ) //Check if the user is out of attempts.
            {
                std::cout << messages::OUT_OF_TRIES << std::endl; //If the user is out of attempts, alert the user.
                std::exit( EXIT_SUCCESS ); //Additionally, exit the program.
            }
            else
            {
                std::cout << messages::unit::INVALID << std::endl; //If the user is not out of attempts, alert the user it was invalid and run the loop again.
            }
        }
    }
    std::exit( EXIT_FAILURE ); //Shouldn't be possible to get here, but just in case a failsafe.
}

//Declare function to retrieve altitude.
bool GetHeight(float& height)
{
    using namespace messages;
    //Allow user to input height, max five attempts.
    for( int i = 0; i < 5; i++ )
    {
        bool isValid; //Declare a variable to store whether the input is valid or not.
        std::cout << height::REQUEST << std::endl; //Request height.
        std::cin >> height; //Retrieves height.

        if( cin_test() ) //Tests that the user input a number.
        {
            isValid = false; //If user did not input a number, set isValid to false.
        }
        else if( height < 0 ) //Verifies that the user input zero or a positive number.
        {
            isValid = false; //If user did not, set isValid to false.
        }
        else if( height >= 0 ) //Double checks that the user did indeed input zero or a positive number.
        {
            isValid = true; //If so, input is valid, set isValid to true.
        }
        else
        {
            std::exit( EXIT_FAILURE ); //Should never get here, but just in case have a back up.
        }

        if( isValid ) //Check if user input a valid height.
        {
            return isValid; //User gave appropriate option, move onto the rest of the program.
        }
        else
        {
            if( i == 4 ) //Check if the user has any more attempts.
            {
                std::cout << OUT_OF_TRIES << std::endl; //If not, inform the user they are out.
                std::exit( EXIT_SUCCESS ); //User ran out of tries, terminate program
            }
            else
            {
                std::cout << height::INVALID << std::endl; //If user has more tries, inform them they put in an invalid height, and begin loop again.
            }
        }

    }
    std::exit( EXIT_FAILURE ); //It should be impossible to get here, but as a failsafe, terminate the program.
}

//Define function to find layer using chosen system
std::string GetLayer( int u, float h )
{
    using namespace values::unit;
    std::string layer;
    switch( u )
    {
        case MILES:      layer = GetLayerM(h);
                         break;
        case KILOMETERS: layer = GetLayerK(h);
                         break;
        default:         std::exit(EXIT_FAILURE);
    }
    return layer;
}

//Define function to find altitude mile layer
std::string GetLayerM( float h )
{
    std::string layer;
    if( h == values::layers::SURFACE )
    {
        layer = messages::layers::miles::SURFACE;
    }
    else if( h <= values::layers::miles::TROPOSPHERE )
    {
        layer = messages::layers::miles::TROPOSPHERE;
    }
    else if( h <= values::layers::miles::STRATOSPHERE )
    {
        layer = messages::layers::miles::STRATOSPHERE;
    }
    else if( h <= values::layers::miles::MESOSPHERE )
    {
        layer = messages::layers::miles::MESOSPHERE;
    }
    else if( h <= values::layers::miles::THERMOSPHERE )
    {
        layer = messages::layers::miles::THERMOSPHERE;
    }
    else if( h <= values::layers::miles::EXOSPEHRE )
    {
        layer = messages::layers::miles::EXOSPHERE;
    }
    else if( h > values::layers::miles::EXOSPEHRE )
    {
        layer = messages::layers::miles::OUTERSPACE;
    }
    else
    {
        exit( EXIT_FAILURE ); //Should never get here, but just in case have a back up
    }
    return layer;
}

//Define function to find altitude kilometer layer
std::string GetLayerK( float h )
{
    std::string layer;
    if( h == values::layers::SURFACE )
    {
        layer = messages::layers::kilometers::SURFACE;
    }
    else if( h <= values::layers::kilometers::TROPOSPHERE )
    {
        layer = messages::layers::kilometers::TROPOSPHERE;
    }
    else if( h <= values::layers::kilometers::STRATOSPHERE )
    {
        layer = messages::layers::kilometers::STRATOSPHERE;
    }
    else if( h <= values::layers::kilometers::MESOSPHERE )
    {
        layer = messages::layers::kilometers::MESOSPHERE;
    }
    else if( h <= values::layers::kilometers::THERMOSPHERE )
    {
        layer = messages::layers::kilometers::THERMOSPHERE;
    }
    else if( h <= values::layers::kilometers::EXOSPEHRE )
    {
        layer = messages::layers::kilometers::EXOSPHERE;
    }
    else if( h > values::layers::kilometers::EXOSPEHRE )
    {
        layer = messages::layers::kilometers::OUTERSPACE;
    }
    else
    {
        exit( EXIT_FAILURE ); //Should never get here, but just in case have a back up
    }
    return layer;
}

bool cin_test()
{
    using namespace std;
    bool input_test;
    if( cin.fail() || ( cin.peek() != '\n' ) )
    {
        cin.clear();
        cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        input_test = true;
    }
    else
    {
        input_test = false;
    }
    return input_test;
}
