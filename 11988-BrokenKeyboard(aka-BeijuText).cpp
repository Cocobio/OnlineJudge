/*

Problem: https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=3139

Ignacio Osorio
Cocobio2

Sentencia de autoría: Indicando si el código entregado ha sido generado personalmente, con asistencia o tomado de alguna otra fuente (foros, páginas web, etc). En caso de que el código no haya sido generado personalmente, se deberán consignar la(s) persona(s) que asistieron en la elaboración del código y/o la referencia de dónde fue obtenido.
Análisis asintótico de la solución: Se deberá consignar el costo (en notación O) del tiempo y espacio requeridos por la solución (para el peor caso) y se deberá justificar este tiempo.

*/
#include <iostream>
#include <list>
#include <string>

using namespace std;

int main() {
	string input_line;
	list<char> input_text;
	string beiju_output;

	list<char>::iterator text_position = input_text.begin();

	char home_button = '[';
	char end_button = ']';

	while (getline(cin, input_line)) {
		for (auto it=input_line.begin(); it!=input_line.end(); it++) {
			if (*it == home_button)
				text_position = input_text.begin();
			else if (*it == end_button)
				text_position = input_text.end();
			else
				input_text.insert(text_position, *it);
		}

		beiju_output = string(input_text.begin(), input_text.end());
		cout << beiju_output << endl;

		input_text.clear();
	}

	return 0;
}