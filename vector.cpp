#include <iostream>
#include <exception>
#include <cmath>
#include "vector.h"

//Create new way to initialize vector, by passing list 
//Overload the operators + * - to eliminate the amount of functions such as add subtract and multiply

template<typename T>
Vector<T>::Vector():dimension{},p_vec{nullptr},vec_name{}{
}

template <typename T>
Vector<T>::Vector(std :: size_t dim): dimension{dim}, p_vec{nullptr},vec_name{}{
	p_vec = new T[dimension]{};
}



template<typename T>
Vector<T>::Vector(T entries, std :: size_t dim): dimension{}, p_vec{nullptr},vec_name{}{
	if(dim<=0){
		throw std :: invalid_argument("Dimension not equal or greater than one.");

	}
	dimension = dim;
	p_vec = new T[dim];
	for(std :: size_t i{};i<dim;++i){
		p_vec[i] = entries;
	}
}

template <typename T>
Vector<T>::~Vector(){

}


template<typename T>
void Vector<T>::init_vec(std::size_t dim){
	dimension = dim;
	p_vec = new T[dimension]{};
}



template<typename T>
void Vector<T>::set_new_entry(T entry, std :: size_t index){
	p_vec[index] = entry;
}



template<typename T>
void Vector<T>::name_vec(std::string nome){
	vec_name = nome;
}


template<typename  T>
std::string Vector<T>::get_name_v(){
	return vec_name;
}






template<typename T>
std :: size_t Vector<T>::get_dim(){
	return dimension;
}

template<typename T>
T Vector<T>::get_entry(std :: size_t index){
	return p_vec[index];
}

template <typename T>
Vector<T> Vector<T>::add_vec(Vector v_add){
	if(v_add.get_dim() != dimension){
		throw std :: invalid_argument("Different dimensions");
	}
	Vector result_vec(dimension);
	for(std :: size_t k{}; k<get_dim(); ++k){
		 result_vec.p_vec[k]= v_add.p_vec[k] + p_vec[k];
	}
	return result_vec;
}


template <typename T>
Vector<T> Vector<T>::subtract_vec(Vector v_subtract){
	Vector sub(v_subtract.get_dim());
	for(std :: size_t k{}; k<v_subtract.get_dim();++k){
		sub.set_new_entry(-(v_subtract.p_vec[k]), k);
	}
	return add_vec(sub);
}

template <typename T>
void Vector<T>::print_vec(){
	for(std :: size_t i{0};i<dimension;++i){
		if(i == 0){
			std :: cout << "< " << p_vec[i] << ", ";
		}
		else if(i<dimension-1){
			std :: cout << p_vec[i] << ", ";
		}
		else{
			std :: cout << p_vec[i] << " >" << std :: endl;
		}
	}
}


template<typename T>
void Vector<T>::clear_vec(){
	delete p_vec;
	p_vec = nullptr;
}


template <typename T>
Vector<T> Vector<T>::scalar_multiply(T scalar){
	Vector result_vec(dimension);
	for(std :: size_t i{};i<dimension; ++i){
		result_vec.set_new_entry(scalar*p_vec[i],i);
	}
	return result_vec;
}


template<typename T>
Vector<T> Vector<T>::dot_product(Vector v_dot){
	T new_entry{};
	if(v_dot.get_dim() != dimension){
		throw std:: invalid_argument("Different dimensions");
	}
	Vector result_vec(dimension);
	for(std :: size_t i{};i<dimension;++i){
		new_entry = p_vec[i]*(v_dot.p_vec[i]);
		result_vec.set_new_entry(new_entry,i);
	}

	return result_vec;
}


template <typename T>
Vector<T> Vector<T>::cross_product(Vector v_cross){
	if(dimension!=3 || v_cross.dimension!=3){
		throw std :: invalid_argument("Invalid Dimensions");
	}
	Vector n(3);
	n.set_new_entry((p_vec[1]*v_cross.p_vec[2] - p_vec[2]*v_cross.p_vec[1]),0);
	n.set_new_entry((p_vec[2]*v_cross.p_vec[0] - p_vec[0]*v_cross.p_vec[2]),1);
	n.set_new_entry((p_vec[0]*v_cross.p_vec[1] - p_vec[1]*v_cross.p_vec[0]),2);

	return n;
}




template <typename T>
T Vector<T>::norm(){
	T resultado{};
	for(std :: size_t i{}; i<dimension; ++i){
		resultado += get_entry(i)*get_entry(i);
	}
	if(sqrt(resultado) < 0){
		throw std ::domain_error("Norm of a vector is always greater or equal to 0");
	}
	return sqrt(resultado);
}