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
int random_raw_number() {
  random_device rd;
  return abs(static_cast<int>(rd()));
}

float promedio(float x[], int size) {
  float suma = 0.0;
  fr(i, size) suma += x[i];
  return suma / static_cast<float>(size);
}

// Desafortunadamente esta linea remueve portabilidad a linux.
static void clear_terminal() { system("cls"); };

static const string thick_separator =
    "================================================";
static const string thin_separator =
    "------------------------------------------------";

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
// que no es solo culpa del regex. El discurso se continua en la funcion
// get_regexed_input.
static const wregex name_regex(L"^[\x20-\x7E\xC0-\xFF]+$");

// Nota sobre const y static segun
// https://stackoverflow.com/questions/2216239/what-is-the-difference-between-a-static-and-const-variable
// 		`const` is a promise you won't try to modify a value
//		`static` means that object is initialized

static const wregex digit_regex(L"[0-9]+");

// regex no es facil de escribir, mil gracias a https://regex101.com
// recordatorio de usar \\ cada vez que se necesita entrar un \, especialmente
// en paths y regexes.
static const wregex float_regex(L"\\d+(\\.\\d+)?");

wstring trim(wstring str) { return str; }

// Continuacion del regex:
// std::stdin acepta toda entrada como UTF-8, pero UTF-8 puede
// ocupar de 1 a 4 bytes, dependiendo del caracter y sistema operativo.
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
// Sin embargo, nada nos para de obtener entrada como wstring y transformarlo en
// string para uso en todos los demas lugares. Asi mismo podemos validar el
// texto con iteracion sobre code points en vez de bytes. Esta solucion es la
// mas elegante que personalmente he encontrado.

string get_regexed_input(const char *msg, wregex regex, const char *error_msg) {
  wstring input;
  bool valid;
  do {
    cout << msg << endl;
    getline(wcin, input);
    input = trim(input);
    valid = regex_match(input, regex);

    if (!valid) {
      cout << error_msg << endl;
    }
  } while (!valid);
  cout << "\n";

  // convercion de wstring a string de https://stackoverflow.com/a/12097772
  string processed_input(input.length(), 0);
  transform(input.begin(), input.end(), processed_input.begin(),
            [](wchar_t c) { return (char)c; });

  return processed_input;
}

void await_enter() {
  cout << "Presiona enter para continuar...";
  getchar();
}

} // namespace custom

#endif
