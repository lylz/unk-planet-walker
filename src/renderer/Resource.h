#pragma once

class Resource
{
public:
	Resource(const char *name) : name_(name) {};
	inline const char *name() { return name_; };

private:
	const char *name_;
};
