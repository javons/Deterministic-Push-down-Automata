#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void compute(int step, string state, string input,
	     string stack, int delta, string R);
void print(int step, string state, string input,
	   string stack, int delta, string R);

int main(void)
{
    string input;
    cout << "This is a program that can recognize the context"
	"-free grammar: \nL = { a^n*b^n | n>=0 }.\n"
	"Please enter input content (put $ at the end): ";
    cin >> input;
    int step = 0; string state = "p"; string stack = "";
    int delta = 0; string R = "";
    cout << "\n\u2731Computation Chart                 "
	"            *Note: \u0394 used 0 represents --\n\n";
    cout << " Step    State            Unread Input         Stack"
	"       \u0394 used      R used\n";
    cout << "---------------------------------------------------"
	"----------------------------\n";
    compute(step, state, input, stack, delta, R);
    
}

void compute(int step, string state, string input,
	     string stack, int delta, string R)
{
    print(step, state, input, stack, delta, R);
    
    while (state != "q$") {
	
	if (state == "p") {
	    state = "q"; stack = "S";
	    step++; delta = 1;
	    print(step, state, input, stack, delta, R);
	}

	else if (state == "q" && input[0] == 'a') {
	    state = "qa"; input.erase(0,1);
	    step++; delta = 2;
	    print(step, state, input, stack, delta, R);
	}

	else if (state == "qa" && stack[0] == 'a') {
	    state = "q"; stack.erase(0,1);
	    step++; delta = 3;
	    print(step, state, input, stack, delta, R);
	}

	else if (state == "q" && input[0] == 'b') {
	    state = "qb"; input.erase(0,1);
	    step++; delta = 4;
	    print(step, state, input, stack, delta, R);
	}

	else if (state == "qb" && stack[0] == 'b') {
	    state = "q"; stack.erase(0,1);
	    step++; delta = 5;
	    print(step, state, input, stack, delta, R);
	}

	else if (state == "q" && input[0] == '$') {
	    state = "q$"; input.erase(0,1);
	    step++; delta = 6;
	    print(step, state, input, stack, delta, R);
	}

	else if (state == "qa" && stack[0] == 'S') {
	    state = "qa";
	    stack.erase(0,1); stack.insert(0, "aSb");
	    step++; delta = 7; R = "S->aSb";
	    print(step, state, input, stack, delta, R);
	    R.erase();
	}

	else if (state == "qb" && stack[0] == 'S') {
	    state = "qb"; stack.erase(0,1);
	    step++; delta = 8; R = "S->e";
	    print(step, state, input, stack, delta, R);
	    R.erase();
	}
	else {
	    cout << "\nError: input you entered is not valid!\n";
	    break;
	}
    }
    if (!stack.empty() || !input.empty())
	cout << "\nError: please try again!\n";
    else {
	cout << "\n" << setw(45) << "Done.\n";
    }
}


void print(int step, string state, string input,
	   string stack, int delta, string R)
{
    if (input == "") input = "e";
    if (stack == "") stack = "e";
    cout << "|" << setw(4) << step << "|"<< setw(9) << state << "|"
	 << setw(26) << input << "|" << setw(14) << stack << "|"
	 << setw(10) << delta << "|" << setw(9) << R << "|\n";
    cout << "--------------------------------------------------"
	"-----------------------------\n";
}
