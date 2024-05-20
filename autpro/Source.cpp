#include <iostream>
#include <vector>
#include <algorithm>
#include<string>

using namespace std;


void printLi() { cout << "-----------------------------------\n\a"; }
void printLine() { cout << "_____________________________________________________________________\n\n\a"; }


//////////////////////////////////////////////////////////
//In this function, we take the number of states and the states, and store them in a vector called 'states'."

vector<string> initializeStates() 
{
    int x;
    cout << "Enter the number of states: ";
    cin >> x;
    printLi();

    vector<string> states(x);
    cout << "Enter the states (initial state first): ";
    for (int i = 0; i < x; ++i) 
    {
        cin >> states[i];
    }
    printLine();

    return states;
}


//////////////////////////////////////////////////////////

//In this function, we take the number of alphabets and the alphabets, and store them in a vector called 'alpha'.

vector<string> initializeAlphabet() 
{
    int y;
    cout << "Enter the number of alphabets: ";
    cin >> y;
    printLi();

    vector<string> alpha(y);
    cout << "Enter the alphabets: ";
    for (int i = 0; i < y; ++i) 
    {
        cin >> alpha[i];
    }
    printLine();

    return alpha;
}


//////////////////////////////////////////////////////////

//In this function, we take the number of final states and the final states, and store them in a vector called 'finalstates'.

vector<string> initializeFinalStates()
{
    int n;
    cout << "Enter the number of final states: ";
    cin >> n;
    printLi();

    vector<string> finalStates(n);
    cout << "Enter the final states: ";
    for (int i = 0; i < n; ++i) 
    {
        cin >> finalStates[i];
    }
    printLine();

    return finalStates;
}


//////////////////////////////////////////////////////////

//In this function, we take the transitions of each state and store them in a 2D vector called 'transition'.

vector<vector<string>> initializeTransitionMatrix(const vector<string>& states, const vector<string>& alphabet) 
{
    int x = states.size();
    int y = alphabet.size();

    vector<vector<string>> transition(x, vector<string>(y));

    for (int i = 0; i < x; ++i) 
    {
        for (int j = 0; j < y; ++j) 
        {
            cout << "from " << states[i] << "  \"if input " << alphabet[j] << "\"  it will go to -->: ";
            cin >> transition[i][j];
        }
        cout << endl;
    }
    printLine();
    return transition;
}


//////////////////////////////////////////////////////////

//In this function, we check whether the input string is part of our alphabet ('sigma') ,that we enter earlier, or not.

bool isStringInAlphabet(const string& input, const vector<string>& alphabet) 
{
    for (char i : input) 
    {
        if (find(alphabet.begin(), alphabet.end(), string(1, i)) == alphabet.end()) 
        {
            return false;  // Character not found in our alphabet ('sigma') that we enter earlier
        }
    }
    return true;    // All characters are found in our alphabet ('sigma') that we enter earlier
}


//////////////////////////////////////////////////////////

//In this function, we take an input string and use a transition matrix (which is taken in the main) to determine the sequence of states that the machine will go through based on the characters of the input string.

void processInputString(const string& input, const vector<string>& alphabet,
    const vector<string>& states, const vector<vector<string>>& transitionMatrix,
    vector<string>& resultStates) 
{
    string start = states[0];

    for (char i : input) {
        auto it = find(alphabet.begin(), alphabet.end(), string(1, i));
        int index = distance(alphabet.begin(), it);

        auto stateIt = find(states.begin(), states.end(), start);
        int stateIndex = distance(states.begin(), stateIt);

        start = transitionMatrix[stateIndex][index];
        resultStates.push_back(start);
    }
}


/* "In the main function, we store the return values of certain functions in new vectors to use them in the 'processInputString' function. 
We then check if the string is for exist or not. 
If it doesn't, we verify whether it belongs to our defined alphabet. 
Finally, we determine whether the string is accepted or rejected." */

int main() 
{
    vector<string> states = initializeStates();
    vector<string> alphabet = initializeAlphabet();
    vector<string> finalStates = initializeFinalStates();
    vector<vector<string>> transitionMatrix = initializeTransitionMatrix(states, alphabet);

    while (true) 
    {
        string input;
        cout << "Please Enter the string to check (type 'quit' to exit): ";
        cin >> input;

        if (input == "quit") 
        {
            break; // exit the loop if the user enters "quit"
        }
        else if (!isStringInAlphabet(input, alphabet)) 
        {
            cout << "Invalid input string \"It contains characters not in the alphabet\"." << endl;
            printLine();
            continue;  // ask to input another string again
        }
        else 
        {
            vector<string> resultStates;
            processInputString(input, alphabet, states, transitionMatrix, resultStates);

            if (find(finalStates.begin(), finalStates.end(), resultStates.back()) != finalStates.end()) 
            {
                cout << "The string  \"" << input << "\"  is ACCEPTED" << endl;
            }
            else 
            {
                cout << "The string  \"" << input << "\"  is REJECTED" << endl;
            }
            printLine();
        }
    }
    printLine();
    return 0;
}
