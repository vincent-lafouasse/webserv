#pragma once

#include <stdexcept>

class BadOptionAccessException : public std::runtime_error {
   public:
    BadOptionAccessException();
};

// meant mostly for value types
template <typename T>
class Option {
   public:
    Option(T value);  // converting constructor

    Option() /* noexcept */;
    Option(const Option&) /* noexcept */;
    Option& operator=(const Option&) /* noexcept */;
    ~Option() /* noexcept */;

    // mutators

    void reset();
    void swap(Option&);

    // accessors

    // const T* operator->() const; // UB on bad access
    // const T& operator*() const; // UB on bad access

    const T& get() const;  // throws on bad access
    const T& getOr(const T& defaultValue) const /* noexcept */;

    operator bool() const /* noexcept */;

    typedef BadOptionAccessException BadOptionAccessException;  // reexport

   private:
    T val;
    bool isSome;
};

// ----- Implementation

template <typename T>
Option<T>::Option(T value) : val(value), isSome(true) {}

template <typename T>
Option<T>::Option() : val(), isSome(false) {}

template <typename T>
Option<T>::Option(const Option& o) : val(o.val), isSome(o.iSome) {}

template <typename T>
Option<T>& Option<T>::operator=(const Option& o) {
    this->val = o.val;
    this->isSome = o.isSome;
    return *this;
}

template <typename T>
Option<T>::~Option() {}

// ----- Mutators

template <typename T>
void Option<T>::reset() {
    this->swap(Option<T>());
}

template <typename T>
void Option<T>::swap(Option& other) {
    // inelegant, dont care
    T tempT = this->val;
    bool tempBool = this->isSome;

    this->val = other.val;
    this->isSome = other.isSome;

    other.val = tempT;
    other.isSome = tempBool;
}

// ----- Accessors

template <typename T>
const T& Option<T>::get() const {
    if (this->isSome) {
        return this->val;
    } else {
        throw BadOptionAccessException();
    }
}

template <typename T>
const T& Option<T>::getOr(const T& defaultValue) const {
    if (this->isSome) {
        return this->val;
    } else {
        return defaultValue;
    }
}

template <typename T>
Option<T>::operator bool() const {
    return this->isSome;
}
