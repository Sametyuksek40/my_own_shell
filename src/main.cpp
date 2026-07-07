#include <iostream>
#include "Shell.h"

int main() {
    // Çıktı tamponlarını kapatıyoruz (Terminalin anlık tepki vermesi için)
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // Orkestra şefimizi sahneye davet edip programı başlatıyoruz
    Shell my_shell;
    my_shell.run();

    return 0;
}