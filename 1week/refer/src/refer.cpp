#include <map>
#include <iostream>
#include <string>
using namespace std;

template <typename key, typename value>
value& GetRefStrict(map<key, value>& m, key k){
	if(m.count(k) == 0){
		throw runtime_error("");
	}
	return m.at(k);
}

int main() {
	map<int, string> m = {{0, "value"}};
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl;
	return 0;
}
