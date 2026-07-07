#ifndef BUİLTİNS_H
#define BUİLTİNS_H

#include<string>
#include<vector>


class Builtins{

 public:
     //Gelen komut yerleşik bir komut mu değil mi kontrol edelim
     static bool isBuiltin(const std::string& command);

      
     //Yerleşik komutu çalıştırır eğer komut başarıyla çalıştırılırsa true döner
     static bool execute(const std::vector<std::string>&tokens);

};

#endif