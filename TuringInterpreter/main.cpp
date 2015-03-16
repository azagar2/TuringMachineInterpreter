//
//  turing.cpp
//  TuringInterpreter
//
//  Created by Andrea Zagar on 2015-03-14.
//  Copyright (c) 2015 Andrea Zagar. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>

using namespace std;


/* Make a struct to model transition (next state, output symbol, head direction) */
struct Transition {
    char next;
    char output;
    char direction;
    
    Transition() {};
    Transition(char s, char o, char d) {
        next = s;
        output = o;
        direction = d;
    }
};


int main() {

    // Make a vector of final states and a vector of inputs
    typedef vector<char> vecList;
    vecList finalStates;
    vector<vecList> inputs;
    
    // Make a map with the key = state, value = map of (key = input symbol, value = transition struct)
    typedef map<char, Transition> inputTransition;
    map<char, inputTransition> m;

    // Read from cin
    string line;

    // Read each line from cin
    while (getline (cin ,line))
    {
        if (!line.empty())
        {
            // Take the blank characters out of the string
            string s = "";
            for ( int i = 0 ; i < line.length(); i++) {
                if (!isspace(line[i]))
                    s += line[i];
            }
            
            // For transitions:
            if (s[0] == 't') {
                m[s[1]][s[2]] = Transition(s[3], s[4], s[5]);
            }
            
            // For final states:
            else if (s[0] == 'f') {
                for (int i = 1; i < s.length(); i++) {
                    finalStates.push_back(s[i]);
                }
            }
            
            // For input string:
            else {
                vector<char> newString;
                newString.push_back('Z'); // begin with Z
                for (int i = 1; i < s.length(); i++)
                {
                    newString.push_back(s[i]);
                }
                newString.push_back('Z'); // end with Z
                inputs.push_back(newString); // add input to vector
            }
        }
    }

    
    /* TURING MACHINE */
    
    // Iterates through each input string
    for (int i = 0; i < inputs.size(); i++)
    {
        // The current tape
        vecList tape = inputs[i];
        
        // Make iterator for tape, but skip the first element which is Z
        vecList::iterator it = tape.begin();
        it++;
        
        
        // Variables for while loop
        string output = "";
        char currentState, nextState = '0';
        
        while (true)
        {
            currentState = nextState;
            
            // Check if input symbol is in the map
            if (! m[currentState].count(*(it)))
            {
                // If it is not valid, append the rest of the tape onto the output string
                for (vecList::iterator it = tape.begin() + 1; it != tape.end() - 1; it++) {
                    output += *(it);
                }
                // Outputs
                cout << output << endl;
                cout << "REJECTED" << endl;
                break;
            }
            
            // Check if direction is HALT
            if (m[currentState][*(it)].direction == 'H')
            {
                // Set next state
                nextState = m[currentState][*(it)].next;
                // Modify the tape
                *(it) = m[currentState][*(it)].output;
                // Add everything to the output string
                for (vecList::iterator it = tape.begin() + 1; it != tape.end() - 1; it++) {
                    output += *(it);
                }
                // Output
                cout << output << endl;
                // Make sure it is a final state
                if(find(finalStates.begin(), finalStates.end(), nextState) == finalStates.end())
                    cout << "Not a final state" << endl;
                else
                    cout << "ACCEPTED" << endl;
                break;
            }
            
            // Set the next state
            nextState = m[currentState][*(it)].next;
            char symbol = *(it);
            
            // Modify the tape
            *(it) = m[currentState][symbol].output;
            
            // Set next direction and increment or decrement the iterator (head)
            if (m[currentState][symbol].direction == 'L')
            {
                it--;
            }
            else if (m[currentState][symbol].direction == 'R')
            {
                it++;
            }
        }
        
    }

    return 0;
}




