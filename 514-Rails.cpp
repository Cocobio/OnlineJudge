/*

Problem: https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=455

Ignacio Osorio
Cocobio2

Sentencia de autoría: Indicando si el código entregado ha sido generado personalmente, con asistencia o tomado de alguna otra fuente (foros, páginas web, etc). En caso de que el código no haya sido generado personalmente, se deberán consignar la(s) persona(s) que asistieron en la elaboración del código y/o la referencia de dónde fue obtenido.
Análisis asintótico de la solución: Se deberá consignar el costo (en notación O) del tiempo y espacio requeridos por la solución (para el peor caso) y se deberá justificar este tiempo.

*/
#include <iostream>
#include <vector>
#include <stack>
#include <deque>

using namespace std;

void trainChief(vector<short> &line_in, vector<short> &line_out, stack<short> &station, deque<short> &combination) {
	short coach_at_line_in = 0;

	for(auto it=combination.begin(); it!=combination.end(); it++) {
		if (coach_at_line_in<line_in.size() && *it == line_in[coach_at_line_in]) {
			line_out.push_back(line_in[coach_at_line_in++]);
		}
		else if (coach_at_line_in<line_in.size() && *it>line_in[coach_at_line_in]) {
			while(*it != line_in[coach_at_line_in]) {
				station.push(line_in[coach_at_line_in++]);
			}

			line_out.push_back(line_in[coach_at_line_in++]);
		}
		else {
			if (*it==station.top()) {
				line_out.push_back(station.top());
				station.pop();
			}
			else {
				// If the combination is not posible, chief will clean the station and return
				while (station.size()) station.pop();
				return;
			}
		}
	}
}

int main() {
	vector<short> line_a;
	vector<short> line_b;
	stack<short> poppush_city_station;

	deque<short> desired_combination;

	short N;
	short tmp;
	// crear linea A al momento de leer N y luego iterar sobre ella. De esta forma no la creo de manera inicesaria todas las veces
	while (cin >> N && N!=0) {
		// It initializes the in line
		for (int i=1; i<=N; i++)
			line_a.push_back(i);

		while (cin >> tmp && tmp != 0) {
			desired_combination.push_back(tmp);

			// it reads the rest of desired combination, and creates the coaches inside the line_a
			for (int i=1; i<N; i++) {
				cin >> tmp;
				desired_combination.push_back(tmp);
			}

			trainChief(line_a, line_b, poppush_city_station, desired_combination);

			// If the 
			if (line_b.size() == N)
				cout << "Yes" << endl;
			else 
				cout << "No" << endl;

			// It cleans all the containers
			line_b.clear();
			desired_combination.clear();
		}
		
		line_a.clear();

		cout << endl;
	}

	return 0;
}