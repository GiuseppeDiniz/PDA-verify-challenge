#include "PDA.h"
#include <iostream>

Automaton::Automaton() {}

Automaton::~Automaton() {
    for (State* state : states)
        delete state;
}

State* Automaton::createState(bool isTerminal) {
    State* newState = new State(states.size(), isTerminal);
    states.push_back(newState);
    return newState;
}

void Automaton::addTransition(State* from, State* to, Rule rule_transition) {
    transitions.push_back(Transition(from, to, rule_transition));
}

void Automaton::printTransitions() {
    for (const auto& transition : transitions) {
        std::cout << "From State " << transition.from->id << " to State " << transition.to->id << " with rule: " << transition.rule_transition.input << ", " << transition.rule_transition.pop << ", " << transition.rule_transition.push << std::endl;
    }
}

bool Automaton::isAccepted(std::string input) {
    // Em construcao
    State* currentState = states.front();
    for (char symbol : input) {
        
    }
    return currentState->isTerminal;
}
