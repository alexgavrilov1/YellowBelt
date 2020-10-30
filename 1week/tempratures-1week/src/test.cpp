#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int N;
	cin >> N;
	vector<int> temps(N);
	int64_t sum = 0;
	for(int& item: temps){
		cin >> item;
		sum += item;
	}
	int avg = sum / N;
	cout << count_if(begin(temps), end(temps), [avg](int i){
		if(i > avg){
			return true;
		}
		return false;
	}) << endl;
	for(int i = 0; i < N; i++){
		if(temps[i] > avg){
			cout << i << " ";
		}
	}

}
