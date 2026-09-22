#include "xcrk.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstdlib>

struct HashEntry {
    std::string hash;
    std::string algo;
    std::string password;
    std::string kategori;
};

struct Analisis {
    std::string algo;
    bool valid;
    bool foundDiDataset;
    std::string password;
    std::string kategori;
    std::string saran;
    std::string tipe;
};

bool otakLoad(const std::string& path);
const std::vector<std::string>& otakGetTips();
const std::vector<HashEntry>& otakGetHashes();
Analisis logikaAnalisis(const std::string& hash);

static std::string trimStr(const std::string& s) {
    auto notSpace = [](unsigned char ch){ return !std::isspace(ch); };
    auto b = std::find_if(s.begin(), s.end(), notSpace);
    auto e = std::find_if(s.rbegin(), s.rend(), notSpace).base();
    if (b >= e) return "";
    return std::string(b, e);
}

static std::string toLowerStr(const std::string& s) {
    std::string r = s;
    std::transform(r.begin(), r.end(), r.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return r;
}

static void aiBanner() {
    std::cout << "\n  " << RED << BOLD << "hash ai chatbot" << RESET
              << GRAY << " · offline · v1.0\n" << RESET;
    std::cout << "  " << GRAY
              << "ketik 'help' buat bantuan, 'exit' buat keluar\n\n" << RESET;
}

static void aiHelp() {
    std::cout << "\n  " << GREEN << "perintah:" << RESET << "\n";
    std::cout << "    " << GRAY << "·" << RESET << " ketik hash langsung       "
              << GRAY << "→ analisa hash\n" << RESET;
    std::cout << "    " << GRAY << "·" << RESET << " tips                       "
              << GRAY << "→ tampilkan tips\n" << RESET;
    std::cout << "    " << GRAY << "·" << RESET << " dataset                    "
              << GRAY << "→ info dataset\n" << RESET;
    std::cout << "    " << GRAY << "·" << RESET << " help                       "
              << GRAY << "→ bantuan ini\n" << RESET;
    std::cout << "    " << GRAY << "·" << RESET << " clear                      "
              << GRAY << "→ bersihin layar\n" << RESET;
    std::cout << "    " << GRAY << "·" << RESET << " exit                       "
              << GRAY << "→ keluar\n\n" << RESET;
}

static void aiTips() {
    const auto& tips = otakGetTips();
    std::cout << "\n  " << RED << "tips dari AI:" << RESET << "\n";
    if (tips.empty()) {
        std::cout << "    " << GRAY << "belum ada tips di dataset.json\n" << RESET;
        return;
    }
    for (const auto& t : tips) {
        std::cout << "    " << GREEN << "›" << RESET << " " << t << "\n";
    }
    std::cout << "\n";
}

static void aiDataset() {
    int count = (int)otakGetHashes().size();
    std::cout << "\n  " << RED << "dataset:" << RESET << "\n";
    std::cout << "    " << GRAY << "·" << RESET << " file   "
              << GREEN << "dataset.json" << RESET << "\n";
    std::cout << "    " << GRAY << "·" << RESET << " status "
              << GREEN << "loaded" << RESET << "\n";
    std::cout << "    " << GRAY << "·" << RESET << " total  "
              << GREEN << count << " hash" << RESET << "\n\n";
}

static void aiAnalisa(const std::string& hash) {
    std::cout << "\n  " << RED << "analyzing..." << RESET << "\n\n";

    Analisis a = logikaAnalisis(hash);

    std::cout << "  " << GRAY << "input    " << RESET << hash << "\n";

    if (!a.valid) {
        std::cout << "  " << GRAY << "status   " << RESET << RED
                  << "bukan hash valid" << RESET << "\n";
        std::cout << "  " << GRAY << "saran    " << RESET
                  << "pastikan hex & panjang 32/40/64\n\n";
        return;
    }

    std::cout << "  " << GRAY << "algo     " << RESET
              << GREEN << a.algo << RESET << "\n";

    if (a.foundDiDataset) {
        std::cout << "  " << GRAY << "status   " << RESET
                  << GREEN << BOLD << "ketemu di dataset!" << RESET << "\n";
        std::cout << "  " << GRAY << "password " << RESET
                  << GREEN << BOLD << a.password << RESET << "\n";
        std::cout << "  " << GRAY << "kategori " << RESET
                  << a.kategori << "\n";
        if (!a.tipe.empty())
            std::cout << "  " << GRAY << "tipe     " << RESET
                      << a.tipe << "\n";
    } else {
        std::cout << "  " << GRAY << "status   " << RESET
                  << RED << "gak ada di dataset" << RESET << "\n";
        std::cout << "  " << GRAY << "saran    " << RESET
                  << a.saran << "\n";
    }
    std::cout << "\n";
}

void runAIChat() {
    bool ok = otakLoad("dataset.json");

    if (!ok) {
        const char* home = std::getenv("HOME");
        if (home) {
            std::string alt1 = std::string(home) + "/xcrk/dataset.json";
            std::string alt2 = std::string(home) + "/dataset.json";
            if (otakLoad(alt1)) ok = true;
            else if (otakLoad(alt2)) ok = true;
        }
    }

    if (!ok) {
        std::cout << "\n  " << RED << "[!] dataset.json gak ketemu." << RESET << "\n";
        std::cout << "  " << GRAY << "pastikan file dataset.json ada di folder ini\n";
        std::cout << "  atau di ~/xcrk/dataset.json\n\n" << RESET;
        return;
    }

    aiBanner();

    for (;;) {
        std::cout << "  " << RED << "ai" << RESET
                  << GRAY << " › " << RESET;
        std::string in;
        if (!std::getline(std::cin, in)) break;
        in = trimStr(in);
        if (in.empty()) continue;

        std::string low = toLowerStr(in);

        if (low == "exit" || low == "quit" || low == "q" || low == "keluar") {
            std::cout << "\n  " << GREEN << "bye." << RESET << "\n\n";
            break;
        }
        if (low == "help" || low == "?" || low == "bantuan") {
            aiHelp();
            continue;
        }
        if (low == "tips" || low == "tip") {
            aiTips();
            continue;
        }
        if (low == "dataset" || low == "data") {
            aiDataset();
            continue;
        }
        if (low == "clear" || low == "cls") {
            std::cout << "\033[2J\033[H";
            aiBanner();
            continue;
        }

        aiAnalisa(in);
    }
}
