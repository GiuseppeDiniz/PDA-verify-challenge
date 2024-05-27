#include "PDA.h"
#include <iostream>
#include <string>

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

void Automaton::addTransition(State* from, State* to, Rule transition_rule) {
    transitions.push_back(Transition(from, to, transition_rule));
}

void Automaton::printTransitions() {
    for (const auto& transition : transitions) {
        std::cout << "From State " << transition.from->id << " to State " << transition.to->id << " with rule: " << transition.transition_rule.input << ", " << transition.transition_rule.pop << ", " << transition.transition_rule.push << std::endl;
    }
}