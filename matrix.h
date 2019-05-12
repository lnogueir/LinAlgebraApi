#include <iostream>

template<typename T> class Matrix;

//Create new way to initialize matrix, by passing list of lists
//Overload the operators + * - to eliminate the amount of functions such as add subtract and multiply

#ifndef MATRIX_H_
#define MATRIX_H_
template <typename T>
class Matrix{
	friend class Armazem<T>;
private:
	std :: size_t dimension_x; // ESTOU REPRESENTANDO X COMO LINHAS
	std :: size_t dimension_y; // ESTOU REPRESENTANDO Y COMO COLUNAS
	T **p_matrix;
	std::string m_name;
public:
	Matrix();
	Matrix(std :: size_t dim); // CASO SEJA SQUARE MATRIX;
	Matrix(std::size_t dim_x,std :: size_t dim_y);
	Matrix(std::size_t dim_x, std::size_t dim_y, std::string nome);
	~Matrix();
	void set_matrix(T entry, std::size_t index_x,std :: size_t index_y);
	void name_matrix(std::string nome);
	std::string get_name();
	void print_matrix();
	void clear_matrix();
	Matrix add_matrix(Matrix B);
	Matrix subtract_matrix(Matrix B);
	Matrix scalar_multiplication(double scalar);
	Matrix matrix_multiply(Matrix B);
	T determinant();
	Matrix transpose();
	Matrix co_factor_matrix(std :: size_t x, std :: size_t y);
	Matrix adj_matrix();
	Matrix inverse_matrix();
	Matrix raise_to_power(int power);
};


#endif /* MATRIX_H_ */