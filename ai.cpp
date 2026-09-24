#include "xcrk.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>

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
const std::vector<std::string>& otakChatReplies(const std::string& key);
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

static std::string pickRandom(const std::vector<std::string>& v, const std::string& fallback) {
    if (v.empty()) return fallback;
    return v[std::rand() % v.size()];
}

static bool isHashLike(const std::string& s) {
    if (s.size() != 32 && s.size() != 40 && s.size() != 64 && s.size() != 128) return false;
    for (char c : s) if (!std::isxdigit((unsigned char)c)) return false;
    return true;
}

static bool containsAny(const std::string& s, std::initializer_list<const char*> keys) {
    for (auto k : keys) {
        if (s.find(k) != std::string::npos) return true;
    }
    return false;
}

static void aiBanner() {
    std::cout << "\n  " << RED << BOLD << "hash ai chatbot" << RESET
              << GRAY << " · offline · v1.3\n" << RESET;
    std::cout << "  " << GRAY
              << "bisa diajak ngobrol & analisa hash. ketik 'help'\n\n" << RESET;
}

static void aiHelp() {
    std::cout << "\n  " << GREEN << "perintah:" << RESET << "\n";
    std::cout << "    " << GRAY << "·" << RESET << " ketik hash           → analisa hash\n";
    std::cout << "    " << GRAY << "·" << RESET << " halo / hai / assalamualaikum\n";
    std::cout << "    " << GRAY << "·" << RESET << " siapa kamu / siapa pembuatmu\n";
    std::cout << "    " << GRAY << "·" << RESET << " cara pakai / fitur\n";
    std::cout << "    " << GRAY << "·" << RESET << " kenapa / knp / ada apa\n";
    std::cout << "    " << GRAY << "·" << RESET << " tips / dataset\n";
    std::cout << "    " << GRAY << "·" << RESET << " clear / exit\n\n" << RESET;
}

static void aiTips() {
    const auto& tips = otakGetTips();
    std::cout << "\n  " << RED << "tips dari AI:" << RESET << "\n";
    if (tips.empty()) {
        std::cout << "    " << GRAY << "belum ada tips\n" << RESET;
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
        std::cout << "\n  " << GRAY
                  << pickRandom(otakChatReplies("hash_tidak_ditemukan"),
                                "coba fitur lain di menu utama")
                  << RESET << "\n";
    }
    std::cout << "\n";
}

void runAIChat() {
    std::srand((unsigned)std::time(nullptr));

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
        std::cout << "\n  " << RED << "[!] dataset.json gak ketemu." << RESET << "\n\n";
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
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("bye"), "bye.") << RESET
                      << "\n\n";
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

        if (containsAny(low, {"assalamualaikum", "assalamu", "salam"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("assalamualaikum"),
                                    "waalaikumsalam") << RESET << "\n\n";
            continue;
        }
        if (containsAny(low, {"selamat pagi", "pagi"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("pagi"), "pagi") << RESET << "\n\n";
            continue;
        }
        if (containsAny(low, {"selamat siang", "siang"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("siang"), "siang") << RESET << "\n\n";
            continue;
        }
        if (containsAny(low, {"selamat sore", "sore"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("sore"), "sore") << RESET << "\n\n";
            continue;
        }
        if (containsAny(low, {"selamat malam", "malam"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("malam"), "malam") << RESET << "\n\n";
            continue;
        }
        if (containsAny(low, {"knp", "kenapa", "mengapa", "ada apa"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("knp"), "kenapa ya") << RESET << "\n\n";
            continue;
        }
        if (containsAny(low, {"maaf", "sorry"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("maaf"), "gapapa") << RESET << "\n\n";
            continue;
        }
        if (containsAny(low, {"tolong", "bantu"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("tolong"), "siap") << RESET << "\n\n";
            continue;
        }
        if (containsAny(low, {"bingung", "gak ngerti", "gak paham"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("bingung"), "coba 'help'") << RESET << "\n\n";
            continue;
        }
        if (containsAny(low, {"mantap", "keren", "bagus", "nice"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("mantap"), "sip") << RESET << "\n\n";
            continue;
        }
        if (containsAny(low, {"capek", "lelah", "tired"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("capek"), "istirahat") << RESET << "\n\n";
            continue;
        }
        if (containsAny(low, {"senang", "happy", "bahagia"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("senang"), "sip") << RESET << "\n\n";
            continue;
        }
        if (containsAny(low, {"sedih", "galau"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("sedih"), "santai") << RESET << "\n\n";
            continue;
        }
        if (low == "iya" || low == "ya" || low == "yoi" || low == "yup") {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("iya"), "oke") << RESET << "\n\n";
            continue;
        }
        if (low == "tidak" || low == "tdk" || low == "no" || low == "engga") {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("tidak"), "oke") << RESET << "\n\n";
            continue;
        }
        if (containsAny(low, {"siapa kamu", "kamu siapa", "nama kamu"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("siapa_kamu"), "gue xcrk-ai") << RESET
                      << "\n\n";
            continue;
        }
        if (containsAny(low, {"pembuat", "yang buat", "owner", "creator"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("pembuat"), "dexter demon team") << RESET
                      << "\n\n";
            continue;
        }
        if (containsAny(low, {"cara pakai", "gimana pakai", "tutorial"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("cara_pakai"), "ketik hash") << RESET
                      << "\n\n";
            continue;
        }
        if (containsAny(low, {"fitur", "bisa apa"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("fitur"), "analisa hash") << RESET
                      << "\n\n";
            continue;
        }
        if (containsAny(low, {"makasih", "terima kasih", "thanks", "thx", "tq"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("terima_kasih"), "siap") << RESET
                      << "\n\n";
            continue;
        }
        if (containsAny(low, {"halo", "hai", "hi", "hello", "hei", "hey", "woi", "woy"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("salam"), "halo") << RESET
                      << "\n\n";
            continue;
        }
        if (containsAny(low, {"aku", "saya"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("aku"), "aku siap bantu") << RESET
                      << "\n\n";
            continue;
        }
        if (containsAny(low, {"kamu", "anda", "sampean"})) {
            std::cout << "\n  " << GREEN
                      << pickRandom(otakChatReplies("kamu"), "kamu tinggal ketik") << RESET
                      << "\n\n";
            continue;
        }

        if (isHashLike(in)) {
            aiAnalisa(in);
            continue;
        }

        std::cout << "\n  " << GRAY
                  << pickRandom(otakChatReplies("unknown"),
                                "gue gak ngerti. ketik 'help'") << RESET
                  << "\n\n";
    }
}
