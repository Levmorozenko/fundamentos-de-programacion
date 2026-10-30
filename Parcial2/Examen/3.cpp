// Escribe una función OrdenarDosNumeros que reciba dos enteros por referencia
// (o por puntero) y los intercambie si el primero es mayor que el segundo, de
// manera que al regresar de la función siempre queden en orden ascendente.
// Pruébala con al menos 3 pares de números distintos.

#include <iostream>
#include <regex>
#include <string>
using namespace std;

namespace external { // todo lo que fue importado desde otras practicas
static void clear_terminal() { system("cls"); };
static const wregex name_regex(L"^[\\x20-\\x3E\\x40-\\x7E\\xC0-\\xFF]+$");
static const wregex digit_regex(L"[0-9]+");
static const wregex float_regex(L"\\d+(\\.\\d+)?");

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
    if (!winput.empty())
      winput = trim(winput);
    valid = regex_match(winput, regex) && winput.length() > 0;
    if (!valid)
      cout << error_msg << endl;
  } while (!valid);
  cout << "\n";
  string input(winput.length(), 0);
  transform(winput.begin(), winput.end(), input.begin(),
            [](wchar_t c) { return (char)c; });

  return input;
}
} // namespace external

void OrdenarDosNumeros(int &a, int &b) {
  if (a > b) {
    int tmp = b;
    b = a;
    a = tmp;
  }
}

int main() {
  int a = stoi(external::get_regexed_input(
      "Entra el valor Numero uno: ", external::digit_regex,
      "El valor tiene que ser numerico sin signos o decimales."));
  int b = stoi(external::get_regexed_input(
      "Entra el valor Numero dos: ", external::digit_regex,
      "El valor tiene que ser numerico sin signos o decimales."));

  cout << "Estado actual - Numero uno es " << a << " y el Numero dos es " << b
       << endl;
  OrdenarDosNumeros(a, b);
  cout << "Estado ordenado - Numero uno es " << a << " y el Numero dos es " << b
       << endl;
}
