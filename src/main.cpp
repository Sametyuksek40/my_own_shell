#define _CRT_NO_SECURE_WARNİNGS  
#include<iostream>
#include<string>
#include<vector>
#include<filesystem>
#include<cstdlib>
#include<fstream>


#include"CommandParser.h"


using namespace::std;

//modülleri include edererek herkese ilgili işi veriyoruz


int main(){
//Çıktıların anında ekrana basılması için ana ekranımızı sürekli temiz tutuyoruz
cout<<unitbuf;
cerr<<unitbuf;

string input_line;

while (true)
{

   cout<<"$ ";
   if (!getline(cin,input_line))
   {
     break;
   }

//? 1.adım Kullanıcının komutunu işlemesi için parsera yolluyoruz

vector<string>tokens=CommandParser::parse(input_line);

//? Eğer kullanıcı hiçbirsey yazmadan ENTER ladıysa döngünün başına dön

if (tokens.empty())
{
     
     continue;
}

//! Listenin ilk elemanı herzaman ana komuttur

string command=tokens[0];
   

//Şimdilik test amaçlı exit çıkış modu

if (command=="exit")
{
     break;
}

// DEBUG / TEST MODU: 
        // Ayrıştırıcımızın girdiyi nasıl kelimelere böldüğünü net görebilmek için ekrana basalım
        std::cout << "[DEBUG] Ayristirilan Kelime Sayisi: " << tokens.size() << "\n";
        for (size_t i = 0; i < tokens.size(); ++i) {
            std::cout << "  -> Kelime [" << i << "]: " << tokens[i] << "\n";
        }

        // Şimdilik geçici bir uyarı basıyoruz (İleride burası Builtins ve SystemUtils'e bağlanacak)
        std::cout << command << ": command not found (Builtins ve PATH sistemleri henüz eklenmedi)\n";


}




     return 0;
}