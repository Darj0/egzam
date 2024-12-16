#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <regex>
#include <vector>
#include <cctype>

using namespace std;

void  zodziu_gaudimas(string input1);
void  URL_paieska(string input2);
void  URL_ekranas(string input2);
string cleanWord(const string& word);

int main()
{
    int pasirinkimas, pas;
    string input1 = "C:/Users/baran/Documents/egzam/input1.txt";
    string input2 = "C:/Users/baran/Documents/egzam/input2.txt";

    cout << "Norite pamatyti pasikartojancius zodzius (spauskite 1), ar visus URL (spauskite 2)?\n";
    cin >> pasirinkimas;
    while (pasirinkimas != 1 && pasirinkimas != 2) {
    cout << "Klaidingas ivedimas, bandykite dar karta (Iveskite 1 arba 2): ";
    cin >> pasirinkimas;
    }
      if (pasirinkimas == 1)
  {
      zodziu_gaudimas(input1);
  }
  else
  {
      cout <<"Norite matyti rezultata ekrane (spauskite 1), ar isvesti i faila (spauskite 2)?\n";
      cin >> pas;
      while (pas != 1 && pas != 2) {
      cout << "Klaidingas ivedimas, bandykite dar karta (Iveskite 1 arba 2): ";
      cin >> pas;}
      if (pas == 2)
  {
      URL_paieska(input2);
  }
  else
  {
      URL_ekranas(input2);
  }
  }
    return 0;
}
//-------------------------------------
void zodziu_gaudimas(string input1) {
    ifstream file(input1);
    if (!file.is_open()) {
        cerr << "Nepavyko atidaryti failo: " << input1 << endl;
        return;
    }

    map<string, vector<int>> eil;
    map<string, int> z_count;
    string line, word;
    int eilutes_numeris = 0;

    while (getline(file, line)) {
        eilutes_numeris++;
        istringstream iss(line);
        while (iss >> word) {
            string cleaned = cleanWord(word);
            if (!cleaned.empty()) {
                eil[cleaned].push_back(eilutes_numeris);
                z_count[cleaned]++;
            }
        }
    }

    if (file.bad()) {
        cerr << "Klaida nuskaitant faila: " << input1 << endl;
    }
    file.close();

    ofstream countOutput("zodziai.txt");
    if (!countOutput.is_open()) {
        cerr << "Nepavyko sukurti zodziai.txt." << endl;
        return;
    }

    countOutput << "Zodziai ir ju pasikartojimu skaicius:\n";
    for (const auto& [key, count] : z_count) {
        if (count > 1) {
            countOutput << key << ": " << count << "\n";
        }
    }
    countOutput.close();


    ofstream refOutput("cross_reference.txt");
    if (!refOutput.is_open()) {
        cerr << "Nepavyko sukurti cross_reference.txt." << endl;
        return;
    }

    refOutput << "Cross-Reference lentele:\n";
    for (const auto& [key, lines] : eil) {
        if (lines.size() > 1) {
            refOutput << key << " (rasta " << lines.size() << " kartus) eilutese: ";
            for (size_t i = 0; i < lines.size(); ++i) {
                refOutput << lines[i];
                if (i != lines.size() - 1) refOutput << ", ";
            }
            refOutput << "\n";
        }
    }
    refOutput.close();

    cout << "Sukurtas 'zodziait.txt'.\n";
    cout << "Cross-Reference lentele irasyta i 'cross_reference.txt'.\n";
}

//-----------------------------------------
string cleanWord(const string& word) {
    string cleaned;
    for (char c : word) {
        if (isalnum(c) || c == '-') {
            cleaned += tolower(c);
        }
    }
    return cleaned;
}
//-----------------------------------------
void  URL_paieska(string input2)
{
     ifstream file(input2);
    if (!file.is_open()) {
        cerr << "Nepavyko atidaryti failo: " << input2 << endl;
        return;
    }

    vector<string> urls;
    string line;
    regex urlRegex(R"((https?://[^\s]+|www\.[^\s]+|\b\w+\.\w+\b))");
    smatch match;

    while (getline(file, line)) {
        string::const_iterator searchStart(line.cbegin());
        while (regex_search(searchStart, line.cend(), match, urlRegex)) {
            urls.push_back(match[0]);
            searchStart = match.suffix().first;
        }
    }

    if (file.bad()) {
        cerr << "Klaida nuskaitant faila: " << input2 << endl;
    }
    file.close();

    ofstream output("url_rezultatai.txt");
    if (!output.is_open()) {
        cerr << "Nepavyko sukurti rezultato failo." << endl;
        return;
    }

    output << "Rasti URL adresai:\n";
    for (const string& url : urls) {
        output << url << "\n";
    }

    cout << "Rezultatai irasyti i 'url_rezultatai.txt'.\n";
}

//--------------------------------------------
void  URL_ekranas(string input2)
{
    ifstream file(input2);
    if (!file.is_open()) {
        cerr << "Nepavyko atidaryti failo: " << input2 << endl;
        return;
    }
     vector<string> urls;
    string line;
    regex urlRegex(R"((https?://[^\s]+|www\.[^\s]+|\b\w+\.\w+\b))");
    smatch match;

    while (getline(file, line)) {
        string::const_iterator searchStart(line.cbegin());
        while (regex_search(searchStart, line.cend(), match, urlRegex)) {
            urls.push_back(match[0]);
            searchStart = match.suffix().first;
        }
    }

    if (file.bad()) {
        cerr << "Klaida nuskaitant faila: " << input2 << endl;
    }
    file.close();



    cout << "Rasti URL adresai:\n";
    for (const string& url : urls) {
        cout << url << "\n";
    }


}
