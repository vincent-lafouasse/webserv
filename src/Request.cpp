#include "Request.hpp"

const std::pair<RequestKind::Kind, const char*>
    RequestKind::pairs[RequestKind::n] = {
        std::make_pair(RequestKind::Get, "GET"),
        std::make_pair(RequestKind::Post, "POST"),
        std::make_pair(RequestKind::Delete, "DELETE"),
};

RequestKind::RequestKind(Kind k) : kind(k) {}  // converting ctor

const char* RequestKind::repr() const {
    for (std::size_t i = 0; i < n; ++i) {
        const std::pair<Kind, const char*> pair = RequestKind::pairs[i];
        if (this->kind == pair.first) {
            return pair.second;
        }
    }
    return "Not a valid verb";
}

Option<RequestKind> RequestKind::parse(const std::string& s) {
    for (std::size_t i = 0; i < n; ++i) {
        const std::pair<Kind, const char*> pair = RequestKind::pairs[i];
        if (s == pair.second) {
            return Option<RequestKind>::Some(pair.first);
        }
    }
    return Option<RequestKind>::None();
}
