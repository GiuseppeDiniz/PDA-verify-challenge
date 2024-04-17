#include <iostream>
#include <fstream>
#include <string>
#include "PDA.h"

int main(int argc, char const *argv[])
{
    std::ifstream file(argv[1]);
    std::string line;

    if(file.is_open())
    {
        while (getline(file,line)) 
        {
            std::cout << line << std::endl;
        }
        file.close();        
    } else
    {
        std::cout << "Error opening the file." << std::endl;
    }

    // Criando o autômato
    Automaton automaton;

    // Criando os estados
    State* q0 = automaton.createState(false);
    State* q1 = automaton.createState(false);
    State* q2 = automaton.createState(true); // estado terminal

    // Adicionando transições
    automaton.addTransition(q0, q0, Rule('a', '&', "A"));
    automaton.addTransition(q0, q1, Rule('&', '&', "&"));
    automaton.addTransition(q1, q1, Rule('b', 'A', "&"));
    automaton.addTransition(q1, q2, Rule('&', 'Z', "Z"));

    // Exibindo as transições do autômato
    automaton.printTransitions();
    
    // Verifica se a palavra é aceita
    automaton.isAccepted("aabb");

    return 0;
}