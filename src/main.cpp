#define _CRT_NO_SECURE_WARNİNGS  
#include<iostream>
#include<string>
#include<vector>
#include<filesystem>
#include<cstdlib>
#include<fstream>
#include "Builtins.h"

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

   // DÜZELTME: Temizliği PARÇALAMADAN ÖNCE yapıyoruz!
    if (!input_line.empty() && input_line.back() == '\r') {
        input_line.pop_back();
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
 
if (Builtins::execute(tokens))
{
  continue;
}

cout<<command<<" : command not found "<<endl;


}



     return 0;
}