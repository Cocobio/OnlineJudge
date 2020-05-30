/*

Problem: https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=3644

Ignacio Osorio Wallace
Cocobio2

Generated by Ignacio Osorio Wallace

Análisis asintótico de la solución: Se deberá consignar el costo (en notación O) del tiempo y espacio requeridos por la solución (para el peor caso) y se deberá justificar este tiempo.

*/

#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class Register {
public:
	unsigned short id;
	unsigned step;
	unsigned next_pop;

	Register() {}

	Register(unsigned short id, unsigned step, unsigned next_pop) {
		this->id = id;
		this->step = step;
		this->next_pop = next_pop;
	}

	bool operator >(const Register &b) const {
		return next_pop>b.next_pop || (next_pop==b.next_pop && id>b.id);
	} 
};

int main() {
	priority_queue<Register, vector<Register>, greater<Register>> Argus_query;
	Register tmpReg;

	// Input data
	string word;
	unsigned short id;
	unsigned step;
	int K;

	cin >> word;

	while (word.compare("#")!=0) {
		cin >> id >> step >> word;
		Argus_query.emplace(id,step,step);
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