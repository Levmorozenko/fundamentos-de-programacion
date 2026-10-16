// El compilador podria hacer esto automaticamente, pero no, tengo que meter
// header guards manualmente, porque no le gustó que tiene dos declaraciones que
// vienen del mismo archivo.
#ifndef CUSTOM_CPP
#define CUSTOM_CPP

#include <cstdlib>
#include <iostream>
#include <random>
#include <regex>
#include <string>

using namespace std;
// descubrimiento del define para extender mini-ifs con mini-fors
#define fr(i, b) for (int i = 0; i < b; i++)

namespace custom {
int random_raw_number() { // reutilizado
  random_device rd;
  return abs(static_cast<int>(rd()));
}

// reutilizado y reformateado {
float promedio(float x[], int size) {
  float suma = 0.0;
  fr(i, size) suma += x[i];
  return round(suma / static_cast<float>(size) * 10.0f) / 10.0f;
}

// Desafortunadamente esta linea remueve portabilidad a linux.
static void clear_terminal() { system("cls"); };

static const string thick_separator =
    "================================================";
static const string thin_separator =
    "------------------------------------------------";
// } // reutilizado y reformateado

// std::regex no soporta Unicode por determinado, itera sobre un
// string en bytes. El std::string tiene la encodificacion de UTF-8 (mas
// informacion despues).
//
// Porque no permitir todo el UTF-8?
// - Porque entonces no verificaría nada.
// - Odio emojis asi que son PROHIBIDOS en los nombres, a pesar de ser UTF-8
// valido. ASCII emoticons son permitidos.
// - Ya llegué demasiado lejos con esta investigacion, no puedo abandonarlo.
// - Porque no usar /^[a-zA-Záéíóú]+&/ ? Porque João y Thérèse
// quedarian fuera del rango, y ambos son nombres completamente legales en
// texto latin. Debido a eso y otros casos posibles, se usan rangos de UTF-8 en
// hexadecimal.
//
// Rango de caracteres imprimibles ASCII (UTF-8 Basic Latin) es 32-126 o
// 0x20-0x7E en hex.
//
// Ademas ocupamos seccion minima de UTF-8 que cubre acentos del idioma español;
// pero tambien quiero cubrir el caso de portugues, frances, etc.
// Afortunadamente la subseccion Latin 1 Supplement cumple esa funcion Segun
// https://www.w3schools.com/charsets/ref_utf_latin1_supplement.asp El rango de
// letras es 192-255 o 0xC0-0xFF en hex.
//
// Los rangos van dentro de [] y se agrega ^ y & como ancores de incicio y fin
// del string respectivamente.
//
// Asi mismo la expresion de regex deberia ser: /^[\x20-\x7E\xC0-\xFF]+$/,
// verdad? Pensé que si, pero luego metí el caracter "ɠ" y lo pasó por correcto.
// Eso me enfadó y organizé una investigacion extensa contra este bug. Resulta
// que no es solo culpa del regex. std::stdin acepta toda entrada como UTF-8,
// pero UTF-8 puede ocupar de 1 a 4 bytes, dependiendo del caracter.
//
// Solucion 1:
// Podemos validar que la cadena del texto es conformada por characteres de
// exactamente 1 byte? Segun la tabla en
// https://en.wikipedia.org/wiki/UTF-8#Description podemos ver que todos los
// caracteres posibles de un bit tienen el rango de 0x00 a 0x7F. Pero el maximo
// del Latin-1 es 0xFF, por lo que tenemos que usar... 2 bytes.
// De hecho, todo el punto de ASCII es que cada caracter sea exactamente 1 byte.
// Debido a que no podemos guardar acentos en ASCII, mi primera solucion fue
// invalida.
//
// Solucion 2:
// Adaptar todo el programa a usar std::wstring en vez de std::string. Es un
// problema ya que todo el programa tendrá que ser modificado (ej. cout ->
// wcout). Ademas introducerá problemas posibles con otras bibliotecas.
// Sin embargo, nada nos para de obtener entrada como wstring, verificar contra
// regex y luego transformarlo en string, para su uso en otros lugares. Con
// wregex podemos validar el texto con iteracion sobre code points en vez de
// bytes. Esta solucion es la mas elegante que personalmente he encontrado.
//
// -----------------------------------------------------------------------------
//
// Problema 2: el caracter malvado ɠ todavia se puede pasar. De lo que descubrí,
// wchar_t, de cual depende wregex, wstring, etcetera, depende del locale de
// windows.
//
// Solucion 1:
// No usar regex. Regex itera sobre cada caracter y checa si esta dentro del
// rango. Hemos encontrado los rangos necesarios, ahora lo podemos hacer
// manualmente. Esta solucion no funcionó porque el problema no fue en la
// verificacion. El problema es en encodificacion de wcin. Mi enum con
// implementacion manual fue inutil.
//
// Extension de problema 2: Tras agregar:
// for (wchar_t c : winput) { wcout << hex << (int)c << L" ";} // funcion de IA
// Se descubre que el ɠ tiene valor de 0x3F, el simbolo "?" de ASCII. En algun
// momento del procesamiento se pierde el valor y es convertido al fallback de
// "?". Asi mismo:
//
// Solucion 2:
// Banear simbolo "?" a traves de excluirlo del rango.
// 0x20-0x7E -> 0x20-0x3E 0x40-0x7E
//
// Solucion 3:
// Dar toda la vuelta y regresar al std::cin y leer los bytes manualmente,
// convertirlos a utf-8 y luego checarlo a traves de wregex.
//
// Entre las soluciones 2 y 3, elijo la 2. Durante este experimento gigante
// aprendi mucho de c++ y repase muchos conceptos como encodificacion de letras.
// Ademas, finalmente gané al ɠ malvado.
//
// Los siguientes regexes son funcionales:
static const wregex name_regex(L"^[\\x20-\\x3E\\x40-\\x7E\\xC0-\\xFF]+$");
static const wregex digit_regex(L"[0-9]+");
static const wregex float_regex(L"\\d+(\\.\\d+)?");

// Nota sobre const y static:
//		`static` means that object is initialized
// 		`const` is a promise you won't try to modify a value

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

} // namespace custom

#endif
