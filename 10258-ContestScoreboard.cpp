/*

Problem: https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1199

Ignacio Osorio
Cocobio2

Sentencia de autoría: Indicando si el código entregado ha sido generado personalmente, con asistencia o tomado de alguna otra fuente (foros, páginas web, etc). En caso de que el código no haya sido generado personalmente, se deberán consignar la(s) persona(s) que asistieron en la elaboración del código y/o la referencia de dónde fue obtenido.
Análisis asintótico de la solución: Se deberá consignar el costo (en notación O) del tiempo y espacio requeridos por la solución (para el peor caso) y se deberá justificar este tiempo.

*/

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int cases;
	char c;

	cin >> cases;
	cin >> c;

	vector

	// id, score
	vector<pair<int,pair<int,int>>> score_board;
	
	// a sera mayor cuando
	// a tenga mayor puntaje o, tengan el mismo puntaje y tenga menos tiempo, o tengan el mismo puntaje, mismo tiempo y su id sea menor que el de b
	// a>b || (a=b && (( a.time<b.time) || ( a.time=b.time && a.id<b.id))
	bool eval(pair<int,pair<int,int>> a, pair<int,pair<int,int>> b) {
		return a.second.first>b.second || (a.second.first==b.second.first && (a.second.second<b.second.second || (a.second.second==b.second.second && a.first<b.first)));
	};

	for (int i=0; i<cases; i++) {

		sort(score_board.begin(), score_board.end(), eval);

		for (vector<pair<int,pair<int,int>>>::iterator it=score_board.begin(); it!=score_board.end(); it++) {
			cout << it->first << 
		} 
	}

	return 0;
}