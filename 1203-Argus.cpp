/*

Problem: https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=3644

Ignacio Osorio
Cocobio2

Sentencia de autoría: Indicando si el código entregado ha sido generado personalmente, con asistencia o tomado de alguna otra fuente (foros, páginas web, etc). En caso de que el código no haya sido generado personalmente, se deberán consignar la(s) persona(s) que asistieron en la elaboración del código y/o la referencia de dónde fue obtenido.
Análisis asintótico de la solución: Se deberá consignar el costo (en notación O) del tiempo y espacio requeridos por la solución (para el peor caso) y se deberá justificar este tiempo.

*/
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;
// class MyQueue : public priority_queue {}

class Register {
public:
	int id;
	int step;
	int next_pop;

	Register() {}

	Register(int id, int step, int next_pop) {
		this->id = id;
		this->step = step;
		this->next_pop = next_pop;
	}

	bool operator <(const Register &b) const {
		return next_pop<b.next_pop || (next_pop==b.next_pop && id<b.id);
	} 
};

int main() {
	priority_queue<Register, vector<Register>, less<Register>> Argus_query;
	Register tmpReg;

	// Input data
	string word;
	int id, step;
	int K;

	cin >> word;
	while (!word.compare("#")) {
		cin >> id >> step;
		tmpReg = Register(id,step,step);
		Argus_query.push(tmpReg);
		cin >> word;
	}
	
	cin >> K;

	for (int i=0; i<K; i++) {
		tmpReg = Argus_query.top();
		Argus_query.pop();
		cout << tmpReg.id << endl;

		tmpReg.next_pop += tmpReg.step;
		Argus_query.push(tmpReg);
	}

	return 0;
}