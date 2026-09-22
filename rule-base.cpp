#include "xcrk.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <limits>
#include <chrono>

static std::vector<std::string> g_wordlistR;
static std::atomic<size_t>      g_wordIdxR{0};
static std::mutex               g_ruleMtx;

static bool detectAlgoLocal(const std::string& hash, std::string& algo) {
    size_t hl = hash.size();
    if      (hl == 32) algo = "MD5";
    else if (hl == 40) algo = "SHA1";
    else if (hl == 64) algo = "SHA256";
    else return false;
    for (char c : hash) if (!std::isxdigit((unsigned char)c)) return false;
    return true;
}

static std::string toLower(const std::string& s) {
    std::string r = s;
    for (auto& c : r) c = std::tolower((unsigned char)c);
    return r;
}
static std::string toUpper(const std::string& s) {
    std::string r = s;
    for (auto& c : r) c = std::toupper((unsigned char)c);
    return r;
}
static std::string capitalize(const std::string& s) {
    std::string r = toLower(s);
    if (!r.empty()) r[0] = std::toupper((unsigned char)r[0]);
    return r;
}
static std::string leet(const std::string& s) {
    std::string r = s;
    for (auto& c : r) {
        switch (std::tolower((unsigned char)c)) {
            case 'a': c = '4'; break;
            case 'e': c = '3'; break;
            case 'i': c = '1'; break;
            case 'o': c = '0'; break;
            case 's': c = '5'; break;
            case 't': c = '7'; break;
            case 'b': c = '8'; break;
            case 'g': c = '9'; break;
        }
    }
    return r;
}
static std::string reverse(const std::string& s) {
    std::string r = s;
    std::reverse(r.begin(), r.end());
    return r;
}

static void applyRules(const std::string& w, std::vector<std::string>& out) {
    out.clear();
    const std::string lw  = toLower(w);
    const std::string uw  = toUpper(w);
    const std::string cap = capitalize(w);

    out.push_back(w);
    out.push_back(lw);
    out.push_back(uw);
    out.push_back(cap);
    out.push_back(leet(lw));
    out.push_back(leet(cap));
    out.push_back(reverse(lw));

    for (int d = 0; d <= 9; ++d)
        out.push_back(lw + std::to_string(d));
    for (int d = 0; d <= 9; ++d)
        out.push_back(cap + std::to_string(d));

    static const char* sufs[] = {
        "!", "!!", "!!!", ".", "@", "#",
        "1!", "123", "1234", "12345",
        "2023", "2024", "2025", "2026",
        "_", "-", "@123", "!@#"
    };
    for (auto s : sufs) {
        out.push_back(lw + s);
        out.push_back(cap + s);
    }

    std::string ll = leet(lw);
    for (int d = 0; d <= 9; ++d)
        out.push_back(ll + std::to_string(d));
    for (int d = 0; d <= 9; ++d)
        out.push_back(std::to_string(d) + lw);
}

static void progressLoopRules() {
    const char spin[] = "|/-\\";
    int idx = 0;
    while (!g_found.load() && !g_stop.load()) {
        auto now = std::chrono::steady_clock::now();
        double el = std::chrono::duration<double>(now - g_startTime).count();
        unsigned long long cnt = g_counter.load();
        size_t cur = g_wordIdxR.load();
        size_t tot = g_wordlistR.size();
        int pct = tot ? (int)(100.0 * cur / tot) : 0;

        std::cout << "\r  " << RED << spin[idx++ % 4] << RESET
                  << "  " << GRAY << "word" << RESET << " "
                  << GREEN << std::setw(8) << std::left
                  << (std::to_string(cur) + "/" + std::to_string(tot)) << RESET
                  << " " << GRAY << "(" << pct << "%)" << RESET
                  << "  " << GRAY << "tried" << RESET << " "
                  << GREEN << std::setw(12) << std::left << formatNumber(cnt) << RESET
                  << "  " << GRAY << "time" << RESET << " "
                  << GREEN << std::fixed << std::setprecision(1)
                  << std::setw(6) << el << "s" << RESET
                  << "   " << std::flush;

        std::this_thread::sleep_for(std::chrono::milliseconds(120));
    }
    std::cout << "\r" << std::string(120, ' ') << "\r";
}

static void ruleWorker(const std::string& algo, const std::string& target) {
    std::vector<std::string> cands;
    cands.reserve(128);
    while (!g_found.load(std::memory_order_relaxed)) {
        size_t i = g_wordIdxR.fetch_add(1, std::memory_order_relaxed);
        if (i >= g_wordlistR.size()) return;
        applyRules(g_wordlistR[i], cands);
        for (const auto& cand : cands) {
            if (g_found.load(std::memory_order_relaxed)) return;
            g_counter.fetch_add(1, std::memory_order_relaxed);
            if (hashString(cand, algo) == target) {
                std::lock_guard<std::mutex> lk(g_ruleMtx);
                if (!g_found.exchange(true)) g_result = cand;
                return;
            }
        }
    }
}

void runRuleBased() {
    resetGlobals();
    g_wordlistR.clear();
    g_wordIdxR.store(0);

    std::cout << "  " << RED << "rule-based cracking" << RESET << "\n\n";
    std::cout << "  " << GRAY
              << "aturan: case / leet / digit / suffix / reverse" << RESET
              << "\n\n";

    std::cout << "  " << RED << "target hash" << RESET << "\n";
    std::cout << "  " << GRAY << "› " << RESET;
    std::string hash; std::getline(std::cin, hash);

    auto notSpace = [](unsigned char ch){ return !std::isspace(ch); };
    hash.erase(hash.begin(), std::find_if(hash.begin(), hash.end(), notSpace));
    hash.erase(std::find_if(hash.rbegin(), hash.rend(), notSpace).base(), hash.end());
    std::transform(hash.begin(), hash.end(), hash.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    std::string algo;
    if (!detectAlgoLocal(hash, algo)) {
        std::cout << "  " << RED << "hash tidak valid." << RESET << "\n";
        return;
    }
    std::cout << "  " << GRAY << "detected › " << RESET
              << GREEN << algo << RESET << "\n\n";

    std::cout << "  " << RED << "wordlist" << RESET << "\n";
    std::cout << "  " << GRAY << "path › " << RESET;
    std::string path; std::getline(std::cin, path);
    if (path.empty()) {
        std::cout << "  " << RED << "path kosong." << RESET << "\n";
        return;
    }

    std::ifstream f(path);
    if (!f.is_open()) {
        std::cout << "  " << RED << "file tidak bisa dibuka: " << path << RESET << "\n";
        return;
    }

    std::string line;
    while (std::getline(f, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (!line.empty()) g_wordlistR.push_back(line);
    }
    f.close();

    if (g_wordlistR.empty()) {
        std::cout << "  " << RED << "wordlist kosong." << RESET << "\n";
        return;
    }

    std::cout << "  " << GRAY << "loaded › " << RESET
              << GREEN << formatNumber(g_wordlistR.size()) << RESET
              << GRAY << " words" << RESET << "\n";

    int threads = (int)std::thread::hardware_concurrency();
    if (threads < 1) threads = 4;
    if (threads > 64) threads = 64;

    std::cout << "  " << GRAY << "threads › " << RESET
              << GREEN << threads << RESET << "\n";
    std::cout << "\n  " << GRAY << "tekan enter untuk mulai..." << RESET;
    std::cin.get();

    std::cout << "\n  " << RED << "running" << RESET << "\n\n";
    g_startTime = std::chrono::steady_clock::now();
    std::thread prog(progressLoopRules);

    std::vector<std::thread> pool;
    for (int i = 0; i < threads; ++i)
        pool.emplace_back(ruleWorker, std::cref(algo), std::cref(hash));
    for (auto& t : pool) t.join();

    g_stop = true;
    prog.join();

    std::cout << "\n";
    if (g_found.load()) {
        auto end = std::chrono::steady_clock::now();
        double el = std::chrono::duration<double>(end - g_startTime).count();
        auto total = g_counter.load();
        std::cout << "  " << GREEN << BOLD << "cracked" << RESET << "\n\n";
        std::cout << "  " << GRAY << "password  " << RESET
                  << GREEN << BOLD << g_result << RESET << "\n";
        std::cout << "  " << GRAY << "attempts  " << RESET << formatNumber(total) << "\n";
        std::cout << "  " << GRAY << "time      " << RESET
                  << std::fixed << std::setprecision(3) << el << "s\n";
    } else {
        std::cout << "  " << RED << BOLD << "not found" << RESET << "\n\n";
        std::cout << "  " << GRAY
                  << "coba wordlist lain atau tambah rule manual." << RESET << "\n";
    }
}
