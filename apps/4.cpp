int main(){
    setlocale(LC_ALL, "portuguese");
    Automaton automaton;

    int num_state = 2;

    for (int i = 0; i < num_state; ++i) {
        automaton.createState();
    }

    automaton.addTransitionRule(0, Rule('a', 'Z', "AZ"), 0);
    automaton.addTransitionRule(0, Rule('b', 'Z', "BZ"), 0);
    automaton.addTransitionRule(0, Rule('a', 'B', "&"), 0);
    automaton.addTransitionRule(0, Rule('b', 'A', "&"), 0);
    automaton.addTransitionRule(0, Rule('a', 'A', "AA"), 0);
    automaton.addTransitionRule(0, Rule('b', 'B', "BB"), 0);
    automaton.addTransitionRule(0, Rule('&', 'Z', "Z"), 1);
    
    automaton.defineFinalState(1);
    automaton.defineFinalState(1);
    
    string word1 = "aabb";
    bool result1 = automaton.isValid(word1);
    cout << word1 << ": " << (result1 ? "sim" : "nao") << endl;

    string word2 = "abb";
    bool result2 = automaton.isValid(word2);
    cout << word2 << ": " << (result2 ? "sim" : "nao") << endl;

    string word3 = "abba";
    bool result3 = automaton.isValid(word3);
    cout << word3 << ": " << (result3 ? "sim" : "nao") << endl;

    string word4 = "aabbbbaab";
    bool result4 = automaton.isValid(word4);
    cout << word4 << ": " << (result4 ? "sim" : "nao") << endl;

    string word5 = "aabbbbabab";
    bool result5 = automaton.isValid(word5);
    cout << word5 << ": " << (result5 ? "sim" : "nao") << endl;

    return 0;
}