#include"CommandParser.h"

/*
     1- tek tırnak,çift tırnak,ters eğik çizgi(tek-çift) kaçışı,boşluk algılanması ve durum değerlendiril
     2-for ile bir döngüye sok 
     3-ayrıştırma daha sonra başlıyor
      
*/
std::vector<std::string>CommandParser::parse(const std::string&input){

     bool in_single_quote=false;
     bool in_double_quote=false;
     
     std::vector<std::string> tokens;
     std::string current_token;

    size_t length=input.length();



    for (size_t i = 0; i < length; i++)
    {
   
      //ilk hedefimiz eğik çizgilerden kaçınmak olacak 
      // tek tırnak kaçış davranışımız farklı,çift tırnakda kaççış davranışımız ise daha farklı olacak
      
      
      char c=input[i];

      //! 1.ters eğik çizgiden kaçış

      if (c=='\\')
      {
          //tek tırnak içerisindeysek ters eğik çizginin hiçbir özel anlamı yok
          if (in_single_quote)
          {
               current_token+=c;
          }

          //Eğer çift tırnak içerisindeysek

         else if (in_double_quote)
          {
              if (i+1<length&&input[i+1]=='"'||input[i+1]=='\\')
              {
                  //Bu durumda bir sonraki karakteri doğrudan al
                  current_token+=c;
                  i++;
              }

              else
              {
               //diğer karakterlerde ise durum daha farklı olur ,o karakterleri korusun ekstra bir kaçış içine girmesin
               current_token+=c;

              }
          }
          

          //Eğer Hiçbir tırnak içerisinde değilsek ise "\" karakteri kendisinden sonra gelen her karakteri
          //düz metin yapar.

          else
          {
               if (i+1<length)
               {
               
                    current_token+=input[i+1];
                    i++;
               }
               
          }
          continue;

      }
      
      //! 2.Tırnak kontrolü tek tırnak

      if (c=='\'')
      {
                 
          //tek tırnağın içindeki çift tırnak düz karakterdir

          if (in_double_quote)
          {
               current_token+=c;
          }
          else
          {
               //Tek tırnak durumunu tersine çevir açıksa kapat,kapalysa aç
                  
               in_single_quote=!in_single_quote;

          }

      }



     //! 3. Tırnak Kontrolü cift tırnak
      
     if (c=='"')
     {
     
          // çif tırnağın içindeki tek tırnak düz karakter olarak ele alınır

         if (in_single_quote)
         {
          current_token+=c;
         }
         else
         {
          in_double_quote=!in_double_quote;
         }
         continue;

     }
     


    //! 4. Boşluk kontrolü

    if (c==' '|| c=='\t')
    {
     
      //Herhangi bir tırnağın içerisindeysek boşluğumuzu koruyoruz.

      if (in_double_quote||in_single_quote)
      {
          current_token+=c;
      }
      
      else
      {
          //Tırnak dışındaysak ve elimizde birikmiş kelimeler varsa listeye yolluyoruz
          
          if (!current_token.empty())
          {
               tokens.push_back(current_token);
               current_token.clear();

          }
          

      }
      
        continue;


    }

    //! 5.Durum sıradan karakterler 

    current_token+=c;
    
    


   
}

//! Döngü bittiğinde satırın sonunda kalan kelimeyi de döngüye ekle

if (!current_token.empty())
{

  tokens.push_back(current_token);

}


return tokens;

}