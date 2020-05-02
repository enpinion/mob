#pragma once

#include "utility.h"

namespace builder
{

class env
{
public:
	enum flags
	{
		replace = 1,
		append,
		prepend
	};

	static env vs_x86();
	static env vs_x64();
	static env vs(arch a);

	env& append_path(const fs::path& p);
	env& append_path(const std::vector<fs::path>& v);
	env& set(std::string k, std::string v, flags f=replace);

	void set_from(const env& e);

	std::string get(const std::string& k) const;

	void* get_pointers() const;

private:
	using map = std::map<std::string, std::string>;

	map vars_;
	mutable std::string string_;

	void create() const;
	map::const_iterator find(const std::string& name) const;
};

}	// namespace


namespace builder::current_env
{

void set(
	const std::string& k,
	const std::string& v,
	env::flags f=env::replace);

env get();
std::string get(const std::string& k);

}	// namespace