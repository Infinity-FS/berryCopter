#include "DI.h"

template <typename T> DI<T>::DI(T t_instance) {
	this->instance = t_instance;
}