#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct State
{
  int state_id;
  bool is_final;
  map<char, vector<State*> > transitions;

  State(int id, bool final)
  {
    state_id = id;
    is_final = final;
  }
};

class NFA
{
private:
  vector<State*> states;

public:
  NFA(string grammar)
  {
    int state_id = 0;

    // Add start state
    State *start = new State(state_id++, false);
    states.push_back(start);

    // Iterate through grammar and add states and transitions
    for (int i = 0; i < grammar.length(); i++)
    {
      char symbol = grammar[i];

      // Add new state for current symbol
      State *new_state = new State(state_id++, (i == grammar.length() - 1));
      states.push_back(new_state);

      // Add transition from current state to new state for current symbol
      start->transitions[symbol].push_back(new_state);

      // Set new state as current state
      start = new_state;
    }
  }

  vector<State*> getStates()
  {
    return states;
  }
};

int main()
{
  string grammar;
  cout << "Enter a regular grammar: ";
  cin >> grammar;

  NFA nfa(grammar);
  vector<State*> states = nfa.getStates();

  cout << "NFA structure: " << endl;
  for (int i = 0; i < states.size(); i++)
  {
    State *state = states[i];
    cout << "State " << state->state_id << ": ";

    if (state->is_final)
    {
      cout << "(final) ";
    }

    cout << "Transitions: ";
    map<char, vector<State*> >::iterator it;
    for (it = state->transitions.begin(); it != state->transitions.end(); it++)
    {
      char symbol = it->first;
      vector<State*> transition_states = it->second;

      cout << symbol << " -> {";
      for (int j = 0; j < transition_states.size(); j++)
      {
        State *transition_state = transition_states[j];
        cout << transition_state->state_id;

        if (j < transition_states.size() - 1)
        {
          cout << ", ";
        }
      }
      cout << "} ";
    }

    cout << endl;
  }

  return 0;
}



