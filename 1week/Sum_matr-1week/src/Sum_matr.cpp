#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix{
public:
	Matrix(){
		num_rows = 0;
		num_cols = 0;
		Reset(num_rows, num_cols);
	}
	Matrix(int new_num_rows, int new_num_cols){
		if(new_num_rows < 0 || new_num_cols < 0){
			throw out_of_range("number is negative");
		}
		Reset(new_num_rows, new_num_cols);

	}
	void Reset(int new_num_rows, int new_num_cols){
		if(new_num_rows < 0 || new_num_cols < 0){
			throw out_of_range("number is negative");
		}
		if(new_num_rows == 0 || new_num_cols == 0){
			num_rows = num_cols = 0;
		}
		else{
			num_rows = new_num_rows;
			num_cols = new_num_cols;
		}
		m.assign(num_rows, vector<int>(num_cols));
	}
	int At(int num_of_row, int num_of_col)const{
		if(num_of_row > num_rows || num_of_col > num_cols || num_of_row < 0 || num_of_col < 0){
			throw out_of_range("out of range");
		}
		return m.at(num_of_row).at(num_of_col);
	}
	int& At(int num_of_row, int num_of_col){
		if(num_of_row >= num_rows || num_of_col >= num_cols || num_of_row < 0 || num_of_col < 0){
			throw out_of_range("out of range");
		}
		return m.at(num_of_row).at(num_of_col);
	}
	int GetNumRows()const{
		return num_rows;
	}
	int GetNumColumns()const{
		return num_cols;
	}
private:
	vector<vector<int>> m;
	int num_rows;
	int num_cols;
};

istream& operator>>(istream& stream, Matrix& matrix){
	int row, col;
	stream >> row >> col;
	matrix.Reset(row, col);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			stream >> matrix.At(i,j);
		}
	}
	return stream;
}

ostream& operator<<(ostream& stream,const Matrix& matrix){
	stream << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;;
	for(int i = 0; i < matrix.GetNumRows(); i++){
		for(int j = 0; j < matrix.GetNumColumns(); j++){
			stream << matrix.At(i,j) << " ";
		}
		stream << endl;
	}
	return stream;
}

bool operator==(const Matrix& left, const Matrix& right){

	if(left.GetNumRows() == right.GetNumRows() && left.GetNumColumns() == right.GetNumColumns()){
		for(int i = 0; i < left.GetNumRows(); i++){
			for(int j = 0; j < left.GetNumColumns(); j++){
				if(left.At(i,j) != right.At(i,j)){
					return false;
				}
			}
		}
	}
	else{
		return false;
	}
	return true;
}

Matrix operator+(const Matrix& left, const Matrix& right){
	if(left.GetNumRows() != right.GetNumRows()){
		throw invalid_argument("Invalid rows");
	}
	if(left.GetNumColumns() != right.GetNumColumns()){
		throw invalid_argument("Invalid columns");
	}
	Matrix c(left.GetNumRows(), left.GetNumColumns());
	for(int i = 0; i < left.GetNumRows(); i++){
		for(int j = 0; j < left.GetNumColumns(); j++){
			c.At(i, j) = left.At(i, j) + right.At(i, j);
		}
	}
	return c;
}


int main() {
	Matrix one;
    Matrix two;

    cin >> one >> two;
    cout << one + two << endl;
    return 0;

}



