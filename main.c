// Program: Finds the nth Prime Number in Sequence
// Input: n
// Output: nth Prime
/* Steps:
 *      1. Create Array to Hold Only Prime Values
 *      2. Create Counter to Value n
 *      3. Create Loop That Checks if Test Value is Composite
 *      4. If Not Composite, Add to Prime Array
 *      5. After Count Reaches n, Return Array Value at Count Index
*/

#include<stdio.h>

int nthPrime(int n) {
	int i, flag = 0;
	
	for (i = 2; i <= (n/2); ++i) {
		if (n % i == 0)
		{
			flag = 1;
			break;
		}
	}

	if (n == 1) {
		printf("Value 1 is Not Prime");
	}
	else {
		if (flag == 0)
		printf("Prime.");
		else
		printf("Composite.");
	}


}


int main() {

	nthPrime(4);
	nthPrime(3);

	return 0;
}