#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#define epsilon '&'

using namespace std;

class Rule {
public:
    char input;
    char pop;
    string push;

    Rule(char input, char pop, string push) : input(input), pop(pop), push(push) {}
};

class Transition {
public:
    int to;
    Rule transition_rules;

    Transition(int to, Rule transition_rules) : to(to), transition_rules(transition_rules) {}
};

class State {
public:
    int id;
    bool isTerminal;
    vector<Transition*> state_transitions;

    State() {}
    ~State(){
        for (Transition* transition : state_transitions){
            delete transition;
        }
    }
};

class Automaton {
private:
    vector<State*> automaton_states;
    std::stack<char> stack;
public:
    Automaton(){}
    ~Automaton() {
        for (State* state : automaton_states) {
            delete state;
        }
    }
    State* createState(){
        State* newState = new State();
        newState->id = automaton_states.size();
        newState->isTerminal = false;
        automaton_states.push_back(newState);
        return newState;
    }
    void pushStack(char value) {
        stack.push(value);
    }
    void popStack() {
        if (!stack.empty()) {
            stack.pop();
        } else {
            std::cerr << "Erro: Tentativa de desempilhar de uma pilha vazia!" << std::endl;
        }
    }
    char peekStack() {
        if (!stack.empty()) {
            return stack.top();
        } else {
            std::cerr << "Erro: Tentativa de espiar em uma pilha vazia!" << std::endl;
            return '\0';
        }
    }
    bool isEmptyStack() {
        return stack.empty();
    }
    void clearStackAndPushZ() {
        while (!stack.empty()) stack.pop();
        pushStack('Z');
    }
    void addTransitionRule(int from, Rule rule, int to) {
        auto it = std::find_if(automaton_states.begin(), automaton_states.end(), [from](State* state) {
            return state->id == from;
        });

        if (it != automaton_states.end()) {
            Transition* newTransition = new Transition(to, rule);
            (*it)->state_transitions.push_back(newTransition);
        } else {
            std::cerr << "Erro: Estado de origem não encontrado!" << std::endl;
        }
    }
    void defineFinalState(int id) { 
        auto it = std::find_if(automaton_states.begin(), automaton_states.end(), [id](State* state) {
            return state->id == id;
        });

        if (it != automaton_states.end()) {
            (*it)->isTerminal = true;
        } else {
            std::cerr << "Erro: Estado não encontrado!" << std::endl;
        }
    }
    bool isValid(string word) {
        State* currentState = automaton_states.front();
        word+='Z';
        clearStackAndPushZ();        
        auto symbolIt = word.begin();

        while (symbolIt != word.end()) {            
            char symbol = *symbolIt;
            bool isValidTransition = false;            

            for (Transition* t : currentState->state_transitions) {                
                if (t->transition_rules.input == symbol) {
                    if(t->transition_rules.pop == peekStack() || t->transition_rules.pop == epsilon){
                        if(t->transition_rules.pop != epsilon)
                        popStack();
                        if(t->transition_rules.push!="&") for (auto it = t->transition_rules.push.rbegin(); it != t->transition_rules.push.rend(); ++it)
                        pushStack(*it);
                        isValidTransition = true;
                        currentState = automaton_states[t->to];
                        ++symbolIt;
                        break;
                    }         
                }
            }            

            if(!isValidTransition){
                emptysTransitions(currentState);
                for (Transition* t : currentState->state_transitions) {
                    emptysTransitions(currentState);
                    if (t->transition_rules.input == epsilon) {

                        if(t->transition_rules.pop == peekStack() || t->transition_rules.pop == epsilon){
                            if(t->transition_rules.pop != epsilon)
                            popStack();                       
                            if(t->transition_rules.push!="&") for (auto it = t->transition_rules.push.rbegin(); it != t->transition_rules.push.rend(); ++it)
                            pushStack(*it);      
                            


                            currentState = automaton_states[t->to];
                            isValidTransition = true;                      
                                                     


                            break;
                        } 
                    }
                }
            }
            if(!isValidTransition)return false;
            if(symbol=='Z')break; 
        }
        return currentState->isTerminal;
    }

    vector<Transition*> emptysTransitions(const State * currentState) {
        vector<Transition*> emptyTransitions;

        for (Transition* t : currentState->state_transitions) {
            if (t->transition_rules.input == '&') {
                emptyTransitions.push_back(t);
            }
        }


        return emptyTransitions;
    }

    void printAutomaton() {
        cout << "Autômato:" << endl;
        for (State* state : automaton_states) {
            cout << "Estado ID: " << state->id << endl;
            if (state->isTerminal) {
                cout << "  Estado Final" << endl;
            } else {
                cout << "  Não é um estado final" << endl;
            }
            cout << "  Transições:" << endl;
            for (Transition* transition : state->state_transitions) {
                cout << "    Para estado: " << transition->to << endl;
                cout << "    Regra: " << transition->transition_rules.input << " -> "
                    << transition->transition_rules.pop << " -> " << transition->transition_rules.push << endl;
            }
            cout << endl;
        }
    }
    void printStack() {
        if (stack.empty()) {
            cout << "Stack is empty." << endl;
            return;
        }

        cout << "\t\t|S|-> |";
        std::stack<char> tempStack = stack;
        while (!tempStack.empty()) {
            cout << tempStack.top() << "|";
            tempStack.pop();
        }
        cout << endl;
    }
};

int main(){
    setlocale(LC_ALL, "portuguese");
    Automaton automaton;

    int num_state = 6;

    for (int i = 0; i < num_state; ++i) {
        automaton.createState();
    }

    automaton.addTransitionRule(0, Rule('a', '&', "A"), 0);
    automaton.addTransitionRule(0, Rule('&', '&', "&"), 1);
    automaton.addTransitionRule(1, Rule('b', 'A', "&"), 1);
    automaton.addTransitionRule(1, Rule('&', 'Z', "Z"), 2);
    automaton.addTransitionRule(2, Rule('c', '&', "&"), 2);
    automaton.addTransitionRule(0, Rule('&', '&', "&"), 3);
    automaton.addTransitionRule(3, Rule('b', '&', "&"), 3);
    automaton.addTransitionRule(3, Rule('&', '&', "&"), 4);
    automaton.addTransitionRule(4, Rule('c', 'A', "&"), 4);
    automaton.addTransitionRule(4, Rule('&', 'Z', "Z"), 5);

    automaton.defineFinalState(2);
    automaton.defineFinalState(5);
    
    string word1 = "aabbccc";
    bool result1 = automaton.isValid(word1);
    cout << word1 << ": " << (result1 ? "sim" : "nao") << endl;

    string word2 = "aabcc";
    bool result2 = automaton.isValid(word2);
    cout << word2 << ": " << (result2 ? "sim" : "nao") << endl;

    string word3 = "aabbcc";
    bool result3 = automaton.isValid(word3);
    cout << word3 << ": " << (result3 ? "sim" : "nao") << endl;

    string word4 = "abbccc";
    bool result4 = automaton.isValid(word4);
    cout << word4 << ": " << (result4 ? "sim" : "nao") << endl;

    string word5 = "abbcc";
    bool result5 = automaton.isValid(word5);
    cout << word5 << ": " << (result5 ? "sim" : "nao") << endl;

    return 0;
}