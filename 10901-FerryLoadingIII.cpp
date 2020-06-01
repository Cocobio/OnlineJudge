/*

Problem: https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1842

Ignacio Osorio
Cocobio2

Sentencia de autoría: Indicando si el código entregado ha sido generado personalmente, con asistencia o tomado de alguna otra fuente (foros, páginas web, etc). En caso de que el código no haya sido generado personalmente, se deberán consignar la(s) persona(s) que asistieron en la elaboración del código y/o la referencia de dónde fue obtenido.

Análisis asintótico de la solución: Se deberá consignar el costo (en notación O) del tiempo y espacio requeridos por la solución (para el peor caso) y se deberá justificar este tiempo.

zCódigo comentado

    El código deberá estar adecuadamente comentado. Se exigirá mayor prolijidad en los comentarios, especialmente en el caso de que el código no sea de entera autoría propia. En especial, si el código no es de entera autoría del estudiante y no se registran comentarios, el ejercicio será calificado con la nota de 1.

*/
#include <iostream>
#include <vector>
#include <deque>
#include <string>

using namespace std;

class car {
private:
	int car_id;
	int car_arrive_t;
public:
	car() {}
	car(int id, int t) { 
		car_id=id;
		car_arrive_t = t;
	}

	int get_id() { return car_id; }
	int get_t() { return car_arrive_t; }
};

void loadFerry(int &current_t, deque<car> *current_lane, deque<car> &ferry, int ferry_capacity) {
	car car_i;
	// if we have to wait, it fastforwards to the new car
	if ((*current_lane).front().get_t() > current_t) current_t = (*current_lane).front().get_t();

	// load at most ferry_capacity cars. Cars must be waiting or just arrived.
	for (int i=0; (*current_lane).size() && i<ferry_capacity && (*current_lane).front().get_t()<=current_t; i++) {
		car_i = (*current_lane).front();
		(*current_lane).pop_front();
		ferry.push_back(car_i);
	}

}

int main() {
	int cases;
	int current_t;

	int ferry_n;
	int ferry_t;
	int cars_n;

	string car_lane;
	int car_t;

	deque<car> left_lane;
	deque<car> right_lane;
	deque<car> ferry;
	vector<int> output_cars;
	bool ferry_current_side;

	// reference
	deque<car> *current_lane, *other_lane;

	cin >> cases;

	for (int  i=1; i<=cases; i++) {
		cin >> ferry_n >> ferry_t >> cars_n;

		output_cars = vector<int>(cars_n);

		// Populate the lanes
		for (int j=0; j<cars_n; j++) {
			cin >> car_t >> car_lane;

			if (car_lane.compare("left") == 0)
				left_lane.emplace_back(j,car_t);
			else // we asume that we only get left or right
				right_lane.emplace_back(j, car_t);
		}

		// it starts at the begining of the day, with the ferry on the left side
		current_t = 0;
		ferry_current_side = false;	// false = left, true = right

		// The ferry will transport them until no more cars to transport
		while (!left_lane.empty() || !right_lane.empty()) {
			// We set our current position
			if (ferry_current_side) {
				current_lane = &right_lane;
				other_lane = &left_lane;
			}
			else {
				current_lane = &left_lane;
				other_lane = &right_lane;
			}

			// Load ferry
			if ((*current_lane).size() && ((*current_lane).front().get_t() <= current_t || ((*other_lane).empty() || (*current_lane).front().get_t() <= (*other_lane).front().get_t())))
				loadFerry(current_t, current_lane, ferry, ferry_n);
			else if ((*other_lane).front().get_t()>current_t)
				current_t = (*other_lane).front().get_t();


			// Time that takes the ferry to cross
			current_t += ferry_t;
			// The ferry crosses to the other side
			ferry_current_side = !ferry_current_side;

			// Unload the ferry
			for (auto it=ferry.begin(); it!=ferry.end(); it++, ferry.pop_front())
				output_cars[(*it).get_id()] = current_t;
		}

		// Output the times when the cars were unloaded on the other side
		for (auto it=output_cars.begin(); it!=output_cars.end(); it++)
			cout << *it << endl;

		// output line between cases
		if (i!=cases) cout << endl;
	}

	return 0;
}