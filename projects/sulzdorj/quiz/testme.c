#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // Get a value from 0 to 94
    int asciiVal = rand() % 95;
    // Offset that value so we're actually getting a number from 32 to 126
    // Which would include all alphanumeric characters as well as the special ones below
    asciiVal += 32;
    // Can just return this as an integer - C will interpret this as a character value
    return asciiVal;
}

char *inputString()
{
    // Generate a random number between 0 and 1
    int pickone = rand() % 2;
    // If 0, then let's return a string that would fail the checks on line 50-52
    if( pickone == 0 ){
      return "not right";
    }
    // Otherwise, return the string that lines 50-52 are expecting
    return "reset";
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
      printf("error ");
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
