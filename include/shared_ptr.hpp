#include <iostream>
#include <stdexcept>

template <typename T>
class shared_ptr
{
public:
	explicit shared_ptr(T * ptr = nullptr); /*strong*/
	~shared_ptr(); /*noexcept*/
	shared_ptr(shared_ptr const & temp); /*noexcept*/
	auto operator =(shared_ptr const & temp)->shared_ptr &; /*noexcept*/
	shared_ptr(shared_ptr && temp); /*noexcept*/
	auto operator =(shared_ptr && temp)->shared_ptr &; /*noexcept*/
	auto swap(shared_ptr & temp)->void; /*noexcept*/
	auto get() const->T *; /*noexcept*/
	auto use_count() const->size_t; /*noexcept*/
	auto reset()->void; /*noexcept*/
	auto unique() const->bool; /*noexcept*/
	auto operator *() const->T &; /*strong*/
	auto operator ->() const->T *; /*strong*/
	auto operator bool() const->bool; /*noexcept*/
	auto owner_before(shared_ptr const & temp) const->bool; /*noexcept*/
private:
	T * ptr_;
	size_t * count_;
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
shared_ptr<T>::shared_ptr(T * ptr) : ptr_(ptr), count_(ptr == nullptr ? nullptr : new size_t(1)) {}

template <typename T>
shared_ptr<T>::~shared_ptr() {
	if (count_ && --(*count_) == 0 && ptr_) {
		delete ptr_;
		delete count_;
	}
}

template <typename T>
auto shared_ptr<T>::swap(shared_ptr & temp)->void {
	std::swap(temp.ptr_, ptr_);
	std::swap(temp.count_, count_);
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr const & temp) : ptr_(temp.ptr_), count_(temp.count_) {
	if (count_) {
		++(*count_);
	}
}

template <typename T>
auto shared_ptr<T>::operator =(shared_ptr const & temp)->shared_ptr & {
	if (this != &temp) {
		(shared_ptr<T>(temp)).swap(*this);
	}
	return *this;
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr && temp) : shared_ptr() { swap(temp); }

template <typename T>
auto shared_ptr<T>::operator =(shared_ptr && temp)->shared_ptr & {
	if (this != &temp) {
		swap(temp);
	}
	return *this;
}

template <typename T>
auto shared_ptr<T>::get() const->T * {return ptr_; }

template <typename T>
auto shared_ptr<T>::use_count() const->size_t { return (count_ == nullptr ? 0 : *count_); }

template <typename T>
auto shared_ptr<T>::reset()->void {
	if (count_ && --(*count_) == 0 && ptr_) {
		delete ptr_;
		delete count_;
	}
	ptr_ = nullptr;
	count_ = nullptr;
}

template <typename T>
auto shared_ptr<T>::unique() const->bool { return (use_count() == 1); }

template <typename T>
auto shared_ptr<T>::operator *() const->T & {
	if (ptr_ != nullptr) {
		return *ptr_;
	}
	else std::logic_error("ptr_=nullptr");
}

template <typename T>
auto shared_ptr<T>::operator ->() const->T * {
	if (ptr_ != nullptr) {
		return ptr_;
	}
	else std::logic_error("ptr_=nullptr");
}

template <typename T>
auto shared_ptr<T>::operator bool() const->bool { return !(ptr_ == nullptr); }

template <typename T>
auto shared_ptr<T>::owner_before(shared_ptr const & temp) const->bool {
	if (temp.ptr_ == ptr_) {
		return true;
	}
	else return false;
}

template<class T, class ...Args>
shared_ptr<T> make_shared(Args && ...args) {
	return shared_ptr<T>(new T(std::forward<Args>(args)...));
}
