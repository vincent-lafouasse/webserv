#pragma once

class RequestKind {
    enum Kind {
        Get,
    };

    RequestKind(Kind k): kind(k) {} // converting ctor

    Kind kind;
};

class Request {
   public:
    typedef RequestKind Kind;

    Kind kind;
};
