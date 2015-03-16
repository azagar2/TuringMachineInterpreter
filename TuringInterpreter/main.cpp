//
//  main.cpp
//  TuringInterpreter
//
//  Created by Andrea Zagar on 2015-03-14.
//  Copyright (c) 2015 Andrea Zagar. All rights reserved.
//

#include <iostream>
#include <map>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

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

    
    typedef vector<char> vecList;
    vecList finalStates;
    vector<vecList> inputs;
    
    // Map types
    typedef map<char, Transition> inputTransition;
    map<char, inputTransition> m;

    // Read from file
    string line;

        while (getline (cin ,line))
        {
            if (!line.empty())
            {
                string s = "";
                for ( int i = 0 ; i < line.length(); i++)
                {
                    if (!isspace(line[i]))
                        s += line[i];
                }
                
                if (s[0] == 't') { // transition
                    
                    inputTransition tempMap;
                    m[s[1]][s[2]] = Transition(s[3], s[4], s[5]);
                }
                
                else if (s[0] == 'f') { // final states
                    for (int i = 1; i < s.length(); i++)
                    {
                        finalStates.push_back(s[i]);
                    }
                }
                
                else { // input string
                    vector<char> newString;
                    newString.push_back('Z'); // begin with Z
                    for (int i = 1; i < s.length(); i++)
                    {
                        newString.push_back(s[i]);
                    }
                    newString.push_back('Z'); // end with Z
                    inputs.push_back(newString);
                }
                
            }
        }

    
    /* TURING MACHINE */
    
    for (int i = 0; i < inputs.size(); i++)
    {
        vecList tape = inputs[i];
        
        vecList::iterator it = tape.begin();
        it++; // skips the first element which is Z
        
        string output = "";
        char currentState, nextState = '0';
        
        while (true)
        {
            currentState = nextState;
            
            // Check if input symbol is valid
            if (! m[currentState].count(*(it)))
            {
                for (vecList::iterator it = tape.begin() + 1; it != tape.end() - 1; it++) {
                    output += *(it);
                }
                cout << output << endl;
                cout << "REJECTED" << endl;
                break;
            }
            
            // Check if direction is H
            if (m[currentState][*(it)].direction == 'H')
            {
                nextState = m[currentState][*(it)].next;
                // Modify the tape
                *(it) = m[currentState][*(it)].output;
                // Add everything to the output string
                for (vecList::iterator it = tape.begin() + 1; it != tape.end() - 1; it++) {
                    output += *(it);
                }
                cout << output << endl;
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
            
            // Set next direction
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




