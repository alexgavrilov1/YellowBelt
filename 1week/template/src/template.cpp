#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

template <typename First, typename Second>
ostream& operator<<(ostream& stream, const pair<First, Second>& p);

template <typename T>
ostream& operator<<(ostream& stream, const vector<T>& vi);

template <typename key, typename value>
ostream& operator<<(ostream& stream, const map<key, value>& vi);

template<typename Collection>
string Join(const Collection& c, const char& d){
	stringstream ss;
	bool first = true;
	for(const auto& item: c){
		if(!first){
			ss << d;
		}
		first = false;
		ss << item;
	}
	return ss.str();
}
template <typename First, typename Second>
ostream& operator<<(ostream& stream, const pair<First, Second>& p){
	return stream << "(" << p.first << "," << p.second << ")";
}

template <typename T>
ostream& operator<<(ostream& stream, const vector<T>& vi){
	return stream << "[" << Join(vi, ',') << "]";
}

template <typename key, typename value>
ostream& operator<<(ostream& stream, const map<key, value>& vi){
	return stream << "{" << Join(vi, ',') << "}";
}


int main() {
	  vector<map<int, int>> vi = {{{1, 2}, {3, 4}}};
	  cout << vi << endl;
	  map<int, double> m = {{1, 2.5}, {3, 4}};
	  cout << m << endl;
	  vector<vector<int>> v = {{1, 2}, {3, 4}};
	  cout << v << endl;
	  cout << sizeof(size_t);
	  return 0;
}
