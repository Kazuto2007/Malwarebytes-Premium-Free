#include "saveoldserial.h"
#include "fstream"
#include "iostream"
namespace utils {
    std::string wstringToString(const std::wstring& wstr) {
        std::string str(wstr.begin(), wstr.end());
        return str;
    }
    bool saveoldguid(const std::wstring& guid, const std::wstring& filePath) {
        std::ofstream outFile(filePath);
        if (outFile) {
            // translate
            std::string guidStr = wstringToString(guid);

            outFile << guidStr << std::endl;
            outFile.close();
            std::wcout << L"GUID saved to file: " << filePath << std::endl;
            return true;
        }
        std::cerr << "Failed to save old GUID to file." << std::endl;
        return false;
    }

}