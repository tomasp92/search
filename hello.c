#include <cs50.h>
#include <stdio.h>


int main(void)
{
    // ask the user its name and store the answer (answer) on te left
    string answer = get_string("whats your name?\n");
    // say hello and the users name (answer)
    printf("hello,  %s\n", answer);
}
