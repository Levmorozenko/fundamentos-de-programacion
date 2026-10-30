// Define un struct Producto con los campos nombre, precio y cantidad en
// existencia. Crea un arreglo de 5 productos, captura sus datos, y muestra el
// nombre del producto con mayor valor total en inventario (precio × cantidad).

#include <iostream>
#include <regex>
#include <string>
#include <vector>
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

struct Producto {
  string nombre = "!!!!";
  float precio = 0;
  int cantidad = 0;
};

Producto registrar_producto() {
  Producto producto;
  cout << "================================================\n";
  producto.nombre = external::get_regexed_input(
      "Entra el nombre del producto: ", external::name_regex,
      "El nombre no debe contener caracteres invalidos.");
  producto.precio = stof(external::get_regexed_input(
      "Entra el precio del producto: ", external::float_regex,
      "El precio solo puede contener cifras y decimales."));
  producto.cantidad = stoi(external::get_regexed_input(
      "Entra la cantidad del producto disponible: ", external::digit_regex,
      "La cantidad es numerica y entera pa que entras otra "
      "cosa."));
  return producto;
}

int main() {
  vector<Producto> menu;
  external::clear_terminal();
  for (int i = 0; i < 5; i++)
    menu.push_back(registrar_producto());

  // y muestra el nombre del producto con mayor valor total en inventario
  // (precio × cantidad).

  // Checamos que producto tiene el mayor valor
  vector<int> mayores_valores;
  float cached_product_value = 0;

  for (int i = 0; i < 5; i++) {
    float huh = menu[i].precio * static_cast<float>(menu[i].cantidad);

    if (huh > cached_product_value) {
      mayores_valores = {i};
      cached_product_value = huh;
    } else if (huh == cached_product_value) {
      mayores_valores.push_back(i);
    }
  }

  // Imprimimos y cubrimos todos posibles casos de algun error mitico.
  if (mayores_valores.size() == 0) {
    cout
        << "Por alguna razon ningun producto tiene mayor valor que otro.\n"; // unreachable
  } else if (mayores_valores.size() == 1) {
    cout << "El producto con mayor valor total en inventario es "
         << menu[mayores_valores[0]].nombre << " con el valor de "
         << cached_product_value << endl;
  } else {
    cout << "Los productos con mayor valor en inventario son: ";
    for (int i : mayores_valores) {
      cout << menu[i].nombre << ", ";
    }
    cout << "con el valor de " << cached_product_value << endl;
  }
}
