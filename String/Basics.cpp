#include <bits/stdc++.h>
using namespace std;
/*
These f unctions return an int, not a bool.
The C standard only says they return:
    zero if the character does not match
    non-zero (any non-zero value) if it does match
They do not promise to return 1.
*/

int main(){
    cout << isalpha('X') << endl;
    cout << isalpha('u') << endl;

    cout << isdigit('0') << endl;
    cout << isdigit('9') << endl;

    cout << isalnum('Q') << endl;
    cout << isalnum('8') << endl;

    cout << islower('p') << endl;
    cout << isupper('D') << endl;

    char low = tolower('G');
    char upp = toupper('e');
    cout << low << " " << upp << endl;
    return 0;
}

/*
    🛠️ Character Classification Functions
    These functions check if a character belongs to a specific category. They return a non-zero
    value (true) if the character matches the criteria, and 0 (false) if it does not.
         Function	                Description
        isdigit(ch)	    Returns true if ch is a numerical digit (0-9).
        isalnum(ch)	    Returns true if ch is alphanumeric (either a letter or a digit).
        isalpha(ch)	    Returns true if ch is an alphabetic letter (a-z, A-Z).
        islower(ch)	    Returns true if ch is a lowercase letter.
        isupper(ch)	    Returns true if ch is an uppercase letter.
        isspace(ch)	    Returns true if ch is any whitespace character (space, tab, \n, \r, etc.).
        isblank(ch)	    Returns true if ch is a blank space or a horizontal tab.
        ispunct(ch)	    Returns true if ch is a punctuation mark (excluding whitespace and alphanumeric).
        iscntrl(ch)	    Returns true if ch is a control character (like \n or ASCII control codes).
        isprint(ch)	    Returns true if ch is any printable character, including spaces.
        isxdigit(ch)    Returns true if ch is a hexadecimal digit (0-9, a-f, A-F).

*/