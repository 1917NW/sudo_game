#include "command.h"
class SudoGenerator
{
private:
    /* data */
public:
    SudoGenerator(/* args */);
    ~SudoGenerator();
    void generate_endGame(const Command& command);
    void generate_sudo_game(const Command& command);
    
};

SudoGenerator::SudoGenerator(/* args */)
{
}

SudoGenerator::~SudoGenerator()
{
}
