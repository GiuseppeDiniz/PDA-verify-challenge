#ifndef PDA_H
#define PDA_H

#include <vector>
#include <string>

class Rule {
public:
    char input;
    char pop;
    std::string push;
    
    Rule(char input, char pop, const std::string& push) : input(input), pop(pop), push(push) {}
};

class State {
public:
    int id;
    bool isTerminal;

    State(int id, bool isTerminal) : id(id), isTerminal(isTerminal) {}
};

class Transition {
public:
    State* from;
    State* to;
    Rule transition_rule;

    Transition(State* from, State* to, Rule transition_rule) : from(from), to(to), transition_rule(transition_rule) {}
};

class Automaton {
private:
    std::vector<State*> states;
    std::vector<Transition> transitions;
    State* initialState;

public:
    Automaton();
    ~Automaton();
    State* createState(bool isTerminal);
    void addTransition(State* from, State* to, Rule transition_rule);
    void printTransitions();
    bool isAccepted(std::string input);
};

#endif // PDA_H
