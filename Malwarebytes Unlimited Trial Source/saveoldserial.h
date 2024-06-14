#pragma once

#include "string"

namespace utils {
    bool saveoldguid(const std::wstring& guid, const std::wstring& filePath);
    std::string wstringToString(const std::wstring& wstr);
}
