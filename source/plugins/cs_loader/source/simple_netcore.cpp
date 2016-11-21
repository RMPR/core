#include <cs_loader/simple_netcore.h>

#include <cs_loader/netcore.h>
#if defined(__linux) | defined( linux)
#include <cs_loader/netcore_linux.h>
#else
#include <cs_loader/netcore_win.h>
#endif

#include <sstream>
#include <iostream>
#include <fstream>
#include <ostream>
#include <stdlib.h>
netcore_handle simple_netcore_create() {
#if defined(__linux) | defined( linux)

	netcore_linux * netcore_inp = new netcore_linux();
#else
	netcore_win *netcore_inp = new netcore_win();
#endif

	if (netcore_inp->start()) {
		return (netcore_handle)netcore_inp;
	}
	else
	{
		return (netcore_handle)0;
	}
}

reflect_function * simple_netcore_get_functions(netcore_handle handle, int *count) {
	netcore * core = (netcore*)handle;

	return core->get_functions(count);
}

void simple_netcore_destroy(netcore_handle handle) {
	netcore * core = (netcore*)handle;
	delete core;
}

void  simple_netcore_load_script(netcore_handle handle, const char *path, const char* file) {
	netcore * core = (netcore*)handle;

	(void)file;

	std::ifstream inFile;
	inFile.open(path);

	std::stringstream strStream;
	strStream << inFile.rdbuf();
	std::string str = strStream.str();

	if (core->load_source((char*)str.c_str())) {

	}
}

void  simple_netcore_invoke(netcore_handle handle, const char *func, parameters *params, size_t count) {
	netcore * core = (netcore*)handle;
	if (params == NULL) {
		core->execute((char*)func);
	}
	else
	{
		core->execute_with_params((char*)func, params, count);
	}
}