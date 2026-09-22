
# 🩸 XCRK — Hash Cracking Toolkit

```

⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣦⣤⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣶⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⣶⣿⣦⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⣠⣄⠀⠀⠀⠀⠀⠀⠀⠀⠹⢿⣿⣿⣿⣿⣿⣷⣤⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣾⣿⣿⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⢾⣿⣿⣿⣶⣦⡀⠀⠀⠀⠀⠀⠀⠉⠙⠿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣰⣾⣿⣿⣿⠿⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣠⡀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠈⢿⣿⣿⣿⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠈⠹⢿⣿⣿⣿⣿⣿⣦⣄⡀⣀⢀⣤⣴⣾⣿⣿⣿⣿⠏⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⣿⣿⣿⡗⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠈⠙⠿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠉⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⣾⣿⣿⡿⠋⠁⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⢿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢘⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⣸⣿⣿⠿⠿⠻⠟⠛⠛⠛⠛⠿⠿⠿⠿⣿⢿⡿⠃⠀⠀⠀⠀⠀⠀⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣿⣿⣿⣿⣦⣄⣠⣴⣾⣿⣿⣃⣀⣄⣠⡀⠀⠀⠀⠀⣀⣴⣀⣠⢇⣞⣶⣤⣀⣀⠀⣀⣀⣴⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠿⠿⠟⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡧⠂⠄⢺⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠟⠛⠛⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⡁⢈⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠄⠀⢺⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡀⣀⣀⣤⣤⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⠂⠀⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⡀⣀⢀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠸⣿⣷⣦⡀⠀⠀⠀⢀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡧⡀⠄⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣤⠀⠀⠀⠀⠀⢠⣼⣷⢆
⠈⢿⣿⣿⣿⣦⣤⣴⣾⣿⣿⣿⡿⠿⠿⢿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡷⡁⠂⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠿⠿⠿⠿⢿⣿⣿⣿⣦⣄⣠⣾⣿⣿⡟⠊
⠀⠘⠿⣿⣿⣿⣿⣿⣿⣿⠿⠋⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡷⠁⠐⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠘⢻⣿⣿⣿⣿⣿⡟⠃⠀⠀
⠀⠀⠀⠈⠹⢿⣿⣿⣿⠋⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⠠⠀⢽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠿⠛⠃⠁⠀⠀⠀
⠀⠀⠀⠀⠀⠈⠉⠉⠁⠀⠀⠀⠀⢀⣠⣴⣶⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡗⠂⠈⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣤⣀⣠⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣏⠡⠐⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⡿⠟⠻⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣳⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢨⣿⣿⣿⡇⠀⠀⠀⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠛⠀⠀⢻⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⡇⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⢸⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⡷⠀⠀⠀⠀⠀⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠀⠀⠀⠀⠀⢸⣿⣿⣿⡃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠈⠙⠿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⢠⣴⣾⣿⣿⡿⠟⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣿⣿⣿⣿⣧⣤⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⡿⠏⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠿⣿⣿⣿⣶⡀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠾⠿⠿⠟⠡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⠿⣿⠗⠀⠀⠀⠀⠀

```

**XCRK** adalah tools hash cracking berbasis C++ dengan CLI modern.
Dibuat untuk edukasi keamanan siber, CTF, dan authorized penetration testing.

![Version](https://img.shields.io/badge/version-0.8.1-red)
![Platform](https://img.shields.io/badge/platform-linux%20%7C%20termux-green)
![Language](https://img.shields.io/badge/language-C%2B%2B17-blue)
![License](https://img.shields.io/badge/license-MIT-yellow)

---

## ⚡ Fitur

| # | Fitur | Deskripsi |
|---|---|---|
| 1 | Brute Force | Coba semua kombinasi charset (a-z, alnum, custom) |
| 2 | Dataset Cracking | Crack pakai wordlist (`words.txt`, `rockyou.txt`, dll) |
| 3 | Rule-Based | Mutasi kata: leet, kapital, digit, suffix, reverse |
| 4 | Hash AI Chatbot | AI offline yang analisa hash dari `dataset.json` |

Algoritma didukung: MD5 · SHA1 · SHA256
Auto-detect: panjang hash otomatis dikenali (32/40/64 hex)
Multithreading: pakai semua core CPU secara otomatis

---

## 🚀 Instalasi

### Termux (Android)

```bash
pkg update && pkg upgrade
pkg install clang openssl git
git clone https://github.com/dexterdemonteam/XCRK-V.0.8.1.git
cd XCRK-V.0.8.1
clang++ -O3 -std=c++17 -o xcrk \
  xcrk.cpp banner.cpp menu.cpp \
  dataset-cracking.cpp rule-base.cpp \
  ai.cpp logika.cpp otak.cpp \
  -lcrypto -pthread
cp xcrk $PREFIX/bin/
chmod +x $PREFIX/bin/xcrk
```

Linux (Debian/Ubuntu/Kali)

```bash
sudo apt install g++ libssl-dev git
git clone https://github.com/dexterdemonteam/XCRK-V.0.8.1.git
cd XCRK-V.0.8.1
g++ -O3 -std=c++17 -o xcrk \
  xcrk.cpp banner.cpp menu.cpp \
  dataset-cracking.cpp rule-base.cpp \
  ai.cpp logika.cpp otak.cpp \
  -lcrypto -pthread
sudo cp xcrk /usr/local/bin/
```

Windows (MSYS2)

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-openssl
g++ -O3 -std=c++17 -o xcrk.exe xcrk.cpp banner.cpp menu.cpp dataset-cracking.cpp rule-base.cpp ai.cpp logika.cpp otak.cpp -lcrypto -pthread
```

---

🎮 Cara Pakai

Jalankan xcrk, setujui disclaimer (y), lalu pilih menu:

```
menu

    [1] brute force       charset-based
    [2] dataset cracking  wordlist attack
    [3] rule-based        mutation attack
    [4] info owner
    [5] join channel
    [6] hash ai chatbot   offline ai
    [0] exit
```

Contoh — Dataset Cracking

```
pilih › 2

target hash
› 5f4dcc3b5aa765d61d8327deb882cf99
detected › MD5

wordlist
path › words.txt
loaded › 1.469 words

threads › 8
tekan enter untuk mulai...
```

Hasil:

```
cracked

password  password
attempts  8
time      0.001s
```

Contoh — Rule-Based

```
pilih › 3

target hash
› 0d107d09f5bbe40cade3de5c71e9e9b7
detected › MD5

wordlist
path › words.txt
loaded › 1.469 words
```

Rule-based akan otomatis nyoba:

· letmein, Letmein, LETMEIN
· letmein1 ... letmein9
· letmein!, letmein@, letmein123, letmein2024
· l3tm31n, L3tm31n

Contoh — Hash AI Chatbot

```
pilih › 6

  hash ai chatbot · offline · v1.0
  ketik 'help' buat bantuan, 'exit' buat keluar

  ai › 21232f297a57a5a743894a0e4a801fc3

  analyzing...

  input    21232f297a57a5a743894a0e4a801fc3
  algo     MD5
  status   ketemu di dataset!
  password admin
  kategori umum
  tipe     huruf
```

Command AI:

Command Fungsi
<hash> Analisa hash (cari di dataset + kasih saran)
help Bantuan
tips Tips dari dataset
dataset Info dataset
clear Bersihin layar
exit Keluar

---

📂 Struktur Project

```
XCRK-V.0.8.1/
├── xcrk.h                 # shared header
├── xcrk.cpp               # main + brute force
├── banner.cpp             # banner ASCII
├── menu.cpp               # menu + owner + channel
├── dataset-cracking.cpp   # wordlist attack
├── rule-base.cpp          # rule-based mutation
├── ai.cpp                 # hash AI chatbot
├── logika.cpp             # AI logic
├── otak.cpp               # AI brain (dataset loader)
├── dataset.json           # database hash untuk AI
├── words.txt              # wordlist
└── README.md
```

---

🧪 Test Cepat

```bash
echo -n "hello" | md5sum
# 5d41402abc4b2a76b9719d911017c592

xcrk
# pilih [2] dataset cracking
# hash: 5d41402abc4b2a76b9719d911017c592
# path: words.txt
```

Hash umum untuk latihan:

Password Hash MD5
hello 5d41402abc4b2a76b9719d911017c592
admin 21232f297a57a5a743894a0e4a801fc3
admin123 0192023a7bbd73250516f069df18b500
123456 e10adc3949ba59abbe56e057f20f883e
qwerty d8578edf8458ce06fbc5bb76a58c5ca4
password 5f4dcc3b5aa765d61d8327deb882cf99

---

🧬 Arsitektur Multi-File

· xcrk.cpp — entry point + brute force core
· banner.cpp — tampilan ASCII art + branding
· menu.cpp — menu navigasi + info owner + channel
· dataset-cracking.cpp — wordlist engine
· rule-base.cpp — mutation engine
· otak.cpp — loader dataset.json (untuk AI)
· logika.cpp — analisa hash + klasifikasi
· ai.cpp — interface chatbot

Semua modul terhubung lewat xcrk.h.

---

⚠️ DISCLAIMER

BACA SEBELUM PAKAI

XCRK dibuat HANYA untuk:

· Edukasi & pembelajaran keamanan siber
· Capture The Flag (CTF)
· Personal security research di sistem milik sendiri
· Authorized penetration testing dengan izin tertulis
· Bug bounty dalam scope yang ditentukan

DILARANG KERAS menggunakan XCRK untuk:

· Menyerang sistem, jaringan, atau akun tanpa izin
· Crack password/hash tanpa otorisasi
· Aktivitas ilegal / melanggar hukum (UU ITE, CFAA, dll)
· Merugikan pihak lain
· Distribusi sebagai bagian dari malware

🚫 Dexter Demon Team TIDAK BERTANGGUNG JAWAB

Dexter Demon Team dan Yongky (owner) secara tegas menyatakan:

TIDAK BERTANGGUNG JAWAB atas segala bentuk penyalahgunaan tools XCRK,
termasuk namun tidak terbatas pada:

· Kerusakan sistem, data, atau perangkat
· Kerugian finansial atau materiil
· Tuntutan hukum, denda, atau proses pidana
· Pelanggaran privasi atau data pribadi
· Pelanggaran hukum lokal, nasional, maupun internasional
· Segala konsekuensi langsung maupun tidak langsung

Semua risiko ditanggung SEPENUHNYA oleh user.
Semua tindakan adalah tanggung jawab PRIBADI user.
Semua akibat hukum adalah tanggung jawab MUTLAK user.

Dexter Demon Team hanya menyediakan tools untuk tujuan edukasi.
Jika tools ini disalahgunakan, itu 100% di luar tanggung jawab kami.

⚖️ Hukum yang Berlaku

Negara Undang-Undang Sanksi
Indonesia UU ITE Pasal 30, 32, 46 6–12 tahun penjara
USA CFAA (18 U.S.C. § 1030) Hingga 20 tahun
UK Computer Misuse Act 1990 Hingga 10 tahun
EU Directive 2013/40/EU Bervariasi
Singapore Computer Misuse Act Hingga 10 tahun
Malaysia Computer Crimes Act 1997 Hingga 10 tahun

✅ Persetujuan User

Dengan menggunakan XCRK, kamu menyatakan:

· Sudah membaca & memahami disclaimer ini
· Akan menggunakan XCRK hanya untuk tujuan legal & etis
· Bertanggung jawab penuh atas semua tindakanmu
· Membebaskan Dexter Demon Team dari segala tuntutan
· Tidak akan menyalahgunakan tools ini

Jika tidak setuju → JANGAN gunakan XCRK.

🩸 Penutup

Dexter Demon Team hadir untuk edukasi, bukan untuk merusak.
Kami tidak mentoleransi penyalahgunaan dalam bentuk apapun.
Gunakan ilmu ini dengan bijak. 🩸

— Dexter Demon Team

---

👤 Owner & Tim

Dexter Demon Team

· Owner: Yongky
· Team: Dexter Demon Team
· Channel: https://whatsapp.com/channel/0029Vb8R7mh4tRrz7K4vBm23
· GitHub: https://github.com/dexterdemonteam/XCRK-V.0.8.1

Update tools, fitur baru, dan info lain ada di channel.

---

🤝 Kontribusi

Pull request & issue terbuka. Tapi ingat:

1. Jangan hapus disclaimer
2. Jangan tambahkan fitur yang melanggar etika
3. Sertakan credit ke Dexter Demon Team

---

📜 License

MIT License © 2026 Yongky — Dexter Demon Team

Bebas pakai, edit, distribusi, dengan syarat tetap menyertakan credit.

---

🩸 Credits

Dibuat dengan 🩸 oleh Dexter Demon Team

Stay sharp. Stay ethical. Stay curious.

```
