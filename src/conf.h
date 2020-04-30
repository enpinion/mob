#pragma once

namespace builder
{

struct conf
{
	static bool verbose();
	static bool dry();
};

struct third_party
{
	static fs::path sevenz();
	static fs::path jom();
	static fs::path patch();
	static fs::path git();
	static fs::path cmake();
	static fs::path perl();
	static fs::path devenv();
	static fs::path msbuild();
};

struct prebuilt
{
	static bool boost();
};

struct versions
{
	static const std::string& vs();
	static const std::string& vs_year();
	static const std::string& vs_toolset();
	static const std::string& sdk();
	static const std::string& sevenzip();
	static const std::string& zlib();
	static const std::string& boost();
	static const std::string& boost_vs();
	static const std::string& python();
	static const std::string& fmt();
	static const std::string& gtest();
	static const std::string& libbsarch();
	static const std::string& libloot();
	static const std::string& libloot_hash();
	static const std::string& openssl();
	static const std::string& bzip2();
};

struct paths
{
	static fs::path prefix();
	static fs::path cache();
	static fs::path patches();
	static fs::path build();

	static fs::path install();
	static fs::path install_bin();
	static fs::path install_libs();
	static fs::path install_pdbs();

	static fs::path install_dlls();
	static fs::path install_loot();

	static fs::path program_files_x86();
	static fs::path temp_dir();

	static fs::path temp_file();
};

fs::path find_third_party_directory();

}	// namespace