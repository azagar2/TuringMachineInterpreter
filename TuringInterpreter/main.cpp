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
    //std::getline(std::cin, line);
    //ifstream myfile ("input.txt");
    //if (myfile.is_open())
    //{
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
                    //                for (vecList::iterator it = newString.begin(); it != newString.end(); it++)
                    //                    std::cout << *it;
                    //                cout << endl;
                }
                
            }
        }
        //myfile.close();

        // TESTING TO SEE ALL STATES
//        for(map<char, inputTransition>::iterator it = m.begin(); it != m.end(); ++it) {
//            cout << "state: " << it->first << "\n";
//            inputTransition temp = it->second;
//            for(inputTransition::iterator it = temp.begin(); it != temp.end(); ++it) {
//                cout << "symbol: " << it->first << "\n";
//            }
//        }
        
    //}
    //else cout << "Unable to open file";
    
    
    /* TURING MACHINE */
    
    cout << inputs.size() << endl;
    
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
            //cout << "The current symbol is: " << *(it) << endl;
            
            // Check if input symbol is valid
            if (! m[currentState].count(*(it)))
            {
                for (vecList::iterator it = tape.begin() + 1; it != tape.end() - 1; it++) {
                    output += *(it);
                }
                cout << output << endl;
                cout << "REJECTED" << endl;
                break;
                // need to add on the rest of the input symbols to the output...
            }
            
            // Check if direction is H
            if (m[currentState][*(it)].direction == 'H')
            {
                nextState = m[currentState][*(it)].next;
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
            //cout << "next state is: " << nextState << endl;
            char symbol = *(it);
            
            // Modify the tape
            *(it) = m[currentState][symbol].output;
            
            // Set next direction
            if (m[currentState][symbol].direction == 'L')
            {
                //cout << "go left" << endl;
                it--;
            }
            else if (m[currentState][symbol].direction == 'R')
            {
                //cout << "go right" << endl;
                it++;
            }
            
        }
        
    }

    return 0;
}




