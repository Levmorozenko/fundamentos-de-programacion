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
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using namespace std;
// Meet the FoR macro family
#define fr(i, b) for (int i = 0; i < b; i++) // short FoR -> FR
#define fro(i, a) for (auto i : a)           // FoR Object -> FRO
#define fror(i, a) for (const auto &i : a)   // FoR Object by Reference -> FROR
#define thick_separator "================================================\n"
#define thin_separator "------------------------------------------------\n"

static void clear_terminal() { system("cls"); };

float promedio(const float x[], const int size) {
  float suma = 0.0;
  fr(i, size) suma += x[i];
  return round(suma / static_cast<float>(size) * 10.0f) / 10.0f;
}

// If It Works, Don't Touch It
static const regex name_regex("^[\\x20-\\x3E\\x40-\\x7E\\xC0-\\xFF]+$");
static const regex filename_regex(R"(^[^<>:"/\\|?*\x00-\x1F]+$)");
static const regex digit_regex("^[0-9]{1,9}$");
static const regex float_regex("^(?=.{1,9}$)\\d+(\\.\\d+)?$");
static const regex confirm_regex("^[sSyYnN]$");

string trim(string str) {
  auto start = str.find_first_not_of(" ");
  auto end = str.find_last_not_of(" ");
  if (start == string::npos)
    return "";
  str = str.substr(start, end - start + 1);
  return str;
}

string get_regexed_input(const char *msg, regex regex, const char *error_msg) {
  string input;
  bool valid = false;

  do {
    cout << msg << endl;
    getline(cin, input);
    if (!input.empty()) {
      try {
        input = trim(input);
        valid = regex_match(input, regex) && input.length() > 0;
      } catch (...) {
        valid = false;
      }
    }

    if (!valid) {
      cout << error_msg << endl;
    }
  } while (!valid);
  cout << "\n";

  return input;
}

void await_enter() {
  cout << "Presiona enter para continuar...";
  string null_str;
  getline(cin, null_str);
}

#endif
