#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include<string>
#include<vector>

class CommandParser{
     public:
     //Kullanıcıdan gelen ham satırı alır,kurallara göre parçalayıp bir kelime listesi döner
     static  std::vector<std::string> parse(const std::string& input);
};

#endif


