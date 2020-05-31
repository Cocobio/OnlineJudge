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
	car car_i;

	cin >> cases;

	for (int  i=1; i<=cases; i++) {
		cin >> ferry_n >> ferry_t >> cars_n;

		output_cars = vector<int>(cars_n);

		// Populate the lanes
		for (int j=0; j<cars_n; j++) {
			cin >> car_t >> car_lane;

			if (car_lane.compare("left"))
				left_lane.emplace_back(j,car_t);
			else // we asume that we only get left or right
				right_lane.emplace_back(j, car_t);
		}

		// it starts at the begining of the day, with the ferry on the left side
		current_t = 0;
		ferry_current_side = false;	// false = left, true = right

		// The ferry will transport them until no more cars to transport
		while (!left_lane.empty() && !right_lane.empty()) {
			// Load from left side
			if (!ferry_current_side) {
				// if there are cars waiting
				if(left_lane[0].get_t() <= current_t) {
					for (int j=0; j<ferry_n && left_lane.front().get_t()==current_t; j++) {
						car_i = left_lane.front();
						left_lane.pop_front();
						ferry.push_back(car_i);
					}
				}
				// if the next car to arrive at both sides is at the left side (no cars waiting on the other side) 
				else if (left_lane[0].get_t() <= right_lane[0].get_t()) {
					// this would be the next time the ferry will start to cross again
					current_t = left_lane[0].get_t();

					for (int j=0; j<ferry_n && left_lane.front().get_t()==current_t; j++) {
						car_i = left_lane.front();
						left_lane.pop_front();
						ferry.push_back(car_i);
					}
				}
			}
			// Load from right side
			else {
				// if there are cars waiting
				if(right_lane[0].get_t() <= current_t) {
					for (int j=0; j<ferry_n && right_lane.front().get_t()==current_t; j++) {
						car_i = right_lane.front();
						right_lane.pop_front();
						ferry.push_back(car_i);
					}
				}
				// if the next car to arrive at both sides is at the left side (no cars waiting on the other side) 
				else if (right_lane[0].get_t() <= left_lane[0].get_t()) {
					// this would be the next time the ferry will start to cross again
					current_t = right_lane[0].get_t();

					for (int j=0; j<ferry_n && right_lane.front().get_t()==current_t; j++) {
						car_i = right_lane.front();
						right_lane.pop_front();
						ferry.push_back(car_i);
					}
				}
			}

			// Time that takes the ferry to cross
			current_t += ferry_t;
			// The ferry crosses to the other side
			ferry_current_side = !ferry_current_side;

			// Unload the ferry
			while (!ferry.empty()) {
				car_i = ferry.front();
				ferry.pop_front();

				output_cars[car_i.get_id()] = current_t;
			}
			// for (auto it=ferry.begin(), it!=ferry.end(); it++, ferry.pop_front())
			// 	output_cars[(*it).get_id()] = current_t;
		}

		// Output the times when the cars were unloaded on the other side
		for (auto it=output_cars.begin(); it!=output_cars.end(); it++)
			cout << *it << endl;

		// output line between cases
		if (i!=cases) cout << endl;
	}

	return 0;
}