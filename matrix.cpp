#include <iostream>
#include <exception>
#include <cmath>
#include "matrix.h"

//Create new way to initialize matrix, by passing list of lists
//Overload the operators + * - to eliminate the amount of functions such as add subtract and multiply

template<typename T>
Matrix<T>::Matrix():dimension_x{},dimension_y{},p_matrix{nullptr},m_name{}{
}

template <typename T>
Matrix<T>::Matrix(std :: size_t dim):dimension_x{dim},dimension_y{dim}, p_matrix{nullptr}, m_name{}{
	p_matrix = new T*[dim]{};
	for(std :: size_t i{};i<dim;++i){
		p_matrix[i] = new T[dim]{};
	}
}

template <typename T>
Matrix<T>::Matrix(std :: size_t dim_x, std :: size_t dim_y): dimension_x{dim_x},
dimension_y{dim_y}, p_matrix{nullptr}{
	p_matrix = new T*[dim_x]{};
	for(std :: size_t i{}; i<dim_x;++i){
		p_matrix[i] = new T[dim_y]{};
	}
}

template <typename T>
Matrix<T>::Matrix(std::size_t dim_x, std::size_t dim_y,std::string nome){
	dimension_x = dim_x;
	dimension_y = dim_y;
	m_name = nome;
	p_matrix = new T*[dim_x]{};
	for(std::size_t i{};i<dim_x;++i){
		p_matrix[i] = new T[dim_y]{};
	}
}

template<typename T>
Matrix<T>::~Matrix(){
}


template<typename T>
void Matrix<T>::set_matrix(T entry, std :: size_t index_x, std :: size_t index_y){
	p_matrix[index_x][index_y] = entry;
}


template<typename T>
void Matrix<T>::name_matrix(std::string nome){
	m_name = nome;
}



template <typename T>
std::string Matrix<T>::get_name(){
	return m_name;
}

template<typename T>
void Matrix<T>::print_matrix(){
	for(std :: size_t i{};i<dimension_x;++i){
		for(std :: size_t j{};j<dimension_y;++j){
			if(j == 0){
				std :: cout << "| ";
			}
			std :: cout << p_matrix[i][j] << " ";
			if(j == (dimension_y - 1)){
				std :: cout << "|";
			}
		}
		std :: cout << std :: endl;
	}
}


template <typename T>
void Matrix<T>::clear_matrix(){
	for(std :: size_t i{};i<dimension_y;++i){
		delete[] p_matrix[i];
		p_matrix[i] = nullptr;
	}
	delete[] p_matrix;
	p_matrix = nullptr;
}


template<typename T>
Matrix<T> Matrix<T>::add_matrix(Matrix B){
	if(dimension_x != B.dimension_x || dimension_y != B.dimension_y){
		throw std :: invalid_argument("Dimension of matrixes must be equal to each other");
	}
	Matrix resultante(dimension_x,dimension_y);
	for(std :: size_t i{0};i<dimension_x;++i){
		for(std :: size_t j{0};j<dimension_y;++j){
			resultante.p_matrix[i][j] = p_matrix[i][j] + B.p_matrix[i][j];
		}
	}
	return resultante;
}



template<typename T>
Matrix<T>Matrix<T>::subtract_matrix(Matrix B){
	Matrix sub(B.dimension_x,B.dimension_y);
	for(std :: size_t i{};i<B.dimension_x;++i){
		for(std :: size_t j{};j<B.dimension_y;++j){
			sub.p_matrix[i][j] = -(B.p_matrix[i][j]);
			//sub.set_matrix(-(B.p_matrix[i][j]),i,j);
		}
	}
	return add_matrix(sub);
}


template<typename T>
Matrix<T>Matrix<T>::scalar_multiplication(double scalar){
	Matrix resultante(dimension_x,dimension_y);
	for(std :: size_t i{};i<dimension_x;++i){
		for(std :: size_t j{};j<dimension_y;++j){
			if(p_matrix[i][j]!=0){
			resultante.p_matrix[i][j] = scalar*p_matrix[i][j];
			}
			else{
				resultante.p_matrix[i][j] = p_matrix[i][j];
			}
		}
	}
	return resultante;
}

template<typename T>
Matrix<T>Matrix<T>::matrix_multiply(Matrix B){
	if(dimension_y != B.dimension_x){
		throw std :: invalid_argument("Invalid Dimensions");
	}
	T somatorio{};
	Matrix resultante(dimension_x,B.dimension_y);
	for(std :: size_t i{};i<dimension_x;++i){
		for(std :: size_t k{};k<dimension_y;++k){
			somatorio = 0;
			for(std :: size_t j{};j<dimension_y;++j){
				somatorio += p_matrix[i][j]*B.p_matrix[j][k];
		}
		resultante.p_matrix[i][k] = somatorio;
		}
	}
	return resultante;
}


template<typename T>
T Matrix<T>::determinant(){
	if(dimension_x != dimension_y){
		throw std :: invalid_argument("Invalid Dimensions");
	}
	T result{0};
			if(dimension_x == 1){
				result = p_matrix[0][0];
				return result;
			}
			if(dimension_x == 2){
				result = p_matrix[0][0]*p_matrix[1][1] - p_matrix[0][1]*p_matrix[1][0];
				return result;
			}
			else{
				Matrix novo(dimension_x-1,dimension_y-1);
				for(std :: size_t i{0};i<dimension_x;++i){
					for(std::size_t j{0};j<novo.dimension_x;++j){
												std :: size_t k{0};
												std :: size_t K{k};
													while (k<novo.dimension_x){
														if(k!=i){
															novo.p_matrix[j][k] = p_matrix[j+1][K];
														}
														else{
															K++;
															novo.p_matrix[j][k] = p_matrix[j+1][K];
														}
														K++;
														k++;
													}
															}
					if (i%2==0){
						result+=p_matrix[0][i]*novo.determinant();
					}
					else{
						result-=p_matrix[0][i]*novo.determinant();
					}

				}
				return result;
}
}



template<typename T>
Matrix<T>Matrix<T>::transpose(){
	Matrix transposta(dimension_y,dimension_x);
	for(std :: size_t i{};i<dimension_x;++i){
		for(std :: size_t j{};j<dimension_y;++j){
			transposta.p_matrix[j][i] = p_matrix[i][j];
		}
	}
	return transposta;
}



template<typename T>
Matrix<T>Matrix<T>::co_factor_matrix(std::size_t x,std::size_t y){
	if(dimension_x != dimension_y || (dimension_y == 2 && dimension_x == 2)){
			throw std :: invalid_argument("Invalid Dimensions");
		}
	Matrix co_factor(dimension_x - 1 , dimension_y - 1);
	std::size_t k_i{};
	for(std::size_t i{};i<dimension_x - 1; ++i,++k_i){
		std::size_t k_j{0};
		if(i == x){
			++k_i;
				}
		for(std::size_t j{};j<dimension_y;++j,++k_j){
			if(j == y){
				++k_j;
				}
			co_factor.p_matrix[i][j] = p_matrix[k_i][k_j];
		}
	}
	return co_factor;
}



template <typename T>
Matrix<T>Matrix<T>::adj_matrix(){
	if(dimension_x != dimension_y){
		throw std :: invalid_argument("Invalid Dimensions");
	}
	if(dimension_x == 2){// CASO MATRIZ FOR 2x2
		Matrix adj(dimension_x,dimension_y);
		adj.p_matrix[0][0] = p_matrix[1][1];
		if(p_matrix[0][1] == 0){
			adj.p_matrix[0][1] = p_matrix[0][1];
		}
		else{
			adj.p_matrix[0][1] = -p_matrix[0][1];
		}
		if(p_matrix[1][0] == 0){
			adj.p_matrix[1][0] = p_matrix[1][0];
		}else{
			adj.p_matrix[1][0] = -p_matrix[1][0];
		}
		adj.p_matrix[1][1] = p_matrix[0][0];

		return adj;
	}
	else{// CASO MATRIZ SEJA NxN
	Matrix adj(dimension_x,dimension_y);
	for(std::size_t i{};i<dimension_x;++i){
		for(std::size_t j{};j<dimension_y;++j){
			if((i+j+2)%2 == 0 || co_factor_matrix(i,j).determinant() == 0){
				adj.p_matrix[i][j] = co_factor_matrix(i,j).determinant();
			}
			else{
				adj.p_matrix[i][j] = (-1)*co_factor_matrix(i,j).determinant();
			}
		}
	}
	return adj.transpose();
	}
}


template<typename T>
Matrix<T>Matrix<T>::inverse_matrix(){
	if(determinant() == 0){
		std::cout << "Matrix is invertible" << std :: endl;
		throw std :: domain_error("Division by zero -- Matrix is invertible");
	}
	return adj_matrix().scalar_multiplication(1.0/determinant());
}




template<typename T>
Matrix<T>Matrix<T>::raise_to_power(int power){
	Matrix<T> power_m(dimension_x,dimension_y);
	if(power == 0){
		for(std::size_t i{};i<dimension_x;++i){
			for(std::size_t j{};j<dimension_y;++j){
				if(i!=j){
					power_m.set_matrix(0,i,j);
				}
				else{
					power_m.set_matrix(1,i,j);
				}
			}
		}
		return power_m;
	}
	else {

		for (std::size_t i { 0 }; i < dimension_x; ++i) {
			for (std::size_t j { 0 }; j < dimension_y; ++j) {
				power_m.set_matrix(p_matrix[i][j], i, j);
			}
		}
		if (power <= -1) {
			Matrix<T> sub { power_m.inverse_matrix() };
			power_m = power_m.inverse_matrix();
			for (std::size_t i { 1 }; i < power; ++i) {
				power_m = sub.matrix_multiply(power_m);
			}
		}
		if (power >= 1) {
			for (std::size_t i { 1 }; i < power; ++i) {
				power_m = matrix_multiply(power_m);

			}
		}
		return power_m;
	}
}