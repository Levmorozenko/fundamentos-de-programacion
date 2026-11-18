#include <string>
using namespace std;

void setup_console();
void clear_screen();
int read_int(const string &prompt, int min = 0, int max = 2147483647);
float read_float(const string &prompt);
string read_string(const string &prompt);
