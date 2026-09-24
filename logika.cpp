#include "xcrk.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

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

const std::vector<HashEntry>& otakGetHashes();
const std::vector<std::string>& otakGetTips();
bool otakIsLoaded();

static std::string analisaAlgo(const std::string& hash) {
    size_t hl = hash.size();
    if (hl == 32) return "MD5";
    if (hl == 40) return "SHA1";
    if (hl == 64) return "SHA256";
    if (hl == 128) return "SHA512";
    return "UNKNOWN";
}

static bool isHex(const std::string& s) {
    for (char c : s)
        if (!std::isxdigit((unsigned char)c)) return false;
    return true;
}

static bool cariDiDataset(const std::string& hash, std::string& outPassword,
                          std::string& outAlgo, std::string& outKategori) {
    const auto& list = otakGetHashes();
    for (const auto& e : list) {
        if (e.hash == hash) {
            outPassword = e.password;
            outAlgo     = e.algo;
            outKategori = e.kategori;
            return true;
        }
    }
    return false;
}

static std::string saranMetode(const std::string& hash, const std::string& algo) {
    size_t hl = hash.size();
    if (hl == 32 || hl == 40 || hl == 64) {
        return "coba [2] dataset dulu, kalau gak nemu pakai [3] rule-based";
    }
    if (hl == 128) {
        return "hash panjang (SHA512), brute force gak realistis, pakai wordlist gede";
    }
    return "algo gak dikenali, cek hash-nya";
}

static std::string klasifikasiPassword(const std::string& pw) {
    bool adaAngka = false, adaHuruf = false, adaSimbol = false;
    for (char c : pw) {
        if (std::isdigit((unsigned char)c)) adaAngka = true;
        else if (std::isalpha((unsigned char)c)) adaHuruf = true;
        else adaSimbol = true;
    }
    if (adaAngka && !adaHuruf && !adaSimbol) return "angka";
    if (adaHuruf && !adaAngka && !adaSimbol) return "huruf";
    if (adaHuruf && adaAngka) return "campuran";
    if (adaSimbol) return "kompleks";
    return "unknown";
}

Analisis logikaAnalisis(const std::string& hash) {
    Analisis a;
    std::string h = hash;
    std::transform(h.begin(), h.end(), h.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    a.algo = analisaAlgo(h);
    a.valid = isHex(h) && a.algo != "UNKNOWN";
    a.foundDiDataset = false;
    a.saran = saranMetode(h, a.algo);

    std::string pw, algo, kat;
    if (cariDiDataset(h, pw, algo, kat)) {
        a.foundDiDataset = true;
        a.password = pw;
        a.kategori = kat;
        a.tipe = klasifikasiPassword(pw);
    }

    return a;
}
