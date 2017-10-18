//Begin include guard ends on line 103
#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H
#include <string>
//Declare all constants

//Declare all message constants
namespace messages 
{
    //Declare message for when the user runs out of attempts for the user input functions.
    const std::string OUT_OF_TRIES = "You ran out of attempts."; 

    //Declare all messages for the unit request
    namespace unit
    {
        const std::string REQUEST = "Which unit of measurement would you like to use? [0 = miles, 1 = kilometers]";
        const std::string INVALID = "That was an invalid option. Please try again.";
    }

    //Declare all messages for the height request
    namespace height
    {
        const std::string REQUEST = "What is the height in question? [Use only positive whole numbers]";
        const std::string INVALID = "That was an invalid entry. Please try again using only numbers.";
    }

    //Declare all messages to inform the user which specific layer the height they provided is in
    namespace layers
    {
        //Declare the layer messages for heights in miles.
        namespace miles
        {
            const std::string SURFACE = " miles is on the surface, which is at the bottom of the Troposphere.";
            const std::string OUTERSPACE = " miles is in outerspace. This is not in the atmosphere, as it is past the Exosphere which is the highest level.";
            const std::string TROPOSPHERE = " miles is in the Troposphere. This is the lowest level of the atmosphere.";
            const std::string STRATOSPHERE = " miles is in the Stratosphere. This is the second lowest level of the atmosphere.";
            const std::string MESOSPHERE = " miles is in the Mesosphere. This is the middle level of the atmosphere.";
            const std::string THERMOSPHERE = " miles is in the Thermosphere. This is the second highest level of the atmosphere.";
            const std::string EXOSPHERE = " miles is in the Exosphere. This is the highest level of the atmosphere.";
        }

        //Declare the layer messages for heights in kilometers.
        namespace kilometers
        {
            const std::string SURFACE = " kilometers is on the surface, which is at the bottom of the Troposphere.";
            const std::string OUTERSPACE = " kilometers is in outerspace. This is not in the atmosphere, as it is past the Exosphere which is the highest level.";
            const std::string TROPOSPHERE = " kilometers is in the Troposphere. This is the lowest level of the atmosphere.";
            const std::string STRATOSPHERE = " kilometers is in the Stratosphere. This is the second lowest level of the atmosphere.";
            const std::string MESOSPHERE = " kilometers is in the Mesosphere. This is the middle level of the atmosphere.";
            const std::string THERMOSPHERE = " kilometers is in the Thermosphere. This is the second highest level of the atmosphere.";
            const std::string EXOSPHERE = " kilometers is in the Exosphere. This is the highest level of the atmosphere.";
        }
    }
}

//Declare all other non-message constants
namespace values
{
    //Unit selection constants
    namespace unit
    {
        const int MILES = 0;
        const int KILOMETERS = 1;
    }

    //Atmospheric height constants
    namespace layers
    {
        //Regardless of unit, zero is on the surface
        const int SURFACE = 0;

        //Mile heights
        namespace miles
        {
            const int TROPOSPHERE = 7;
            const int STRATOSPHERE = 31;
            const int MESOSPHERE = 50;
            const int THERMOSPHERE = 440;
            const int EXOSPEHRE = 6200;
        }

        //Kilometer heights
        namespace kilometers
        {
            const int TROPOSPHERE = 12;
            const int STRATOSPHERE = 50;
            const int MESOSPHERE = 80;
            const int THERMOSPHERE = 700;
            const int EXOSPEHRE = 10000;
        }
    }
}

//Declare function names
bool GetUnit(int& unit);
bool GetHeight(float& height);
std::string GetLayer(int u, float h);
std::string GetLayerK(float h);
std::string GetLayerM(float h);
bool cin_test();
void onExit();

#endif //End the include guard started on line 2
