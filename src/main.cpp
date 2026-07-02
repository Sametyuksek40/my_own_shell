#define _CRT_NO_SECURE_WARNİNGS  
#include<iostream>
#include<string>
#include<vector>
#include<filesystem>
#include<cstdlib>
#include<fstream>


using namespace::std;

//modülleri include edererek herkese ilgili işi veriyoruz


int main(){
//Çıktıların anında ekrana basılması için ana ekranımızı sürekli temiz tutuyoruz
cout<<unitbuf;
cerr<<unitbuf;

string command;

while (true)
{

   cout<<"$ "<<endl;
   if (!getline(cin,command))
   {
     break;
   }
   if (command=="exit")
   {
     break;
   }
   if (!command.empty())
   {
     
    cout<<command<<" command is nout found"<<endl;

   }
   
   

}





     return 0;
}