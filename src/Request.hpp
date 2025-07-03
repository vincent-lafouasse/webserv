#pragma once

class RequestKind {
    enum Kind {
        Get,
    };

    RequestKind(Kind k): kind(k) {} // converting ctor
    // RequestKind parse(string) ? add None variant ?

    Kind kind;
};

class Request {
   public:
    typedef RequestKind Kind;

    Kind kind;
};
