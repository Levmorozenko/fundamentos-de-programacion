#ifndef CUSTOM_CPP
#define CUSTOM_CPP

// repara acentos en el terminal de windows.
#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
static void set_utf8() {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8); // cout
  SetConsoleCP(CP_UTF8);       // getline
#endif
}

#include "faker-cxx/faker.h"
#include <cstdlib>
#include <iostream>
#include <regex>
#include <string>

using namespace std;
// Meet the FoR macro family
#define fr(i, b) for (int i = 0; i < b; i++) // short FoR -> FR
#define fro(i, a) for (auto i : a)           // FoR Object -> FRO
#define fror(i, a) for (const auto &i : a)   // FoR Object by Reference -> FROR
#define thick_separator "================================================"
#define thin_separator "------------------------------------------------"

static void clear_terminal() { system("cls"); };

float promedio(float x[], int size) {
  float suma = 0.0;
  fr(i, size) suma += x[i];
  return round(suma / static_cast<float>(size) * 10.0f) / 10.0f;
}

int random_raw_number() { // reutilizado
  random_device rd;
  return abs(static_cast<int>(rd()));
}

// If It Works, Don't Touch It
static const wregex name_regex(L"^[\\x20-\\x3E\\x40-\\x7E\\xC0-\\xFF]+$");
static const wregex digit_regex(L"^[0-9]{1,9}$");
static const wregex float_regex(L"^(?=.{1,9}$)\\d+(\\.\\d+)?$");

wstring trim(wstring str) {
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
      try {
        winput = trim(winput);
        valid = regex_match(winput, regex) && winput.length() > 0;
      } catch (...) {
        valid = false;
      }
    }

    if (!valid) {
      cout << error_msg << endl;
    }
  } while (!valid);
  cout << "\n";

  string input(winput.length(), 0);
  transform(winput.begin(), winput.end(), input.begin(),
            [](wchar_t c) { return (char)c; });

  return input;
}

void await_enter() {
  cout << "Presiona enter para continuar...";
  getchar();
}

#endif
