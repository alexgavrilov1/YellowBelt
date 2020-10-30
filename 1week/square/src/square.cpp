#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

template <typename T>
vector<T> operator*(const vector<T>& lhs, const vector<T>& rhs);

template <typename Key, typename Value>
map<Key, Value> operator*(const map<Key, Value>& lhs, const map<Key, Value>& rhs);

template <typename First, typename Second>
pair<First, Second> operator*(const pair<First, Second>& lhs,
		const pair<First, Second>& rhs);

template <typename T>
T Sqr(const T& x);

template <typename T>
vector<T> operator*(const vector<T>& lhs, const vector<T>& rhs){
	vector<T> result;
	for(const auto& item: lhs){
		result.push_back(item * item);
	}
	return result;
}

template <typename Key, typename Value>
map<Key, Value> operator*(const map<Key, Value>& lhs, const map<Key, Value>& rhs){
	map<Key, Value> result;
	for(const auto& item: lhs){
		result[item.first] = item.second * item.second;
	}
	return result;
}

template <typename First, typename Second>
pair<First, Second> operator*(const pair<First, Second>& lhs,
		const pair<First, Second>& rhs){
	return make_pair(lhs.first * rhs.first, lhs.second * rhs.second);
}


template <typename T>
T Sqr(const T& x){
	return x * x;
}

int main() {
	vector<int> v = {1, 2, 3};
	cout << "vector:";
	for (int x : Sqr(v)) {
	  cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
	  cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
	return 0;
}
