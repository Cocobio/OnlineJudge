/*

Problem: https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=565

Ignacio Osorio
Cocobio2

Generated by Ignacio Osorio Wallace

Asymptotic analysis of solution:
	temporal: O(tape_length*track_n)	: Where tape_length is the size of the tape (in minutes) and track_n is the number of tracks on the CD
	spatial: O(tape_length*track_n)		: Same as above

	For the temporal analysis, all the complexities are commented right next to all of the lines. 

		=========================================================================================================================================================================
		**** track_n is the number of tracks on the CD. **** tape_length is the length in minutes for the tape ****
		read input => O(track_n)

		create a dynamic programming table with access as a matrix => O(track_n)

		set the case for no tracks added to the tape => O(tape_length)

		fill the dynamic programming table => O(tape_length*track_n)

		print results => O(track_n)

		clear containers => O(1)
		=========================================================================================================================================================================

		So the complexity will be: track_n + track_n + tape_length + tape_length*track_n + track_n + 1 = 3*track_n + tape_length + tape_length*track_n
		= O(tape_length*track_n)

	For the spatial analysis, we look at the variables.
		The inputs are all integers, and a total of 2+track_n. each track wont be longer than the tape itself, so the space needed would be at most track_n*log(tape_length)/log(2)
		for the tape length and the track lengths. For the track_n, it doesn't say anything, so we could reserve 32 bits (the size of a integer on a computer) for it (constant)

		For the dynamic programming table the space is tape_length*track_n*log(tape_length)

		On this algorithm the size for storing the inputs are fixed on 32 bits, so the complexity results on:

		O(input + dynamic_programming_table)
		O(track_n + tape_length*track_n) = O(tape_length*track_n)

*/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

// Creates a table for dynamic programming.
template <class T>
T** create_dynamic_programming_table(unsigned x, unsigned y) {	// O(y)
	T* data = (T*) malloc(x*y*sizeof(T));
	T** table = (T**) malloc(y*sizeof(T*));

	for (int i=0; i<y; i++)			// O(y)
		table[i] = data+i*x;		// O(1)

	return table;					// O(1)
}

// Clean the memory requested
template <class T>
void clear_table(T** table) {	// O(1)
	free(table[0]);
	free(table);
}


int main() {
	string line;

	while (getline(cin, line) && line.size() != 0) { // Reads each case
		stringstream s(line);

		// Declare variables
		unsigned tape_length;
		unsigned track_n;
		vector<unsigned> track_times;
		unsigned tmp;

		// Parse input data for the case
		s >> tape_length;								// O(1)
		s >> track_n;									// O(1)
		while (s >> tmp) track_times.push_back(tmp);	// O(track_n)

		// Create a table for memoization
		unsigned ** table = create_dynamic_programming_table<unsigned>(tape_length+1, track_times.size()+1);	// O(track_n)

		// Base case for dynamic programming solution
		// its created at the end of the table, to facilitate the order for the output
		for (int i=0; i<=tape_length; i++) table[track_times.size()][i] = i;	// O(tape_length)

		// dynamic programming approach
		// it will save on a table the minimum residual tape space for each track if it is included or not.
		for (int i=track_times.size()-1; i>=0; i--) {			// O(tape_length*track_n)
			for (unsigned j=0; j<=tape_length; j++) {			// O(tape_length)
				unsigned included;								// O(1)
				unsigned not_included = table[i+1][j];			// O(1)
				unsigned tape_j = j-track_times[i];				// O(1)
				
				// it gets cast to a unsigned so it cant be check if is less than 0
				if (tape_j > tape_length) { 					// O(1)
					table[i][j] = not_included;					// O(1)
				}
				else {
					included = table[i+1][tape_j];				// O(1)
					table[i][j] = min(included, not_included);	// O(1)
				}
			}
		}

		// Print results
		for (int i=0,j=tape_length; i<track_times.size(); i++) {	// O(track_n)
			unsigned tape_j = j-track_times[i];	// O(1)

			if (tape_j<=tape_length && table[i][j] == table[i+1][tape_j]) {	// O(1)
				cout << track_times[i] << " ";	// O(1)
				j = tape_j;						// O(1)
			}
		}

		cout << "sum:" << tape_length-table[0][tape_length];	// O(1)
		cout << endl;

		// Clear containers
		clear_table(table);		// O(1)
		track_times.clear();	// O(1) because of data type
	}

	return 0;
}
