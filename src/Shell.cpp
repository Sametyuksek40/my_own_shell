#include "Shell.h"
#include "CommandParser.h"
#include "Builtins.h"
#include "SystemUtils.h"
#include <iostream>
#include <cstdlib> // std::system için

void Shell::run() {
    std::string input_line;

    while (true) {
        std::cout << "$ ";
        if (!std::getline(std::cin, input_line)) {
            break;
        }

        // Windows'un gizli \r karakterini temizle
        if (!input_line.empty() && input_line.back() == '\r') {
            input_line.pop_back();
        }

        // 1. Akıllı Ayrıştırıcı ile girdiyi parçala
        std::vector<std::string> tokens = CommandParser::parse(input_line);
        if (tokens.empty()) continue;

        // 2. Önce Yerleşik Komut (Builtin) mi diye bak
        if (Builtins::execute(tokens)) {
            continue; // Yerleşik komutsa çalıştı ve bitti, başa dön
        }

        // 3. Yerleşik değilse, dış program olarak çalıştırmayı dene
        executeExternal(tokens[0], tokens);
    }
}

void Shell::executeExternal(const std::string& command, const std::vector<std::string>& tokens) {
    // Dedektifimiz programın yerini bulsun
    std::string exec_path = SystemUtils::getExecutable(command);

    if (!exec_path.empty()) {
        // Program bulundu! Şimdi onu C++'ın std::system fonksiyonu ile çalıştırılabilir 
        // bir string komutuna dönüştüreceğiz.
        
        // Windows'ta yollar boşluk içerebilir (örn: C:\Program Files\...),
        // bu yüzden yolu çift tırnak içine alıyoruz.
        std::string sys_cmd = "\"" + exec_path + "\"";
        
        // Argümanları yanına ekle (Örn: "git" "--version" gibi)
        for (size_t i = 1; i < tokens.size(); ++i) {
            sys_cmd += " " + tokens[i];
        }

        // İşletim sistemine komutu icra ettir
        std::system(sys_cmd.c_str());
    } 
    else {
        // Hiçbir yerde bulunamadıysa nihai hatayı bas
        std::cout << command << ": command not found\n";
    }
}