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
    Option();
    Option(const Option&);
    Option& operator=(const Option&);
    ~Option();

    Option(T value);  // converting constructor
    static Option None();
    static Option Some(T val);

    // mutators
    void reset();
    void swap(Option&);

    // accessors
    const T& unwrap() const;  // checked, throws on bad access
    const T& unwrapOr(const T& defaultValue) const /* noexcept */;
    const T* operator->() const;  // unchecked, UB on bad access
    const T& operator*() const;   // in reality, T()

    bool is() const;

    typedef ::BadOptionAccessException BadOptionAccessException;  // reexport

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
Option<T>::Option(const Option& o) : val(o.val), isSome(o.isSome) {}

template <typename T>
Option<T>& Option<T>::operator=(const Option& o) {
    this->val = o.val;
    this->isSome = o.isSome;
    return *this;
}

template <typename T>
Option<T>::~Option() {}

template <typename T>
Option<T> Option<T>::None() {
    return Option<T>();
}

template <typename T>
Option<T> Option<T>::Some(T val) {
    return Option<T>(val);
}

// ----- Mutators

template <typename T>
void Option<T>::reset() {
    this->swap(None());
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
const T& Option<T>::unwrap() const {
    if (this->isSome) {
        return this->val;
    } else {
        throw BadOptionAccessException();
    }
}

template <typename T>
const T& Option<T>::unwrapOr(const T& defaultValue) const {
    if (this->isSome) {
        return this->val;
    } else {
        return defaultValue;
    }
}

template <typename T>
const T& Option<T>::operator*() const {
    return this->val;
}

template <typename T>
const T* Option<T>::operator->() const {
    return &this->val;
}

template <typename T>
bool Option<T>::is() const {
    return this->isSome;
}
