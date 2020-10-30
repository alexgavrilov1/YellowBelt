#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
	uint64_t result;
	uint N, R;
	uint64_t sum = 0;
	cin >> N >> R;
	for(uint i = 0; i < N; i++){
		uint num1, num2, num3;
		cin >> num1 >> num2 >> num3;
		uint64_t p = static_cast<uint64_t>(num1) * num2 * num3;
		sum += p;
	}
	result = R * sum;
	cout << result;
	return 0;
}



