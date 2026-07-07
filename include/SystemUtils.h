#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H
#include<string>

class SystemUtils{
public:
//Gelen komutun sistem üzerindeki tam yolunu bulur
//bulursa tam yolu,bulamazsa boş string döner

static std::string getExecutable(const std::string& command);


};




#endif