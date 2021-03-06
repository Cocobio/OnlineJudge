/*

Problem: https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2613

Ignacio Osorio
Cocobio2

Generated by Ignacio Osorio Wallace

Asymptotic analysis of solution:
	temporal: O(N^2*(X-1.1*T)*K)	: Where N is the number of friends, X is the amount of money per friend, T is the price for the tea and K is the number of dim sums
	spatial: O((N^2*(X-1.1*T)*K)	: Same as above

	For the temporal analysis, all the complexities are commented right next to all of the lines. 

		=========================================================================================================================================================================
		create containers => O(1)

		read input => O(K*N)

		Create dynamic programming table => O(N^2*(X-1.1*T))	

		Base case dp => O(N^2*(X-1.1*T))

		dynamic programming solution => O(N^2*(X-1.1*T)*K)

		Output and clean => O(1)
		=========================================================================================================================================================================

		So the complexity will be: K*N + N^2*(X-1.1*T) + N^2*(X-1.1*T) + N^2*(X-1.1*T)*K
		= O(N^2*(X-1.1*T)*K)

	For the spatial analysis, we look at the variables.
		The inputs are the constants and the two containers that will hold the flavour value and the dim sum prices 2*K elements.
		
		The dynamic programming table takes (2*(N+1)+1)*((((X-T)*10-T)*(N+1))+1)*(K+1) space

		The resulting complexity is:

		O(N^2*(X-1.1*T)*K)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Creates a table for dynamic programming. 3-D
template <class T>
T*** create_dynamic_programming_table(size_t x, size_t y, size_t z) {	// O(x*y)
	T* data = (T*) malloc(x*y*z*sizeof(T));		// O(1)
	T** data_y = (T**) malloc(x*y*sizeof(T*));	// O(1)
	T*** table = (T***) malloc(x*sizeof(T**));	// O(1)

	for (int i=0; i<x; i++)					// O(x)
		table[i] = data_y+i*y;				// O(1)

	for (int i=0; i<x; i++)	{				// O(x*y)
		for (int j=0; j<y; j++)				// O(y)
			table[i][j] = data+i*y*z+j*z;	// O(1)
	}

	return table;							// O(1)
}

// Clean the memory requested
template <class T>
void clear_table(T*** table) {	// O(1)
	free(table[0][0]);	// O(1)
	free(table[0]);		// O(1)
	free(table);		// O(1)
}

int main() {
	unsigned short N,X,T,K;
	short tmp;

	// Since we can chose not buy, buy 1 or buy 2 from a dim sum
	// we need a max function that takes 3 arguments
	auto my_max = [] (float a, float b, float c) {	// O(1)
		if (a>b) {
			if (a>c) return a;
			else return c;
		}
		else {
			if (b>c) return b;
			else return c;
		}
	};

	// Read inputs until all of them are 0
	while (cin >> N >> X >> T >> K && 
		  (N!=0 || X!=0 || T!=0 || K!=0)) {
		vector<unsigned short> pricing(K, 0);		// O(1)
		vector<float> avr_flavour_val(K, 0.0);		// O(1)

		// Read the value and flavour rating for each dim sum
		for (int i=0; i<K; i++) {					// O(K*N)
			cin >> tmp;								// O(1)
			
			// Since we, as a group, have to tip the 10%, we might as well consider the price as the 1.1. Mult by 10
			// to round the price into a integer (so we can use it for accessing the dynamic programming table)
			pricing[i] = tmp*10+tmp;				// O(1)
			
			for (int j=0; j<N+1; j++) {				// O(N)
				cin >> tmp;							// O(1)
				avr_flavour_val[i] += tmp/(N+1.0);	// O(1)
			}
		}

		// Create dynamic programming table
		float*** table = create_dynamic_programming_table<float>(2*(N+1)+1, (((X-T)*10-T)*(N+1))+1, K+1); // O(2*N^2*(X-1.1*T)*10)	

		// Base case no dim sum on list
		for (int x=0; x<2*(N+1)+1; x++)					// O(2*N^2*(X-1.1*T)*10)
			for (int y=0; y<(((X-T)*10-T)*(N+1))+1; y++)// O((X-1.1*T)*10*N)
				table[x][y][0] = 0;

		// dynamic programming approach
		// it will save on the table the maximum flavour value achieved for the 'z' amount of dims sums, 'y' amount of money and 'x' amount of total dim sum that we can order 
		for (int x=0; x<2*(N+1)+1; x++)						// O(2*N^2*(X-1.1*T)*10*K)
			for (int y=0; y<(((X-T)*10-T)*(N+1))+1; y++)	// O(((X-T)*10-T)*K*N)
				for (int z=1; z<K+1; z++) {					// O(K)
					// Different posible values for not including, including 1 or 2 dishes for the 'z' dim sum
					float not_included = table[x][y][z-1];																					// O(1)
					float one_included = (x-1 < 0 || y-pricing[z-1] < 0) ? 0 : table[x-1][y-pricing[z-1]][z-1] + avr_flavour_val[z-1];		// O(1)
					float two_included = (x-2 < 0 || y-2*pricing[z-1] < 0) ? 0 : table[x-2][y-2*pricing[z-1]][z-1] + 2*avr_flavour_val[z-1];// O(1)			

					// Remember this maximum
					table[x][y][z] = my_max(not_included, one_included, two_included);														// O(1)
				}

		// Output the maximum flavour value and cleaning
		printf("%.2f\n", table[2*(N+1)] [(((X-T)*10-T)*(N+1))] [K]);// O(1)
		clear_table(table);											// O(1)
	}

	return 0;
}
