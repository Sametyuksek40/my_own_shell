#ifndef SHELL_H
#define SHELL_H

#include <string>
#include<vector>

class Shell{
public:
//Kabuğun ana yaşam döngüsünü başlatır.(REPL)
void run();
private:

void executeExternal(const std::string&command,const std::vector<std::string>& tokens);


};

#endif 