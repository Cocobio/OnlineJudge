/*

Problem: https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=2261

Ignacio Osorio
Cocobio2

Sentencia de autoría: Indicando si el código entregado ha sido generado personalmente, con asistencia o tomado de alguna otra fuente (foros, páginas web, etc). En caso de que el código no haya sido generado personalmente, se deberán consignar la(s) persona(s) que asistieron en la elaboración del código y/o la referencia de dónde fue obtenido.
Análisis asintótico de la solución: Se deberá consignar el costo (en notación O) del tiempo y espacio requeridos por la solución (para el peor caso) y se deberá justificar este tiempo.

*/

#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	// 1 <= n <= 10k,  -32k <= short <= 32k
	unordered_map<string, short> combinations;
	vector<short> classes;
	short frosh;
	short class_id;
	string key_buffer;

	priority_queue<short> concurrencies;
	short top_concurrency;
	short n_prize;

	while (cin >> frosh && frosh != 0) {
		for (int student=0; student<frosh; student++) {
			for (int i=0; i<5; i++) {
				cin >> class_id;
				classes.push_back(class_id);
			}
			sort(classes.begin(), classes.end());

			// It forms the key for the combination
			key_buffer = "";
			for (auto it=classes.begin(); it!=classes.end(); it++)
				key_buffer += to_string(*it);
			classes.clear();

			// It adds 1 to the combination concurrency
			if (combinations.find(key_buffer)!=combinations.end())
				combinations[key_buffer]++;
			else
				combinations[key_buffer] = 1;

		}

		for (auto it=combinations.begin(); it!=combinations.end(); it++)
			concurrencies.push(it->second);
		
		n_prize = 0;

		for (top_concurrency=concurrencies.top(); top_concurrency==concurrencies.top() && concurrencies.size(); concurrencies.pop())
			n_prize += top_concurrency;

		cout << n_prize << endl;

		// clear containers
		combinations.clear();

	}

	return 0;
}