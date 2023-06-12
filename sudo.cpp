#include<iostream>
#include<cstring>
#include "command.h"
using namespace std;

Command parseCommand(int argc, char* argv[]);

int main(int argc, char* argv[]){
   Command command = parseCommand(argc, argv);
   command.show();
}

Command parseCommand(int argc, char* argv[]){
    Command command = Command();
    if(strcmp(argv[1], "-c") == 0){
        command.is_create = true;
        try{
            if(argc >= 3)
                command.endboard_number = atoi(argv[2]);
            else
                cerr<<"arg c need a num"<<endl;
        }
        catch(exception e){
            cerr<<"need a number"<<endl;
        }
    }
    else if(strcmp(argv[1], "-s") == 0){
        command.is_solve = true;
        if(argc >= 3)
            command.board_path = argv[2];
        else
            cerr<<"arg s need a path"<<endl;
    }
    else{
        for(int i = 1; i < argc; i++){
            if(strcmp(argv[i], "-n") == 0){
                try{
                    command.game_number = atoi(argv[++i]);  
                }catch(exception e){
                    cerr<<"arg n need a number"<<endl;
                }
           
        }
        else if(strcmp(argv[i], "-m") == 0){
                try{
                    command.game_hard_level = atoi(argv[++i]);  
                }catch(exception e){
                    cerr<<"arg m need a number"<<endl;
                }
        }
        else if(strcmp(argv[i], "-u") == 0){
            command.is_unique = true;
        }
        else if(strcmp(argv[i], "-r") == 0){
            try{
            command.hole_number = atoi(argv[++i]);
            }catch(exception e){
                cerr<<"arg r need a number"<<endl;
            }
        }
           
    }
    
    }

    return command;
}