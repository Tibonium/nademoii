#include <iostream>
#include <genecis/probability/binomial.h>

USING_NAMESPACE(std)
USING_NAMESPACE(genecis::probability)
USING_NAMESPACE(genecis::math)

int main(int argv, char* argc[])
{
	cout << "11 choose 3: " << choose(11, 3) << endl ;
	cout << "11 choose 3, with probability of success at 10%: " << binomial::pmf(11, 3, 0.1)*100.0 << "%" << endl ;
	cout << "110 choose 50, with probability of success at 10%: " << binomial::pmf(110, 50, 0.1)*100.0 << "%" << endl ;
		
	cout << "Chance for 1 5* in an 11-draw: " << binomial::pmf(11, 1, 0.1)*100.0 << "%" << endl ;
	cout << "Chance for 2 5*s in an 11-draw: " << binomial::pmf(11, 2, 0.1)*100.0 << "%" << endl ;
	
	cout << "Chance for 1 5* in a 3-draw: " << binomial::pmf(3, 1, 0.1)*100.0 << "%" << endl ;
	cout << "Chance for 2 5*s in a 3-draw: " << binomial::pmf(3, 2, 0.1)*100.0 << "%" << endl ;
	cout << "Chance for 2 5*s in two 3-draws: " << binomial::pmf(6, 2, 0.1)*100.0 << "%" << endl ;

}
