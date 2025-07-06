#pragma once

// meant mostly for value types
template <typename T>
class Option {
public:
    Option(T value);

    Option();
    Option(const Option&);
    Option& operator=(const Option&);
    ~Option();

private:
    T val;
    bool isSome;
};

// ----- Implementation

template <typename T>
Option<T>::Option(T value): val(value), isSome(true) {}

template <typename T>
Option<T>::Option(): val(), isSome(false) {}

template <typename T>
Option<T>::Option(const Option& o): val(o.val), isSome(o.iSome) {}

template <typename T>
Option<T>& Option<T>::operator=(const Option& o) {
    this->val = o.val;
    this->isSome = o.isSome;
    return *this;
}

template <typename T>
Option<T>::~Option() {}
