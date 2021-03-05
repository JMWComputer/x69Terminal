#include "Host.h"
#include "Shell/Shell.h"

#include <jclib/singleton.h>

namespace x69
{
	namespace impl
	{
		extern inline jcTerminal* terminal_v = nullptr;
		extern inline bool keep_open_v = false;
	};

	void set_terminal(jcTerminal* _terminal)
	{
		impl::terminal_v = _terminal;
	};
	jcTerminal*& terminal()
	{
		return impl::terminal_v;
	};

	bool keep_terminal_open()
	{
		return impl::keep_open_v;
	};
	void set_terminal_keep_open_flag(bool _to)
	{
		impl::keep_open_v = _to;
	};

};

namespace x69
{
	namespace
	{
		auto& get_shell()
		{
			return jc::get_singleton<Shell, struct x69Shell>();
		};
	};
	
	bool start_shell()
	{
		auto& _sh = get_shell();
		return true;
	};
	Shell& shell()
	{
		return get_shell();
	};

}

