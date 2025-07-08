#pragma once

#include <string>
#include <utility>
#include "Option/Option.hpp"

struct RequestKind {
    enum Kind { Get, Post, Delete };

    static const std::size_t n = 3;
    static const std::pair<Kind, const char*> pairs[n];

    Kind kind;

    // need defaut ctor for Option hmmm
    RequestKind() : kind(Get) {}
    RequestKind(Kind k);  // converting ctor
    static Option<RequestKind> parse(const std::string&);

    const char* repr() const;
};

// inherit from HttpMessage ? since start-line = request-line | response-line
class Request {
public:
    typedef RequestKind Kind;

    Kind kind;
};
