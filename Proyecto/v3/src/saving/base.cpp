#ifndef BASE_CPP
#define BASE_CPP

#include "../custom.cpp"
#include "../structs.cpp"
#include <fstream>

static const string default_file = "datos.bin";

void write_string(fstream &file, const string &str) {        // n
  size_t n = str.length();                                   // n
  file.write(reinterpret_cast<const char *>(&n), sizeof(n)); // n
  file.write(str.data(), n);                                 // n
} // n es el marcador / cantidad de bytes para leer/escribir.
// alternativas fueron: length, size, bytes, long; es decir, palabras ya
// reservadas y mas confusas que n. Unicamente por eso se comite este crimen de
// nombre corto.

string read_string(fstream &file) {
  string str;
  size_t n = 0;
  file.read(reinterpret_cast<char *>(&n), sizeof(n));
  file.read(str.data(), n);
  return str;
}

#endif
