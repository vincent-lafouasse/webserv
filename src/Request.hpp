#pragma once

class Request {
public:
	class RequestKind {
		enum Kind {
			Get,
		};
	};

	typedef RequestKind Kind;

	Kind kind;
};
