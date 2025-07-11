#include "chainload.h"

#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

void chainload(HMODULE hModule) {
	TCHAR module_path[MAX_PATH] = {};
	GetModuleFileName(hModule, module_path, MAX_PATH);
	auto library_list = std::wifstream(
		// Strip the filename part from the module path, then add 'chainload.txt'.
		std::filesystem::path(module_path).remove_filename().append("chainload.txt")
	);
	std::vector<std::wstring> modules;

	if (library_list.is_open())
	{
		// Read filenames from each line and call LoadLibrary.
		for (std::wstring line; std::getline(library_list, line);)
		{
			// Treat lines starting with '#' as comments.
			if (line.empty() || line.starts_with(L"#"))
				continue;
			modules.push_back(line);
		}
	}
	
	for (const auto& mod : modules)
		LoadLibrary(mod.c_str());
}