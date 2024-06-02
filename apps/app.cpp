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
    string invertString(const string& str) {
        string reversed(str.rbegin(), str.rend());
        return reversed;
    }
    bool isValid(int stateNumber, const std::string& word, std::stack<char>& stack, std::vector<std::tuple<int, std::string, std::stack<char>>>& configurations){
        State* currentState = automaton_states[stateNumber];
        std::stack<char> stackcpy = stack;
        string newWord = word;

        configurations.push_back(std::make_tuple(stateNumber, newWord, stackcpy));

        if (currentState->isTerminal && newWord.empty() && stackcpy.top() == 'Z' && stackcpy.size() == 1) {
            return true;
        }

        for (Transition* t : currentState->state_transitions) {
            if (t->transition_rules.input == newWord[0] || t->transition_rules.input == epsilon) {
                if (t->transition_rules.pop == stackcpy.top() || t->transition_rules.pop == epsilon) {
                    if(t->transition_rules.input!=epsilon)newWord = newWord.substr(1);
                    if(t->transition_rules.pop!=epsilon)stackcpy.pop();
                    if(t->transition_rules.push!="&"){
                        string stringPush = invertString(t->transition_rules.push);
                        for ( char letter : stringPush) stackcpy.push(letter);
                    }
                    if(isValid(t->to,newWord,stackcpy,configurations)){
                        return true;
                    }else{
                        newWord = word;
                        stackcpy = stack;
                        configurations.pop_back();
                    }
                }                
            }
        }
        return false;
    }
};

void printConfiguration(const std::vector<std::tuple<int, std::string, std::stack<char>>>& configurations) {
    for (size_t i = 0; i < configurations.size(); ++i) {
        int stateNumber = std::get<0>(configurations[i]);
        std::string word = std::get<1>(configurations[i]);
        std::stack<char> stack = std::get<2>(configurations[i]);

        std::stack<char> tempStack = stack;
        std::string stackContents;
        
        while (!tempStack.empty()) {
            stackContents = tempStack.top() + stackContents;
            tempStack.pop();
        }

        std::string displayWord = word.empty() ? "&" : word;

        std::cout << "(q" << stateNumber << ", " << displayWord << ", " << stackContents << ")";
        if (i == configurations.size() - 1) {
            std::cout << "." << std::endl;
        } else {
            std::cout << " |- " << endl;
        }
    }
}

int main(){
    Automaton automaton;
    std::stack<char> myStack;
    myStack.push('Z');

    int num_state, num_transitions, num_state_final;
    int from, to;
    char input, pop;
    string word, push;

    cin >> num_state >> num_transitions;

    for (int i = 0; i < num_state; ++i) {
        automaton.createState();
    }

    for (int i = 0; i < num_transitions; ++i){
        cin >> from >> input >> pop >> push >> to;
        automaton.addTransitionRule(from, Rule(input, pop, push), to);

    }

    cin >> num_state_final;
    for (int i = 0; i < num_state_final; ++i) {
        int final_state;
        cin >> final_state;
        automaton.defineFinalState(final_state);
    }
    
    while (true) {
        std::cin >> word;
        if (word ==  "*") {
            break;
        }
        std::stack<char> stackCopy = myStack;
        std::vector<std::tuple<int, std::string, std::stack<char>>> configurations;
        bool result = automaton.isValid(0, word, stackCopy, configurations);
        std::cout<< '\n' << word << ": " << (result ? "sim" : "não") << std::endl;
        if (result) printConfiguration(configurations);
    }
    
    return 0;
}

