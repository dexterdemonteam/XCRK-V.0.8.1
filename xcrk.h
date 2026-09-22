#pragma once

#include <string>
#include <atomic>
#include <chrono>
#include <cstddef>
#include <vector>

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define GRAY    "\033[0;90m"
#define DRED    "\033[0;31m"

extern std::atomic<bool>         g_found;
extern std::atomic<bool>         g_stop;
extern std::atomic<unsigned long long> g_counter;
extern std::atomic<size_t>       g_nextIdx;
extern std::string               g_result;
extern std::chrono::steady_clock::time_point g_startTime;

std::string hashString(const std::string& in, const std::string& algo);
std::string formatNumber(unsigned long long n);
void        resetGlobals();

void printBanner();
bool showDisclaimer();
void printFooter();
void printOwnerInfo();

void showMainMenu();

void runBruteForce();
void runDatasetCracking();
void runRuleBased();
void runAIChat();
