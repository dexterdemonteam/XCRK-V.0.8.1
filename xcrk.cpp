#define OPENSSL_SUPPRESS_DEPRECATED

#include "xcrk.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <cctype>
#include <limits>
#include <openssl/evp.h>

std::atomic<bool>         g_found{false};
std::atomic<bool>         g_stop{false};
std::atomic<unsigned long long> g_counter{0};
std::atomic<size_t>       g_nextIdx{0};
std::string               g_result;
std::chrono::steady_clock::time_point g_startTime;

static std::mutex g_resultMtx;

static std::string toHex(const unsigned char* d, size_t n) {
    static const char* h = "0123456789abcdef";
    std::string s; s.reserve(n * 2);
    for (size_t i = 0; i < n; ++i) {
        s += h[(d[i] >> 4) & 0xF];
        s += h[d[i] & 0xF];
    }
    return s;
}

std::string hashString(const std::string& in, const std::string& algo) {
    const EVP_MD* md = EVP_get_digestbyname(algo.c_str());
    if (!md) return "";
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int  dlen = 0;
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, md, nullptr);
    EVP_DigestUpdate(ctx, in.data(), in.size());
    EVP_DigestFinal_ex(ctx, digest, &dlen);
    EVP_MD_CTX_free(ctx);
    return toHex(digest, dlen);
}

std::string formatNumber(unsigned long long n) {
    std::string s = std::to_string(n);
    std::string out;
    int cnt = 0;
    for (int i = (int)s.size() - 1; i >= 0; --i) {
        out.push_back(s[i]);
        if (++cnt % 3 == 0 && i != 0) out.push_back('.');
    }
    std::reverse(out.begin(), out.end());
    return out;
}

void resetGlobals() {
    g_found.store(false);
    g_stop.store(false);
    g_counter.store(0);
    g_nextIdx.store(0);
    g_result.clear();
    g_startTime = std::chrono::steady_clock::now();
}

bool showDisclaimer() {
    std::cout << "  " << RED << BOLD << "DISCLAIMER" << RESET << "\n\n";
    std::cout << GREEN << "  Hanya untuk:" << RESET << "\n";
    std::cout << GRAY   << "    · " << RESET << "edukasi & pembelajaran\n";
    std::cout << GRAY   << "    · " << RESET << "CTF / lab pribadi\n";
    std::cout << GRAY   << "    · " << RESET << "authorized pentest\n\n";
    std::cout << RED << "  Dilarang keras untuk:" << RESET << "\n";
    std::cout << GRAY << "    · " << RESET << "menyerang sistem tanpa izin\n";
    std::cout << GRAY << "    · " << RESET << "aktivitas ilegal\n\n";
    std::cout << GREEN << "  Segala penyalahgunaan = tanggung jawab user." << RESET << "\n\n";

    std::cout << "  " << GRAY << "setuju? " << RESET << GREEN << "(y/n)" << RESET
              << GRAY << " › " << RESET;
    std::string in; std::getline(std::cin, in);
    std::transform(in.begin(), in.end(), in.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return (in == "y" || in == "yes");
}

void printFooter() {
    std::cout << "\n  " << DRED << "xcrk v0.8.1" << RESET
              << GRAY << " · " << RESET
              << DRED << "dexter demon team" << RESET << "\n\n";
}

struct BruteConfig {
    std::string targetHash;
    std::string algo;
    std::string charset;
    int minLen  = 1;
    int maxLen  = 4;
    int threads = 4;
};

static void bruteRecurse(const BruteConfig& cfg, std::string& cur) {
    if (g_found.load(std::memory_order_relaxed)) return;

    if ((int)cur.size() >= cfg.minLen) {
        g_counter.fetch_add(1, std::memory_order_relaxed);
        if (hashString(cur, cfg.algo) == cfg.targetHash) {
            std::lock_guard<std::mutex> lk(g_resultMtx);
            if (!g_found.exchange(true)) g_result = cur;
            return;
        }
    }
    if ((int)cur.size() >= cfg.maxLen) return;

    for (char c : cfg.charset) {
        cur.push_back(c);
        bruteRecurse(cfg, cur);
        cur.pop_back();
        if (g_found.load(std::memory_order_relaxed)) return;
    }
}

static void bruteWorker(const BruteConfig& cfg) {
    while (!g_found.load(std::memory_order_relaxed)) {
        size_t i = g_nextIdx.fetch_add(1, std::memory_order_relaxed);
        if (i >= cfg.charset.size()) return;
        std::string cur;
        cur.push_back(cfg.charset[i]);
        bruteRecurse(cfg, cur);
    }
}

static void progressLoop(const char* label) {
    const char spin[] = "|/-\\";
    int idx = 0;
    while (!g_found.load() && !g_stop.load()) {
        auto now = std::chrono::steady_clock::now();
        double el = std::chrono::duration<double>(now - g_startTime).count();
        unsigned long long cnt = g_counter.load();
        double rate = el > 0 ? (double)cnt / el : 0;

        std::cout << "\r  " << RED << spin[idx++ % 4] << RESET
                  << "  " << GRAY << label << RESET
                  << "  " << GREEN << std::setw(14) << std::left
                  << formatNumber(cnt) << RESET
                  << "  " << GRAY << "rate" << RESET << " " << GREEN
                  << std::setw(11) << std::left
                  << (formatNumber((unsigned long long)rate) + " H/s") << RESET
                  << "  " << GRAY << "time" << RESET << " " << GREEN
                  << std::fixed << std::setprecision(1)
                  << std::setw(6) << el << "s" << RESET
                  << "   " << std::flush;

        std::this_thread::sleep_for(std::chrono::milliseconds(120));
    }
    std::cout << "\r" << std::string(100, ' ') << "\r";
}

static bool detectAlgo(const std::string& hash, std::string& algo) {
    size_t hl = hash.size();
    if      (hl == 32) algo = "MD5";
    else if (hl == 40) algo = "SHA1";
    else if (hl == 64) algo = "SHA256";
    else return false;
    for (char c : hash) if (!std::isxdigit((unsigned char)c)) return false;
    return true;
}

static std::string inputHash(std::string& outAlgo) {
    std::cout << "  " << RED << "target hash" << RESET << "\n";
    std::cout << "  " << GRAY << "› " << RESET;
    std::string h; std::getline(std::cin, h);
    auto notSpace = [](unsigned char ch){ return !std::isspace(ch); };
    h.erase(h.begin(), std::find_if(h.begin(), h.end(), notSpace));
    h.erase(std::find_if(h.rbegin(), h.rend(), notSpace).base(), h.end());
    std::transform(h.begin(), h.end(), h.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    if (!detectAlgo(h, outAlgo)) {
        std::cout << "  " << RED << "hash tidak valid (32/40/64 hex)." << RESET << "\n";
        return "";
    }
    std::cout << "  " << GRAY << "detected › " << RESET
              << GREEN << outAlgo << RESET << "\n\n";
    return h;
}

void runBruteForce() {
    resetGlobals();
    BruteConfig cfg;
    cfg.targetHash = inputHash(cfg.algo);
    if (cfg.targetHash.empty()) return;

    std::cout << "  " << RED << "charset" << RESET << "\n";
    std::cout << GREEN << "    [1]" << RESET << " a-z              " << GRAY << "26\n" << RESET;
    std::cout << GREEN << "    [2]" << RESET << " a-z + 0-9        " << GRAY << "36\n" << RESET;
    std::cout << GREEN << "    [3]" << RESET << " A-Za-z + 0-9     " << GRAY << "62\n" << RESET;
    std::cout << GREEN << "    [4]" << RESET << " printable ascii  " << GRAY << "95\n" << RESET;
    std::cout << GREEN << "    [5]" << RESET << " custom\n\n";
    std::cout << "  " << GRAY << "pilih › " << RESET;
    int c; if (!(std::cin >> c)) { std::cin.clear(); c = 1; }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    const std::string lc = "abcdefghijklmnopqrstuvwxyz";
    const std::string uc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string dg = "0123456789";
    switch (c) {
        case 1: cfg.charset = lc; break;
        case 2: cfg.charset = lc + dg; break;
        case 3: cfg.charset = lc + uc + dg; break;
        case 4: {
            std::string s;
            for (char ch = 32; ch < 127; ++ch) s += ch;
            cfg.charset = s; break;
        }
        case 5: {
            std::cout << "  " << GRAY << "charset › " << RESET;
            std::string s; std::getline(std::cin, s);
            cfg.charset = s.empty() ? lc : s; break;
        }
        default: cfg.charset = lc;
    }
    if (cfg.charset.empty()) { std::cout << "  " << RED << "charset kosong." << RESET << "\n"; return; }

    std::cout << "\n  " << RED << "length range" << RESET << "\n";
    std::cout << "  " << GRAY << "min › " << RESET; std::cin >> cfg.minLen;
    std::cout << "  " << GRAY << "max › " << RESET; std::cin >> cfg.maxLen;
    if (cfg.minLen < 1) cfg.minLen = 1;
    if (cfg.maxLen < cfg.minLen) cfg.maxLen = cfg.minLen;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cfg.threads = (int)std::thread::hardware_concurrency();
    if (cfg.threads < 1) cfg.threads = 4;
    if (cfg.threads > 64) cfg.threads = 64;

    std::cout << "\n  " << RED << "summary" << RESET << "\n";
    std::cout << "  " << GRAY << "algo      " << RESET << GREEN << cfg.algo << RESET << "\n";
    std::cout << "  " << GRAY << "charset   " << RESET << cfg.charset.size() << " chars\n";
    std::cout << "  " << GRAY << "length    " << RESET << cfg.minLen << " - " << cfg.maxLen << "\n";
    std::cout << "  " << GRAY << "threads   " << RESET << cfg.threads << "\n";
    std::cout << "\n  " << GRAY << "tekan enter untuk mulai..." << RESET;
    std::cin.get();

    std::cout << "\n  " << RED << "brute force" << RESET << "\n\n";
    g_startTime = std::chrono::steady_clock::now();
    std::thread prog(progressLoop, "brute");

    std::vector<std::thread> pool;
    for (int i = 0; i < cfg.threads; ++i) pool.emplace_back(bruteWorker, std::cref(cfg));
    for (auto& t : pool) t.join();

    g_stop = true; prog.join();

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
        std::cout << "  " << GRAY << "rate      " << RESET
                  << formatNumber((unsigned long long)(total / (el > 0 ? el : 1e-9)))
                  << " H/s\n";
    } else {
        std::cout << "  " << RED << BOLD << "not found" << RESET << "\n\n";
        std::cout << "  " << GRAY
                  << "coba perbesar max length / tambah charset.\n" << RESET;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    printBanner();

    if (!showDisclaimer()) {
        std::cout << "\n  " << RED << "dibatalkan." << RESET << "\n";
        return 1;
    }

    showMainMenu();
    printFooter();
    return 0;
}
