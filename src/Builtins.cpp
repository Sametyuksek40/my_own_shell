#include"Builtins.h"
#include"SystemUtils.h"
#include<iostream>
#include<filesystem>


bool Builtins::isBuiltin(const std::string&command){

     return (command=="exit"|| command=="pwd"||command=="echo"||command=="type"||command=="cd");

}


bool Builtins::execute(const std::vector<std::string>&tokens){

if (tokens.empty())return false;


//! 1.exit komutu çalıştığında 

std::string cmd=tokens[0];

if (cmd=="exit")
{
     std::exit(0);
}


//! 2. pwd komutu çalıştığında(print working directory )

if (cmd=="pwd")
{
     
try
{
     std::cout<<std::filesystem::current_path().string()<<std::endl;
}
catch(const std::exception& e)
{
     std::cerr <<" pwd hatasi"<<e.what() << '\n';
}
return true;

}


//! 3 type komutu

if (cmd=="type")
{
  if (tokens.size()<2)
  {
     return true;
  }
std::string tip=tokens[1];
if (isBuiltin(tip))
{
     std::cout<<tip<<" is a shell builtin "<<std::endl;
}
     
else
{
     //Eğer yerleşik değilse PATH içinde aranacak.
std::string exec_path=SystemUtils::getExecutable(tip);



if (!exec_path.empty())
{
     //program bulunduysa tam yolunu ekrana bas 
     std::cout<<tip<<" is "<<  exec_path<<std::endl;
}
else
{
     //Hiçbir yerde bulunamadi

     std::cout<<tip<<" is not found "<<std::endl;
}

}
return true;

}


//! 4 cd komutu 
if (cmd == "cd") {
        if (tokens.size() < 2) return true;
        
        std::string target_dir = tokens[1];
        
        // Windows'taki olası \r karakterini temizle
        if (!target_dir.empty() && target_dir.back() == '\r') target_dir.pop_back();

        if (target_dir == "~") {
            const char* home = std::getenv("HOME");
            if (home == nullptr) home = std::getenv("USERPROFILE");
            if (home != nullptr) target_dir = home;
        }

        std::error_code ec;
        std::filesystem::current_path(target_dir, ec);
        
        if (ec) {
            std::cout << "cd: " << tokens[1] << ": No such file or directory\n";
        }
        return true; // BURASI ÇOK ÖNEMLİ: true dönmelisin!
    }






return false;
}



