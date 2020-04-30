#include "pch.h"
#include "conf.h"
#include "net.h"
#include "op.h"
#include "tools.h"
#include "utility.h"
#include "tasks/tasks.h"

namespace builder
{




















template <class Tool, class... Args>
class dummy : public basic_task<dummy<Tool, Args...>>
{
public:
	dummy(Args&&... args)
		: basic_task("dummy"), args_(std::forward<Args>(args)...)
	{
	}


protected:
	void do_fetch() override
	{
		std::apply([&](auto&&... args){ run_tool<Tool>(args...); }, args_);
	}

private:
	std::tuple<Args...> args_;
};


template <class Tool, class... Args>
std::unique_ptr<dummy<Tool, Args...>> make_dummy(Args&&... args)
{
	using Dummy = dummy<Tool, Args...>;
	return std::unique_ptr<Dummy>(new Dummy(std::forward<Args>(args)...));
}


BOOL WINAPI signal_handler(DWORD) noexcept
{
	info("caught sigint");
	task::interrupt_all();
	return TRUE;
}


struct curl_init
{
	curl_init()
	{
		curl_global_init(CURL_GLOBAL_ALL );
	}

	~curl_init()
	{
		curl_global_cleanup();
	}
};


int run(int argc, char** argv)
{
	try
	{
		::SetConsoleCtrlHandler(signal_handler, TRUE);

		curl_init curl;
		vcvars();
		prepend_to_path(find_third_party_directory() / "bin");

		add_task<sevenz>();
		add_task<zlib>();
		add_task<fmt>();
		add_task<gtest>();
		add_task<libbsarch>();
		add_task<libloot>();
		add_task<openssl>();
		add_task<libffi>();
		add_task<bzip2>();
		add_task<python>();
		add_task<boost>();

		if (argc > 1)
			return run_task(argv[1]) ? 0 : 1;

		run_all_tasks();

		return 0;
	}
	catch(bailed)
	{
		error("bailing out");
		return 1;
	}
}

} // namespace


int main(int argc, char** argv)
{
	int r = builder::run(argc, argv);
	builder::dump_logs();
	//std::cin.get();
	return r;
}