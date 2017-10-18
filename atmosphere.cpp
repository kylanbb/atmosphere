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
    
    if( GetUnit( unit ) ) //Retrieve preferred unit of measure.
    {
        cout << "Thank you for selecting the unit." << endl; //If successful, thank the user and continue.
    }
    else 
    {
        exit( EXIT_FAILURE ); //If unsuccessful, exit the program.
    }
    
    if( GetHeight( height ) ) //Retreive Altitude.
    {
        cout << "Thank you for choosing a valid height. Now calculating the atmospheric layer." 
             << endl; //If successful, thank the user and continue.
    }
    else
    {
        exit( EXIT_FAILURE ); //If unsuccessful, exit the program.
    }

    //Inform the user the atmospheric layer based on the unit type and height they selected.
    cout << height << GetLayer( unit, height ) << endl; 
    
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

        //Test to see if the number corresponds to either unit of measurement.
        else if( unit != values::unit::MILES && unit != values::unit::KILOMETERS ) 
        {
            isValid = false; //If user put in an invalid number, set isValid to false.
        }

        //Double check that user did indeed put in a valid number.
        else if( unit == values::unit::MILES || unit == values::unit::KILOMETERS ) 
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
                //If the user is out of attempts, alert the user.
                std::cout << messages::OUT_OF_TRIES << std::endl; \
                std::exit( EXIT_SUCCESS ); //Additionally, exit the program.
            }
            else
            {
                //If the user is not out of attempts, alert the user it was invalid and run the loop again.
                std::cout << messages::unit::INVALID << std::endl; 
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
                std::exit( EXIT_SUCCESS ); //User ran out of tries, terminate program.
            }
            else
            {
                //If user has more tries, inform them they put in an invalid height, and begin loop again.
                std::cout << height::INVALID << std::endl; 
            }
        }

    }

    //It should be impossible to get here, but as a failsafe, terminate the program.
    std::exit( EXIT_FAILURE ); 
}

//Define function to find layer using chosen system.
std::string GetLayer( int u, float h )
{
    using namespace values::unit;
    using namespace std;
    assert( u == MILES || u == KILOMETERS ); //Asserts that the function call provided a valid unit option.
    string layer; //Declare variable to hold the layer message.
    switch( u ) //Test for which unit the user selectes.
    {
        case MILES:      layer = GetLayerM(h); //If user selected to use miles, run the miles lookup function.
                         break; //Guard from running both functions, and exiting the program prematurely.
        case KILOMETERS: layer = GetLayerK(h); //If user selected to use kilometers, run the kilometers lookup function.
                         break; //Guard from exiting the program prematurely.
        default:         exit(EXIT_FAILURE); //Should never be able to get here, but if some how the user does, exit the program.
    }
    return layer; //Return the layer of the atmosphere the height is in.
}

//Define function to find altitude mile layer.
std::string GetLayerM( float h )
{
    std::string layer; //Declare a variable to store the result as.
    if( h == values::layers::SURFACE ) //Checks if the height is at the surface level.
    {
        layer = messages::layers::miles::SURFACE; //If so, it prints the appropriate message.
    }
    else if( h <= values::layers::miles::TROPOSPHERE ) //Checks if the height is at the troposphere level.  
    {
        layer = messages::layers::miles::TROPOSPHERE; //If so, it prints the appropriate message.  
    }
    else if( h <= values::layers::miles::STRATOSPHERE ) //Checks if the height is at the stratosphere level.  
    {
        layer = messages::layers::miles::STRATOSPHERE; //If so, it prints the appropriate message.  
    }
    else if( h <= values::layers::miles::MESOSPHERE ) //Checks if the height is at the mesosphere level.  
    {
        layer = messages::layers::miles::MESOSPHERE; //If so, it prints the appropriate message.  
    }
    else if( h <= values::layers::miles::THERMOSPHERE ) //Checks if the height is at the thermosphere level.  
    {
        layer = messages::layers::miles::THERMOSPHERE; //If so, it prints the appropriate message.  
    }
    else if( h <= values::layers::miles::EXOSPEHRE ) //Checks if the height is at the exosphere level.  
    {
        layer = messages::layers::miles::EXOSPHERE; //If so, it prints the appropriate message.  
    }
    else if( h > values::layers::miles::EXOSPEHRE ) //Checks if the height is above the exosphere level.  
    {
        layer = messages::layers::miles::OUTERSPACE; //If so, it prints the appropriate message.  
    } 
    else
    {
        exit( EXIT_FAILURE ); //Should never get here, but just in case have a back up.
    }
    return layer; //Return the appropriate message back to GetLayer(int,float).
}

//Define function to find altitude kilometer layer
std::string GetLayerK( float h )
{
    std::string layer;
    if( h == values::layers::SURFACE ) //Checks if the height is at the surface level.  
    {
        layer = messages::layers::kilometers::SURFACE; //If so, it prints the appropriate message.  
    }
    else if( h <= values::layers::kilometers::TROPOSPHERE ) //Checks if the height is at the troposhere level.  
    {
        layer = messages::layers::kilometers::TROPOSPHERE; //If so, it prints the appropriate message.  
    }
    else if( h <= values::layers::kilometers::STRATOSPHERE ) //Checks if the height is at the stratosphere level.  
    {
        layer = messages::layers::kilometers::STRATOSPHERE; //If so, it prints the appropriate message.  
    }
    else if( h <= values::layers::kilometers::MESOSPHERE ) //Checks if the height is at the mesosphere level.  
    {
        layer = messages::layers::kilometers::MESOSPHERE; //If so, it prints the appropriate message.  
    }
    else if( h <= values::layers::kilometers::THERMOSPHERE ) //Checks if the height is at the thermosphere level.  
    {
        layer = messages::layers::kilometers::THERMOSPHERE; //If so, it prints the appropriate message.  
    }
    else if( h <= values::layers::kilometers::EXOSPEHRE ) //Checks if the height is at the exosphere level.  
    {
        layer = messages::layers::kilometers::EXOSPHERE; //If so, it prints the appropriate message.  
    }
    else if( h > values::layers::kilometers::EXOSPEHRE ) //Checks if the height is above the exosphere level.  
    {
        layer = messages::layers::kilometers::OUTERSPACE;//If so, it prints the appropriate message.  
    }
    else
    {
        exit( EXIT_FAILURE ); //Should never get here, but just in case have a back up.
    }
    return layer; //Return the appropriate message back to GetLayer(int,float).
}

//Define a function to simultaneously test user input, and clear the buffer if it fails.
bool cin_test()
{
    using namespace std;
    bool input_test; //Declare a variable to store the pass/fail status of the test.

    //Check if the user didn't put in a number, or put a non number character between numbers and pressing enter.
    if( cin.fail() || ( cin.peek() != '\n' ) ) 
    {
        cin.clear(); //Clear the input failure flag.
        cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' ); //Clear the buffer of the bad data.
        input_test = true; //Set input_test to true in order to reflect that there was an error.
    }
    else
    {
        input_test = false; //If there was no error, set input_test to false.
    }
    return input_test; //Return the result in order to use this for conditional checks.
}
