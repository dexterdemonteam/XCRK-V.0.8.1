#include "xcrk.h"
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>

struct HashEntry {
    std::string hash;
    std::string algo;
    std::string password;
    std::string kategori;
};

struct Otak {
    std::vector<HashEntry> hashes;
    std::vector<std::string> tips;
    std::vector<std::pair<std::string, std::string>> pola;
    std::map<std::string, std::vector<std::string>> chat;
    bool loaded = false;
};

static Otak g_brain;

static std::string trim(const std::string& s) {
    auto notSpace = [](unsigned char ch){ return !std::isspace(ch); };
    auto b = std::find_if(s.begin(), s.end(), notSpace);
    auto e = std::find_if(s.rbegin(), s.rend(), notSpace).base();
    if (b >= e) return "";
    return std::string(b, e);
}

static std::string extractValue(const std::string& line, const std::string& key) {
    std::string search = "\"" + key + "\"";
    size_t pos = line.find(search);
    if (pos == std::string::npos) return "";
    pos = line.find(':', pos);
    if (pos == std::string::npos) return "";
    pos++;
    while (pos < line.size() && std::isspace((unsigned char)line[pos])) pos++;
    if (pos >= line.size() || line[pos] != '"') return "";
    pos++;
    size_t end = pos;
    while (end < line.size()) {
        if (line[end] == '\\') { end += 2; continue; }
        if (line[end] == '"') break;
        end++;
    }
    if (end >= line.size()) return "";
    return line.substr(pos, end - pos);
}

bool otakLoad(const std::string& path) {
    std::ifstream f(path);
    if (!f.is_open()) return false;

    g_brain.hashes.clear();
    g_brain.tips.clear();
    g_brain.pola.clear();
    g_brain.chat.clear();

    std::string line;
    std::string mode;
    std::string currentChatKey;

    while (std::getline(f, line)) {
        std::string t = trim(line);
        if (t.empty()) continue;

        if (t.find("\"hashes\"") != std::string::npos) { mode = "hash"; continue; }
        if (t.find("\"pola\"")   != std::string::npos) { mode = "pola"; continue; }
        if (t.find("\"tips\"")   != std::string::npos) { mode = "tips"; continue; }
        if (t.find("\"chat\"")   != std::string::npos) { mode = "chat"; continue; }

        if (mode == "hash" && t.find('{') != std::string::npos) {
            HashEntry e;
            e.hash     = extractValue(t, "hash");
            e.algo     = extractValue(t, "algo");
            e.password = extractValue(t, "password");
            e.kategori = extractValue(t, "kategori");
            if (!e.hash.empty()) {
                std::transform(e.hash.begin(), e.hash.end(), e.hash.begin(),
                               [](unsigned char c){ return std::tolower(c); });
                g_brain.hashes.push_back(e);
            }
        }
        else if (mode == "pola" && t.find('{') != std::string::npos) {
            std::string kata  = extractValue(t, "kata");
            std::string saran = extractValue(t, "saran");
            if (!kata.empty()) g_brain.pola.push_back({kata, saran});
        }
        else if (mode == "tips" && t.find('"') != std::string::npos) {
            size_t p1 = t.find('"');
            size_t p2 = t.find('"', p1 + 1);
            if (p2 != std::string::npos) {
                std::string s = t.substr(p1 + 1, p2 - p1 - 1);
                if (!s.empty() && s != "tips") g_brain.tips.push_back(s);
            }
        }
        else if (mode == "chat") {
            if (t.find('"') != std::string::npos &&
                t.find(':') != std::string::npos &&
                t.find('[') != std::string::npos) {
                size_t p1 = t.find('"');
                size_t p2 = t.find('"', p1 + 1);
                if (p2 != std::string::npos) {
                    currentChatKey = t.substr(p1 + 1, p2 - p1 - 1);
                    if (g_brain.chat.find(currentChatKey) == g_brain.chat.end())
                        g_brain.chat[currentChatKey] = {};
                }
            }
            else if (!currentChatKey.empty() && t.find('"') != std::string::npos) {
                size_t p1 = t.find('"');
                size_t p2 = t.find('"', p1 + 1);
                if (p2 != std::string::npos) {
                    std::string s = t.substr(p1 + 1, p2 - p1 - 1);
                    if (!s.empty() && s != currentChatKey && s != "chat")
                        g_brain.chat[currentChatKey].push_back(s);
                }
            }
        }
    }

    g_brain.loaded = true;
    return true;
}

const std::vector<HashEntry>& otakGetHashes() { return g_brain.hashes; }
const std::vector<std::string>& otakGetTips() { return g_brain.tips; }
bool otakIsLoaded() { return g_brain.loaded; }

const std::vector<std::string>& otakChatReplies(const std::string& key) {
    static const std::vector<std::string> empty;
    auto it = g_brain.chat.find(key);
    if (it == g_brain.chat.end()) return empty;
    return it->second;
}
