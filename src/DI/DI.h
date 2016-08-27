#ifndef __DI_H_INCLUDED__
#define __DI_H_INCLUDED__

template<class T> class DI {
 public:
	DI(T t_instance) {
		this->instance = t_instance;
	};

 private:
	T instance;

 protected:
	T getInstance() {
		return this->instance;
	}
};

#endif // __DI_H_INCLUDED__