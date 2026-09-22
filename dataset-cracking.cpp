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

static std::vector<std::string> g_wordlist;
static std::atomic<size_t>      g_wordIdx{0};
static std::mutex               g_wordMtx;

static bool detectAlgoLocal(const std::string& hash, std::string& algo) {
    size_t hl = hash.size();
    if      (hl == 32) algo = "MD5";
    else if (hl == 40) algo = "SHA1";
    else if (hl == 64) algo = "SHA256";
    else return false;
    for (char c : hash) if (!std::isxdigit((unsigned char)c)) return false;
    return true;
}

static void progressLoopWords() {
    const char spin[] = "|/-\\";
    int idx = 0;
    while (!g_found.load() && !g_stop.load()) {
        auto now = std::chrono::steady_clock::now();
        double el = std::chrono::duration<double>(now - g_startTime).count();
        unsigned long long cnt = g_counter.load();
        double rate = el > 0 ? (double)cnt / el : 0;
        size_t cur = g_wordIdx.load();
        size_t tot = g_wordlist.size();
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

static void wordlistWorker(const std::string& algo, const std::string& target) {
    while (!g_found.load(std::memory_order_relaxed)) {
        size_t i = g_wordIdx.fetch_add(1, std::memory_order_relaxed);
        if (i >= g_wordlist.size()) return;
        const std::string& w = g_wordlist[i];
        g_counter.fetch_add(1, std::memory_order_relaxed);
        if (hashString(w, algo) == target) {
            std::lock_guard<std::mutex> lk(g_wordMtx);
            if (!g_found.exchange(true)) g_result = w;
            return;
        }
    }
}

void runDatasetCracking() {
    resetGlobals();
    g_wordlist.clear();
    g_wordIdx.store(0);

    std::cout << "  " << RED << "dataset cracking" << RESET << "\n\n";

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
        if (!line.empty()) g_wordlist.push_back(line);
    }
    f.close();

    if (g_wordlist.empty()) {
        std::cout << "  " << RED << "wordlist kosong." << RESET << "\n";
        return;
    }

    std::cout << "  " << GRAY << "loaded › " << RESET
              << GREEN << formatNumber(g_wordlist.size()) << RESET
              << GRAY << " words" << RESET << "\n\n";

    int threads = (int)std::thread::hardware_concurrency();
    if (threads < 1) threads = 4;
    if (threads > 64) threads = 64;

    std::cout << "  " << GRAY << "threads › " << RESET
              << GREEN << threads << RESET << "\n";
    std::cout << "\n  " << GRAY << "tekan enter untuk mulai..." << RESET;
    std::cin.get();

    std::cout << "\n  " << RED << "running" << RESET << "\n\n";
    g_startTime = std::chrono::steady_clock::now();
    std::thread prog(progressLoopWords);

    std::vector<std::thread> pool;
    for (int i = 0; i < threads; ++i)
        pool.emplace_back(wordlistWorker, std::cref(algo), std::cref(hash));
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
        std::cout << "  " << GRAY << "password tidak ada di wordlist." << RESET << "\n";
    }
}
