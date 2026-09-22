// ============================================================
//  XCRK - V.0.8.1  ·  Menu
//  Dexter Demon Team
// ============================================================
#include "xcrk.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>

#define WHATSAPP_CHANNEL "https://whatsapp.com/channel/0029Vb8R7mh4tRrz7K4vBm23"

static void printMenuOptions() {
    std::cout << "  " << RED << "menu" << RESET << "\n\n";
    std::cout << GREEN << "    [1]" << RESET << " brute force       "
              << GRAY << "charset-based\n" << RESET;
    std::cout << GREEN << "    [2]" << RESET << " dataset cracking  "
              << GRAY << "wordlist attack\n" << RESET;
    std::cout << GREEN << "    [3]" << RESET << " rule-based        "
              << GRAY << "mutation attack\n" << RESET;
    std::cout << GREEN << "    [4]" << RESET << " info owner\n";
    std::cout << GREEN << "    [5]" << RESET << " join channel\n";
    std::cout << RED   << "    [0]" << RESET << " exit\n\n";
}

void printOwnerInfo() {
    std::cout << "\n  " << RED << BOLD << "owner info" << RESET << "\n\n";
    std::cout << "  " << GRAY << "team      " << RESET
              << GREEN << "Dexter Demon Team" << RESET << "\n";
    std::cout << "  " << GRAY << "project   " << RESET
              << GREEN << "XCRK v0.8.1" << RESET << "\n";
    std::cout << "  " << GRAY << "purpose   " << RESET
              << "security research & education\n";
    std::cout << "  " << GRAY << "channel   " << RESET
              << GREEN << WHATSAPP_CHANNEL << RESET << "\n";
    std::cout << "  " << GRAY << "status    " << RESET
              << GREEN << "active" << RESET << "\n";
}

static void joinChannel() {
    std::cout << "\n  " << RED << BOLD << "join channel" << RESET << "\n\n";
    std::cout << "  " << GRAY << "WhatsApp Channel:" << RESET << "\n";
    std::cout << "  " << GREEN << WHATSAPP_CHANNEL << RESET << "\n\n";
    std::cout << "  " << GRAY
              << "update, tools baru, dan info lain ada di channel." << RESET
              << "\n";
}

void showMainMenu() {
    for (;;) {
        std::cout << "\n";
        printMenuOptions();

        std::cout << "  " << GRAY << "pilih › " << RESET;
        std::string in;
        if (!std::getline(std::cin, in)) break;
        std::transform(in.begin(), in.end(), in.begin(),
                       [](unsigned char c){ return std::tolower(c); });

        if (in == "1")      runBruteForce();
        else if (in == "2") runDatasetCracking();
        else if (in == "3") runRuleBased();
        else if (in == "4") printOwnerInfo();
        else if (in == "5") joinChannel();
        else if (in == "0" || in == "q" || in == "exit") {
            std::cout << "\n  " << GREEN << "bye." << RESET << "\n";
            break;
        }
        else {
            std::cout << "  " << RED << "pilihan tidak valid." << RESET << "\n";
        }

        std::cout << "\n  " << GRAY << "enter untuk lanjut..." << RESET;
        std::cin.get();
    }
}
