#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>
using namespace std;

//интерфейс шаблона класса stack:

template <class T>
class stack
{
public:
	stack();
	size_t count() const;
	void push(T const &);
	T pop();
	~stack();
private:
	T * array_; //массив который будем забивать
	size_t count_; //номер элемента
	size_t capacity_;  //зарезервированная память (первоначальный размер стека)
	void reallocate(); //перераспределение
};

//реализация методов класса:

template <typename T>
void stack<T>::reallocate() 
{
	capacity_ *= 2; //увеличение зарез.памяти в 2 раза
	T* temp = new T[capacity_]; //выделение памяти под массив temp
	for (size_t i = 0; i < count_; ++i)
	{
		temp[i] = array_[i];
	}
	delete[] array_; //освобождаем изначальный участок памяти
	array_ = temp;   //меняем указатель
}

template <typename T>
stack<T>::stack() : capacity_(5), count_(0), array_{ new T[capacity_]; }
{}

template <typename T>
stack<T>::~stack()
{
	delete[] array_;  //освобождение памяти
}

template <typename T>
void stack<T>::push(T const &value)
{
	if (count_ >= capacity_)
	{
		reallocate();
	}
	array_[count_++] = value;
}

template <typename T>
T stack<T>::pop()
{
	if (count_ == 0) //проверяем размер стека
		throw runtime_error("Stack Empty!");
	--count_; 
	return array_[count_];
}

template <typename T>
size_t stack<T>::count() const // используем спецификатор const в конце функции т.к. метод ничего не изменяет,а только возвращает 
{
	return count_;
}

#endif /* STACK_HPP */
