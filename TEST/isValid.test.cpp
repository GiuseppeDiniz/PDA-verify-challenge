bool isValid(string word) {
        State* currentState = automaton_states.front();
        word+='Z';
        clearStackAndPushZ();
        
        auto symbolIt = word.begin();

        while (symbolIt != word.end()) {
            char symbol = *symbolIt;
            bool isEmptyInput = true;
            std::cout << "symbol: '" << symbol << "'" << endl;

            for (Transition* t : currentState->state_transitions) {                
                if (t->transition_rules.input == symbol) {
                    cout << "\tinput = " << t->transition_rules.input << endl;
                    if(t->transition_rules.pop == peekStack() || t->transition_rules.pop == epsilon){
                        if(t->transition_rules.pop != epsilon) popStack();
                            if(t->transition_rules.push!="&") for (auto it = t->transition_rules.push.rbegin(); it != t->transition_rules.push.rend(); ++it) {
                                pushStack(*it);
                            }
                        isEmptyInput = false;
                        cout << "\t\t change from state " << currentState->id << " to state " << t->to << endl;
                        printStack();
                        currentState = automaton_states[t->to];
                        ++symbolIt;
                        break;
                    }         
                }
            }

            if(isEmptyInput){
                for (Transition* t : currentState->state_transitions) {
                    if (t->transition_rules.input == epsilon) {
                        cout << "\tinput = &" << endl;      
                        if(t->transition_rules.pop == peekStack() || t->transition_rules.pop == epsilon){

                            if(t->transition_rules.pop != epsilon)
                            popStack();                            
                        
                            if(t->transition_rules.push!="&") for (auto it = t->transition_rules.push.rbegin(); it != t->transition_rules.push.rend(); ++it)
                            pushStack(*it);
                            
                            cout << "\t\t change from state " << currentState->id << " to state " << t->to << endl;
                            currentState = automaton_states[t->to];
                            printStack();
                            if(symbol=='Z')++symbolIt;
                            break;
                        } 
                        return false; // posso ter mais de uma transicao vazia??
                    }
                }
            }            
        }
        return currentState->isTerminal;
    }


        bool isValid(string word) {
        State* currentState = automaton_states.front();
        word+='Z';
        clearStackAndPushZ();
        
        auto symbolIt = word.begin();

        while (symbolIt != word.end()) {
            char symbol = *symbolIt;
            bool isEmptyInputTransition = true, isValidTransition = false;
            for (Transition* t : currentState->state_transitions) {                
                if (t->transition_rules.input == symbol) {
                    if(t->transition_rules.pop == peekStack() || t->transition_rules.pop == epsilon){
                        if(t->transition_rules.pop != epsilon) popStack();
                            if(t->transition_rules.push!="&") for (auto it = t->transition_rules.push.rbegin(); it != t->transition_rules.push.rend(); ++it) {
                                pushStack(*it);
                            }
                        isEmptyInputTransition = false;
                        isValidTransition = true;
                        currentState = automaton_states[t->to];
                        ++symbolIt;
                        break;
                    }         
                }
            }            

            if(isEmptyInputTransition){
                for (Transition* t : currentState->state_transitions) {
                    if (t->transition_rules.input == epsilon) {
                        if(t->transition_rules.pop == peekStack() || t->transition_rules.pop == epsilon){
                            if(t->transition_rules.pop != epsilon)
                            popStack();                       
                            if(t->transition_rules.push!="&") for (auto it = t->transition_rules.push.rbegin(); it != t->transition_rules.push.rend(); ++it)
                            pushStack(*it);                            
                            currentState = automaton_states[t->to];
                            if(symbol=='Z')++symbolIt;
                            isValidTransition = true;
                            break;
                        } 
                    }
                }
            }
            if(!isValidTransition)return false;       
        }
        return currentState->isTerminal;
    }