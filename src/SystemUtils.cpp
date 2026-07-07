// Microsoft derleyicilerinde "getenv güvensizdir" uyarısını kapatmak için EN ÜSTE yazılmalıdır
#define _CRT_SECURE_NO_WARNINGS
#include "SystemUtils.h"
#include <cstdlib>
#include <sstream>
#include <filesystem>
#include <vector>

// İşletim sistemine göre Ayar verme
#ifdef _WIN32
    #include <io.h>
    #define access _access
    const char PATH_SEP = ';'; // WIN32'de klasörler ; ile ayrılır

    // MinGW'nin hatalı X_OK (1) tanımını ezip zorla 0 yapıyoruz!
    #ifdef X_OK
        #undef X_OK
    #endif
    #define X_OK 0

#else
    #include <unistd.h>
    const char PATH_SEP = ':';
#endif   


std::string SystemUtils::getExecutable(const std::string& command) {
    const char* path_env = std::getenv("PATH");
    if (path_env == nullptr) {
        return "";
    }

    std::stringstream ss(path_env);
    std::string dir;

    while (std::getline(ss, dir, PATH_SEP)) {
        // Klasör yolundaki görünmez boşluk ve hatalı karakterleri temizle
        dir.erase(0, dir.find_first_not_of(" \t\r\n"));
        dir.erase(dir.find_last_not_of(" \t\r\n") + 1);

        if (dir.empty()) continue;

        std::filesystem::path dir_path(dir);

#ifdef _WIN32
        // Windows için: Komutun hem yalın halini hem de yaygın uzantılarını ara
        std::vector<std::string> extensions = {"", ".exe", ".cmd", ".bat"};
        for (const std::string& ext : extensions) {
            std::filesystem::path full_path = dir_path / (command + ext);
            std::error_code ec;

            if (std::filesystem::is_regular_file(full_path, ec) && access(full_path.string().c_str(), X_OK) == 0) {
                return full_path.string();
            }
        }
#else
        // Linux/Mac için sadece yalın hali yeterlidir
        std::filesystem::path full_path = dir_path / command;
        std::error_code ec;
        if (std::filesystem::is_regular_file(full_path, ec) && access(full_path.string().c_str(), X_OK) == 0) {
            return full_path.string();
        }
#endif
    }
    return "";
}