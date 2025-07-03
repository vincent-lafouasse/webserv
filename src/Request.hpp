#pragma once

struct RequestKind {
    enum Kind {
        Get,
    };

    Kind kind;

    RequestKind(Kind k): kind(k) {} // converting ctor
    // RequestKind parse(string) ? add None variant ? throw ?
    const char* repr() const {
        switch (kind) {
            case Get: return "GET";
            default: return "Not a valid verb";
        }
    }
};

class Request {
   public:
    typedef RequestKind Kind;

    Kind kind;
};
