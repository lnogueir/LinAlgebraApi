#ifndef VECTOR_H_
#define VECTOR_H_

template<typename T> class Vector;

template <typename T>
class Vector{
	friend class Armazem<T>;
private:
	std :: size_t dimension;
	T *p_vec;
	std::string vec_name;

public:
	Vector();
	Vector(std ::size_t dim);
	Vector(T entries, std :: size_t dim);
	~Vector();
	void init_vec(std::size_t dim);
	void set_new_entry(T entry, std :: size_t index);
	void name_vec(std::string nome);
	std::string get_name_v();
	std :: size_t get_dim();
	T get_entry(std :: size_t index);
	Vector add_vec(Vector v_add);
	Vector subtract_vec(Vector v_subtract);
	void print_vec();
	void clear_vec();
	Vector scalar_multiply(T scalar);
	Vector dot_product(Vector v_dot);
	Vector cross_product(Vector v_cross);
	void set_matrix(std :: size_t dim);
	T norm();
};


#endif /* VECTOR_H_ */