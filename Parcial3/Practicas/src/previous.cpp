#include <iostream>
#include <regex>
#include <string>

using namespace std;

#define fr(i, b) for (int i = 0; i < b; i++)

static void clear_terminal() { system("cls"); };

static const string thick_separator =
    "================================================\n";
static const string thin_separator =
    "------------------------------------------------\n";

static const wregex name_regex(L"^[\\x20-\\x3E\\x40-\\x7E\\xC0-\\xFF]+$");
static const wregex digit_regex(L"[0-9]+");
static const wregex float_regex(L"\\d+(\\.\\d+)?");

wstring trim(wstring str) { // reutilizado
  auto start = str.find_first_not_of(L" ");
  auto end = str.find_last_not_of(L" ");
  str = str.substr(start, end - start + 1);
  return str;
}

string get_regexed_input(const char *msg, wregex regex, const char *error_msg) {
  wstring winput;
  bool valid;

  do {
    cout << msg << endl;
    getline(wcin, winput);
    if (!winput.empty()) {
      winput = trim(winput);
    }
    valid = regex_match(winput, regex) && winput.length() > 0;

    if (!valid) {
      cout << error_msg << endl;
    }
  } while (!valid);
  cout << "\n";

  // convercion de wstring a string de https://stackoverflow.com/a/12097772
  string input(winput.length(), 0);
  transform(winput.begin(), winput.end(), input.begin(),
            [](wchar_t c) { return (char)c; });

  return input;
}

void await_enter() { // reutilizado y reformateado
  cout << "Presiona enter para continuar...";
  getchar();
}
