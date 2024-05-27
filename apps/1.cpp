int main(){
    setlocale(LC_ALL, "portuguese");
    Automaton automaton;

    int num_state = 3;

    for (int i = 0; i < num_state; ++i) {
        automaton.createState();
    }

    automaton.addTransitionRule(0,Rule('a','&',"A"),0);
    automaton.addTransitionRule(0,Rule('&','&',"&"),1);
    automaton.addTransitionRule(1,Rule('b','A',"&"),1);
    automaton.addTransitionRule(1,Rule('&','Z',"Z"),2);

    automaton.defineFinalState(2);

    string word1 = "ab";
    bool result1 = automaton.isValid(word1);
    cout << word1 << ": " << (result1 ? "sim" : "nao") << endl;

    string word2 = "aabb";
    bool result2 = automaton.isValid(word2);
    cout << word2 << ": " << (result2 ? "sim" : "nao") << endl;

    string word3 = "aabba";
    bool result3 = automaton.isValid(word3);
    cout << word3 << ": " << (result3 ? "sim" : "nao") << endl;

    string word4 = "abb";
    bool result4 = automaton.isValid(word4);
    cout << word4 << ": " << (result4 ? "sim" : "nao") << endl;

    string word5 = "aab";
    bool result5 = automaton.isValid(word5);
    cout << word5 << ": " << (result5 ? "sim" : "nao") << endl;

    string word6 = "aaabbb";
    bool result6 = automaton.isValid(word6);
    cout << word6 << ": " << (result6 ? "sim" : "nao") << endl;

    string word7 = "aaaaabbbb";
    bool result7 = automaton.isValid(word7);
    cout << word7 << ": " << (result7 ? "sim" : "nao") << endl;

    string word8 = "aaaaabbbbb";
    bool result8 = automaton.isValid(word8);
    cout << word8 << ": " << (result8 ? "sim" : "nao") << endl;

    string word9 = "aaaaabbbbbb";
    bool result9 = automaton.isValid(word9);
    cout << word9 << ": " << (result9 ? "sim" : "nao") << endl;

    return 0;
}