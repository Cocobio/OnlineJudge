/*

Problem: https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1199

Ignacio Osorio
Cocobio2

Sentencia de autoría: Indicando si el código entregado ha sido generado personalmente, con asistencia o tomado de alguna otra fuente (foros, páginas web, etc). En caso de que el código no haya sido generado personalmente, se deberán consignar la(s) persona(s) que asistieron en la elaboración del código y/o la referencia de dónde fue obtenido.
Análisis asintótico de la solución: Se deberá consignar el costo (en notación O) del tiempo y espacio requeridos por la solución (para el peor caso) y se deberá justificar este tiempo.

*/

#define N_PROBLEMS 9

#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <vector>
#include <array>
#include <sstream>

using namespace std;

bool eval(pair<int,pair<int,int>> a, pair<int,pair<int,int>> b) {
	return a.second.first>b.second.first || (a.second.first==b.second.first && (a.second.second<b.second.second || (a.second.second==b.second.second && a.first<b.first)));
};

// No necesito un mapa para el score_board, no tiene sentido dejarlo guardado si voy a ordenarlo despues
// podria cambiar el vector de un monton de pares, por un vector<array<int,3>>
int main() {
	int cases;
	char c;
	int contestant_id, problem_id;
	int time;

	// <id, advances on problems>
	unordered_map<short,array<int,N_PROBLEMS>> problems_student;
	array<int,N_PROBLEMS> problems_tmp;

	// id, score
	map<int,pair<int,int>> score_board;
	vector<pair<int,pair<int,int>>> sorting_container;

	

	string s_stream;

	// Read cases, then 
	cin >> cases;
	// Read empty line
	getline(cin, s_stream);

	for (int i=0; i<cases; i++) {

		// Each case
		while (getline(cin, s_stream) && s_stream.size()!=0) {
			stringstream s(s_stream);
			s >> contestant_id >> problem_id >> time >> c;

			if (score_board.find(contestant_id)==score_board.end()) {
				score_board.emplace(contestant_id, make_pair(0,0));
				problems_tmp = array<int,N_PROBLEMS>();
				problems_tmp.fill(0);

				problems_student[contestant_id] = problems_tmp;
			}
			
			if (problems_student[contestant_id][problem_id-1] == -1) continue;

			else if (c == 'C') {
				score_board[contestant_id].first += 1;
				score_board[contestant_id].second += problems_student[contestant_id][problem_id-1] + time;
				problems_student[contestant_id][problem_id-1] = -1;
			}

			else if (c == 'I') {
				problems_student[contestant_id][problem_id-1] += 20;
			}
		}
		
		for (auto it=score_board.begin(); it!=score_board.end(); it++)
			sorting_container.push_back(*it);

		sort(sorting_container.begin(), sorting_container.end(), eval);

		for (auto it=sorting_container.begin(); it!=sorting_container.end(); it++)
			cout << it->first << " " << it->second.first << " " << it->second.second << endl; 

		problems_student.clear();
		sorting_container.clear();
		cout << endl;
	}

	return 0;
}