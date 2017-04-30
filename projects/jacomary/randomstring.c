/*~Development of my Random Tester~

* I looked through testme.c to see what the error message was and what would
* make it print. I noticed that it printed if the random string (s) equaled 
* "reset\0" and the state equaled 9. 
*
* I knew inputChar() is supposed to return a random character from the set
* charactors already in testme() and that inputString() is supposed to
* return a random string made up of the charactors
* 'r', 'e', 's', 'e', 't','\0'. I also noticed that the while loop would
* keep going until the error message was triggered since it was set
* to while true so I knew that it would keep getting random values from
* inputChar() and inputString() unil inputString returned "reset\0" and the
* state = 9. 
*
* For inputChar(), I used a random number generator to select a
* charactor from the set of charactors being tested. Then returned that 
* charactor. 
*
* For inputString(), I first looped through 5 times and used 
* rand() to generate a random charactor from the set of charactors in
* "reset". After the loop exited I set the last charactor in the string to
* the null terminator. That way every string returned would be a null
* terminated string. For this way of doing it, the while loop inside 
* testme() only had to iterate six hundred and something times. When I 
* decided to change it to putting the null terminator inside the for loop
* so that was one of the charactors being chosen from to randomly generate
* the string. This way it took over 66,000 iterations to generate "reset\0"
* to print the error message and exit the program. The coverage for 
* testme.c when the null terminating charactor was in the for loop
* was over 96% and branch coverage was 100%.
