/*

Problem: https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=919

Ignacio Osorio
Cocobio2

Generated by Ignacio Osorio Wallace

Análisis asintótico de la solución: Se deberá consignar el costo (en notación O) del tiempo y espacio requeridos por la solución (para el peor caso) y se deberá justificar este tiempo.

*/
#include <iostream>
#include <queue>
#include <string>
#include <utility>

using namespace std;

// In wars there are no real winners
void announceWinner(string msg, priority_queue<char> &fighters) {
	cout << msg << endl;

	while (!fighters.empty()) {
		cout << (int)fighters.top() << endl;	// O(1)
		fighters.pop();							// O(log(n))
	}
}

// Getting savage!
void fight(char &green, char &blue) {			// O(1)
	if (green < blue) {
		blue -= green;
		green = 0;
	}
	else if (blue < green) {
		green -= blue;
		blue = 0;
	}
	else {
		green = 0;
		blue = 0;
	}
}

int main() {
	string green_win = "green wins";
	string blue_win = "blue wins";
	string tied = "green and blue died";

	unsigned short N;
	unsigned B, SG, SB;

	vector<pair<char,char>> battlefield;
	priority_queue <char> green_team, blue_team;
	char green_fighter, blue_fighter;
	short input_fighter;


	cin >> N;

	for (int i=0; i<N; i++) {
		cin >> B >> SG >> SB;

		for (int j=0; j<SG; j++) {
			cin >> input_fighter;
			green_team.push(input_fighter);
		}
		for (int j=0; j<SB; j++) {
			cin >> input_fighter;
			blue_team.push(input_fighter);
		}

		// FIGHT TO THE DEAD!
		while (green_team.size()!=0 && blue_team.size()!=0) {	// At maximun (SG+SB)/B
			// It populates the battlefields
			for (int j=0; j<B; j++) {
				if (green_team.empty() || blue_team.empty()) break;	// O(1)

				green_fighter = green_team.top();	// O(1)
				blue_fighter = blue_team.top();		// O(1)

				green_team.pop();	// O(log(n))
				blue_team.pop();	// O(log(n))

				fight(green_fighter, blue_fighter);	// O(1)

				battlefield.push_back(make_pair(green_fighter,blue_fighter));	// O(log(n))
			}

			// Check for survivors! If found, get them to safety, so they can experience the horrors on the battlefield again (if need it)
			for (auto nurse=battlefield.begin(); nurse!=battlefield.end(); nurse++) {
				if (nurse->first) green_team.push(nurse->first);			// Green survivor
				else if (nurse->second) blue_team.push(nurse->second);		// Blue sorvivor
			}
			battlefield.clear();
		}

		// Declare winner and survivors
		if (green_team.size()) announceWinner(green_win, green_team);
		else if (blue_team.size()) announceWinner(blue_win, blue_team);
		else cout << tied << endl;
	}

	return 0;
}