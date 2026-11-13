# Overall Design

This product's purpose is to take in the readings of a classroom and determine if they are in an acceptable temperature range or not.

This product allows for a warning light to be connected, so that you can easily and visually determine whether or not a temperature is outside of the expected range.

## Connection Between Hardware and Software

By connecting a wire from GPIO pin 17 to a breadboard, and another wire from one of the GPIO ground pins to the same breadboard, you can connect a warning led which will light up whenever an unacceptable temperature is entered by the user. 

The warning light will not turn off until an acceptable value is entered. 

## User Experience

The program's user experience is structured as a terminal menu, so it is easy to use and navigate.

As stated in the requirements, all user input must be numeric.

All incorrect numeric input within menu options is handled properly.

The program itself does not stop the user from entering large numbers, but does handle the user entering negative numbers as readings.

## Macros

There are 3 preprocessor macros present, which allow for maintainers to change the exact design choices.

* PIN - This is the GPIO pin that is used to light the warning light.
* MAX - This is the maximum number of readings a user is able to enter.
* PATH - This is the path to the status.txt file, where users can save their readings along with their normal/warning statuses.

## Functions

There are multiple functions that separate the many tasks that this program needs to accomplish.

* int addReading(double*, int);
  * This function prompts the user to enter a reading. The parameters include the array in which the reading is stored, and the index in the array where the data should be stored.
* int checkTemp(double);
  * This function takes a reading and compares it against the global variables for the bounds of the acceptable temperature range. The only parameter is a double, which is the reading being checked.
* double calculateAverage(double*, int);
  * This function calculates the average of all of the readings entered by the user. The parameters include the array which the readings are held, and the number of readings entered into the array at that current point.
* int saveToFile(FILE*, double*, int );
  * This function saves all of the currently entered readings into a file determined by the PATH macro. The function takes in a FILE* used within the rest of the program, as well as the array of readings and the count of readings entered into the array at that point.
* void changeRange(int* int*);
  * This function allows for the user to change the acceptable temperature range. The function takes in 2 int*s, which are the addresses of the boundary numbers for the acceptable temperature range.

