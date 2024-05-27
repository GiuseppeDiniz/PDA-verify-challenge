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