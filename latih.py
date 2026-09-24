#!/usr/bin/env python3
import os

R  = "\033[0m"
B  = "\033[1m"
DR = "\033[1;31m"
DG = "\033[1;32m"
DM = "\033[1;35m"
GY = "\033[0;90m"

WORDS = "words.txt"

KATA_BARU = [
    # === frasa pribadi + spasi & tanpa spasi ===
    "aku ganteng", "akuganteng", "akuganteng123", "akugantengbanget",
    "aku cantik", "akucantik", "akucantik123", "akucantikbanget",
    "aku pintar", "akupintar", "akupintar123",
    "aku hebat", "akuhebat", "akuhebat123",
    "aku keren", "akukeren", "akukeren123",
    "aku jago", "akujago", "akujago123",
    "aku bagus", "akubagus", "akubaik", "akusoleh",
    "aku imut", "akuimut", "akulucu", "akuasik",
    "aku setia", "akusetia", "akujujur", "akuberani",
    "aku bijak", "akubijak", "akusabar", "akurajin",
    "aku disiplin", "akudisiplin", "akukreatif", "akuproduktif",
    "aku kuat", "akukuat", "aku tangguh", "akutangguh",
    "aku bahagia", "akubahagia", "aku sedih", "akusedih",
    "aku bahagia", "akubahagia", "aku senang", "akusenang",

    # === frasa pujian orang lain ===
    "kamu ganteng", "kamuganteng", "kamuganteng123",
    "kamu cantik", "kamucantik", "kamucantik123",
    "kamu pintar", "kamupintar", "kamupintar123",
    "kamu hebat", "kamuhebat", "kamuhebat123",
    "kamu keren", "kamukeren", "kamukeren123",
    "kamu jago", "kamujago", "kamujago123",
    "kamu baik", "kamubaik", "kamu soleh", "kamusoleh",
    "kamu imut", "kamuimut", "kamu lucu", "kamulucu",
    "kamu hebat sekali", "kamuluarbiasa", "kamuterbaik",
    "doi ganteng", "doiaganteng", "doiacantik",
    "dia baik", "diabaik", "dia keren", "diakeren",

    # === frasa kita ===
    "kita bisa", "kitabisa", "kitakeren", "kitahebat",
    "kitakerja keras", "kitakerjakeras",
    "kita pasti bisa", "kitapastibisa",
    "ayo kita bisa", "ayokitabisa",
    "ayo semangat", "ayosemangat",
    "jangan menyerah", "janganmenyerah",
    "terus semangat", "terussemangat",
    "pantang menyerah", "pantangmenyerah",
    "hidup jokowi", "hidupjokowi",
    "hidup indonesia", "hidupindonesia",
    "hidup merdeka", "hidupmerdeka",
    "merdeka selamanya", "merdekaselamanya",
    "indonesia raya", "indonesiaraya",
    "nusantara jaya", "nusantarajaya",

    # === panggilan umum ===
    "bro", "broo", "bruh", "sis", "cuy", "cui", "gan", "agan",
    "suhu", "juragan", "bos", "boss", "om", "tante",
    "kakak", "ade", "adik", "bang", "dang", "wang",
    "pak", "bu", "mbak", "mas", "dik", "dek",

    # === singkatan chat ===
    "otw", "brb", "afk", "gtg", "ttyl", "idk", "imo",
    "lol", "lmao", "rofl", "omg", "wtf", "wth",
    "fyi", "asap", "diy", "asl", "btw", "tbh",
    "nvm", "rn", "ftw", "kekw", "kek", "gg", "wp", "ez",
    "gr8", "b4", "2day", "2moro", "2night", "4u", "4me",

    # === hacker vibe ===
    "anonymous", "anonim", "darkweb", "darknet", "deepweb",
    "blackhat", "whitehat", "greyhat", "redhat", "bluehat",
    "cyberpunk", "cyberforce", "cyberarmy", "cyberteam",
    "zeroday", "bugbounty", "pentestlab", "hackthebox",
    "tryhackme", "htbplayer", "thmplayer", "ctfplayer",
    "kaliarmy", "kalilinux", "parrotos", "blackarch",
    "metasploit", "burpsuite", "wireshark", "nmapscan",
    "sqlmap", "nikto", "hydra", "johnripper", "hashcat",
    "aircrack", "reaver", "ettercap", "bettercap",
    "exploitdb", "packetstorm", "shodan", "censys",

    # === teknis ===
    "hashcrack", "passwordcrack", "bruteforce", "wordlist",
    "dictionary", "rainbowtable", "md5crack", "sha1crack",
    "sha256crack", "bcrypt", "scrypt", "argon2",
    "aes256", "rsa2048", "ecc", "base64", "hexencode",
    "urlencode", "rot13", "caesar", "vigenere",
    "xor", "xorcode", "payload", "shellcode",
    "reverse_shell", "bind_shell", "backdoor", "rootkit",
    "keylog", "ransomware", "spyware", "adware", "trojan",

    # === cybersecurity ===
    "firewall", "antivirus", "idsips", "soc", "siem",
    "redteam", "blueteam", "purpleteam", "incidentresponse",
    "forensics", "malwareanalysis", "reverseengineering",
    "cryptography", "steganografi", "osint", "socialengineering",
    "phishing", "vishing", "smishing", "spearphishing",
    "ddos", "dos", "mitm", "sqlinjection", "xssattack",
    "csrf", "lfi", "rfi", "rce", "ssrf",
    "idor", "brokenauth", "sensitivedata", "xxe",

    # === motivasi ===
    "semangat pagi", "semangatpagi", "semangat siang", "semangatsiang",
    "semangat sore", "semangatsore", "semangat malam", "semangatmalam",
    "semangat terus", "semangatterus", "semangat bro", "semangatbro",
    "kamu harapan", "kamuharapan", "kamu istimewa", "kamuistimewa",
    "kamu mengagumkan", "kamumengagumkan",
    "kamu produktif", "kamuproduktif", "kamu konsisten", "kamukonsisten",
    "terus belajar", "terusbelajar", "terus berkembang", "terusberkembang",
    "terus maju", "terusmaju", "terus jalan", "terusjalan",
    "jangan berhenti", "janganberhenti", "jangan ragu", "janganragu",
    "jangan putus asa", "janganputusasa",
    "tetap semangat", "tetapsemangat", "tetap fokus", "tetapfokus",
    "tetap kuat", "tetapkuat", "tetap sabar", "tetapsabar",

    # === salam ===
    "assalamualaikum", "waalaikumsalam",
    "selamat pagi", "selamatpagi", "selamat siang", "selamatsiang",
    "selamat sore", "selamatsore", "selamat malam", "selamatmalam",
    "selamat jalan", "selamatjalan", "selamat istirahat", "selamatistirahat",
    "salam kenal", "salamkenal", "salam sejahtera", "salamsejahtera",
    "salam damai", "salamdamai", "salam hangat", "salamhangat",
    "terima kasih", "terimakasih", "sama sama", "samasama",
    "permisi", "maaf ya", "maafya",
    "mohon bantuan", "mohonbantuan", "mohon dibantu", "mohondibantu",
    "bisa bantu", "bisabantu", "tolong bantu", "tolongbantu",
    "minta tolong", "mintatolong", "minta bantuan", "mintabantuan",

    # === admin & role ===
    "adminxcrk", "adminteam", "admindemon", "adminsite",
    "moderator", "modxcrk", "moddemon", "modteam",
    "superadmin", "rootadmin", "sysadmin", "netadmin",
    "ownerxcrk", "ownerdemom", "ownerteam", "owneryongky",
    "founderxcrk", "founderdemon", "founderyongky",
    "developerxcrk", "devxcrk", "dexdemon",
    "staffteam", "memberteam", "guestuser", "normaluser",

    # === nama indo + pola ===
    "budi123", "andi123", "rudi123", "joko123", "agus123",
    "dedi123", "hendra123", "heri123", "irfan123",
    "siti123", "dewi123", "sari123", "rina123", "lina123",
    "maya123", "putri123", "wulan123", "fitri123", "indah123",
    "budi2024", "andi2024", "siti2024", "dewi2024",
    "budisantoso", "andiwijaya", "sitinurhaliza", "dewilestari",

    # === frasa lucu ===
    "aku ganteng banget", "akugantengbanget",
    "aku ganteng sekali", "akugantengsekali",
    "kamu ganteng banget", "kamugantengbanget",
    "kamu cantik sekali", "kamucantiksekali",
    "kamu hebat banget", "kamuhebatbanget",
    "kita keren banget", "kitakerenbanget",
    "hidupku indah", "hidupkuindah",
    "hidupku bahagia", "hidupkubahagia",
    "wkwkwk", "hahaha", "hehehe", "hihihi",
    "yayaya", "yoiyoi", "sipsip", "okeoke",
    "gasken", "gaskeun", "gasaja", "gasinaja",
    "ayokgas", "ayokjalan", "ayokmain", "ayokbelajar",

    # === password pattern + tahun ===
    "admin2025", "admin2026", "user2025", "user2026",
    "guest2025", "guest2026", "root2025", "root2026",
    "test2025", "test2026", "demo2025", "demo2026",
    "welcome2025", "welcome2026", "letmein2025", "letmein2026",
    "qwerty2025", "qwerty2026", "pass2025", "pass2026",
    "abc2025", "abc2026", "love2025", "love2026",
    "iloveyou2025", "iloveyou2026",
    "dexter2025", "dexter2026", "demon2025", "demon2026",
    "yongky2025", "yongky2026", "xcrk2025", "xcrk2026",
    "indonesia2025", "indonesia2026",
    "jakarta2025", "jakarta2026", "bali2025", "bali2026",

    # === hacker indo ===
    "hackerganteng", "hackercantik", "hackerkeren", "hackerhebat",
    "hackerindo", "hackerjawa", "hackersunda",
    "hackerminang", "hackerbugis", "hackerbatak", "hackeraceh",
    "cyberindo", "cyberjawa", "cybersunda", "cyberminang",
    "anonimindo", "anonimjawa", "anonimsunda", "anonimminang",
    "dexterjawa", "dextersunda", "dexterminang", "dexterbugis",
    "demonjawa", "demonsunda", "demonminang", "demonbugis",
    "yongkyjawa", "yongkysunda", "yongkyminang", "yongkybugis",
    "xcrkjawa", "xcrksunda", "xcrkminang", "xcrkbugis",

    # === angka + huruf ===
    "12345abc", "abc12345", "a1b2c3d4e5", "1a2b3c4d5e",
    "q1w2e3r4t5", "1q2w3e4r5t", "z1x2c3v4b5", "1z2x3c4v5b",
    "a1a2a3a4a5", "b1b2b3b4b5", "c1c2c3c4c5",
    "12ab34cd", "ab12cd34", "12cd34ab",
    "aa11bb22", "cc33dd44", "ee55ff66",
    "111222333", "444555666", "777888999",
    "000111222", "333444555", "666777888",

    # === tahun ===
    "1990", "1991", "1992", "1993", "1994", "1995",
    "1996", "1997", "1998", "1999", "2000",
    "2001", "2002", "2003", "2004", "2005",
    "2006", "2007", "2008", "2009", "2010",
    "2011", "2012", "2013", "2014", "2015",
    "2016", "2017", "2018", "2019", "2020",
    "2021", "2022", "2023", "2024", "2025", "2026",

    # === bulan ===
    "januari", "februari", "maret", "april",
    "mei", "juni", "juli", "agustus",
    "september", "oktober", "november", "desember",
    "january", "february", "march", "april",
    "may", "june", "july", "august",
    "october", "november", "december",

    # === hari ===
    "senin", "selasa", "rabu", "kamis", "jumat",
    "sabtu", "minggu", "ahad",
    "monday", "tuesday", "wednesday", "thursday",
    "friday", "saturday", "sunday",

    # === makanan viral ===
    "seblakviral", "cirengviral", "cilokviral", "batagorviral",
    "mieayamviral", "basoviral", "sotoviral", "rawonviral",
    "gado gado", "pecel lele", "nasi padang", "nasi uduk",
    "rendang asli", "sate ayam", "sate kambing", "soto betawi",
    "boba viral", "es kopi", "es teh", "es jeruk",
    "kopi susu", "kopi luwak", "teh tarik", "teh botol",
    "martabak manis", "martabak telor", "terang bulan",
    "pisang goreng", "ubi goreng", "singkong goreng",
    "tempe goreng", "tahu goreng", "bakwan goreng",

    # === brand lokal ===
    "indomie", "mie sedap", "sarimi", "popmie", "supermi",
    "tehbotol", "tehpucuk", "tehgelas", "tehsisri",
    "kopikap", "kapalapi", "abc kopi", "goodday",
    "taro", "chitato", "lays", "pringles",
    "beng beng", "choki choki", "oreo", "goodtime",
    "silverqueen", "cadbury", "kitkat", "ferrero",

    # === brand luar ===
    "cocacola", "pepsi", "sprite", "fanta", "milo",
    "kfc", "mcd", "burgerking", "pizzahut", "dominos",
    "starbucks", "coffee bean", "dunkin", "jco",
    "nike", "adidas", "puma", "reebok", "converse",
    "gucci", "prada", "versace", "chanel", "dior",
    "samsung", "apple", "xiaomi", "oppo", "vivo",
    "realme", "huawei", "asus", "acer", "lenovo",

    # === tempat wisata ===
    "monas", "borobudur", "prambanan", "bromo",
    "rinjani", "semeru", "merbabu", "merapi",
    "kawah ijo", "tumpak sewu", "labuan bajo",
    "raja ampat", "komodo", "tanah toraja",
    "ubud", "kuta bali", "sanur", "nusa dua",
    "gili", "gili trawangan", "menjangan",
    "danau toba", "danau sentani",

    # === tools ===
    "nmap", "netcat", "socat", "telnet",
    "ssh client", "putty", "winscp", "filezilla",
    "vmware", "virtualbox", "qemu", "docker",
    "tcpdump", "tshark", "ngrep",
    "burp", "zap", "postman", "insomnia",
    "vscode", "sublime", "vim", "nano", "emacs",
    "git", "github", "gitlab", "bitbucket",
    "docker hub", "docker compose", "kubernetes",

    # === pujian singkat ===
    "goodjob", "goodwork", "well done", "nice work",
    "keep going", "keep fighting", "keep strong",
    "stay positive", "stay focused", "stay safe",
    "be yourself", "be strong", "be kind",
    "dont give up", "never give up", "never surrender",
    "you can do it", "you are amazing", "you are great",

    # === quote ===
    "hidup adalah pilihan", "hidup adalah perjuangan",
    "belajar tanpa henti", "berpikir sebelum bertindak",
    "bersyukur setiap hari", "berdoa dan berusaha",
    "jangan lupa ibadah", "jangan lupa keluarga",
    "jangan lupa teman", "jangan lupa diri sendiri",

    # === warna ===
    "merah", "putih", "biru", "kuning", "hijau",
    "hitam", "abu abu", "emas", "perak", "perunggu",
    "tembaga", "ungu", "orange", "pink", "cyan",
    "magenta", "turquoise", "maroon", "navy", "olive",
    "merah muda", "biru muda", "hijau muda", "kuning muda",
    "merah tua", "biru tua", "hijau tua", "kuning tua",

    # === hewan ===
    "kucing", "anjing", "burung", "ayam", "sapi",
    "kambing", "kuda", "harimau", "singa", "macan",
    "buaya", "ular", "naga", "garuda", "elang",
    "rajawali", "merpati", "cicak", "tokek", "kadal",
    "kura kura", "penyu", "paus", "hiu", "dolfin",
    "gajah", "jerapah", "zebra", "kudanil", "badak",
    "monyet", "orangutan", "gorila", "simpanse", "babon",

    # === gaul ===
    "anjay", "anjir", "anjeng", "waduh", "wadidaw",
    "wow", "wah", "ih", "eh", "ah",
    "gabut", "baper", "mager", "gaje", "kepo",
    "julid", "bucin", "mokondo", "cogan",
    "cewek", "cowok", "cewek cantik", "cowok ganteng",
    "cogan keren", "cewek kece",

    # === dexter demon team spesifik ===
    "dexter demon", "dexterdemon", "dexterdemonteam",
    "dexter team", "dexterteam", "demonteam",
    "yongky dexter", "yongkydemon", "yongkyteam",
    "xcrk dexter", "xcrkdemon", "xcrkteam",
    "dexterdemon2024", "dexterdemon2025",
    "xcrk2024", "xcrk2025",
    "dexterdemonteam2024", "dexterdemonteam2025",
]


def banner():
    print(f"\n{DR}{B}  LATIH · tambah kata ke words.txt{R}")
    print(f"{DM}  Dexter Demon Team{R}\n")


def load_words(path):
    if not os.path.exists(path):
        return set()
    with open(path, "r", encoding="utf-8", errors="ignore") as f:
        return {line.strip() for line in f if line.strip()}


def save_words(path, words):
    with open(path, "w", encoding="utf-8") as f:
        for w in sorted(words):
            f.write(w + "\n")


def main():
    banner()
    print(f"{GY}[*] loading {WORDS}...{R}")

    existing = load_words(WORDS)
    print(f"{GY}[*] kata existing: {len(existing)}{R}")

    baru = [w for w in KATA_BARU if w not in existing]
    print(f"{DG}[*] kata baru    : {len(baru)}{R}")

    if not baru:
        print(f"{DG}[+] gak ada kata baru, semua udah ada.{R}\n")
        return

    combined = existing | set(KATA_BARU)
    save_words(WORDS, combined)

    print(f"{DG}[+] saved → {WORDS}{R}")
    print(f"{DG}[+] total   : {len(combined)} kata{R}")
    print(f"{GY}    size    : {os.path.getsize(WORDS)} bytes{R}\n")
    print(f"{DM}  done · Dexter Demon Team{R}\n")


if __name__ == "__main__":
    main()
