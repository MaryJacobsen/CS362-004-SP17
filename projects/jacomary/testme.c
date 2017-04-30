#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//Get random number 0-8 to pick from the 9 chars
char inputChar()
{
    	// TODO: rewrite this function
	int randomInputChar = rand() % 9; //nine different chars (0-8)
	switch (randomInputChar) {
    		case 0: return '[';
		case 1: return '(';
		case 2: return '{';
		case 3: return ' ';
		case 4: return 'a';
		case 5: return 'x';
		case 6: return '}';
		case 7: return ')';
		case 8: return ']';
	}
}

//make a null-terminated, 6 char string by looping through and using a random number generator to select each char
char *inputString()
{
    	// TODO: rewrite this function
	int randomInputString, i;
	char *s;
	s = (char *) malloc(6);
	for(i=0; i<6; i++) {
		randomInputString = rand() % 6;
		switch (randomInputString)
		{
			case 0: s[i] = 'r';
				break;
			case 1: s[i] = 'e';
				break;
			case 2: s[i] = 's';
				break;
			case 3: s[i] = 'e';
				break;
			case 4: s[i] = 't';
				break;
			case 5: s[i] = '\0';
				break;
		}
	}
	return s;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error\n");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
