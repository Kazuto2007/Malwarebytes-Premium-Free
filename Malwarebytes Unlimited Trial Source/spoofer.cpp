#include "spoofer.h"
#include "windows.h"
#include "iostream"
#include "objbase.h" //what the sigma

namespace utils {
    std::wstring getguid() {
        HKEY hKey;
        const wchar_t* subKey = L"SOFTWARE\\Microsoft\\Cryptography";
        wchar_t guidBuffer[39];
        DWORD bufferSize = sizeof(guidBuffer);

        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, subKey, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
            if (RegQueryValueEx(hKey, L"MachineGuid", nullptr, nullptr, (LPBYTE)guidBuffer, &bufferSize) == ERROR_SUCCESS) {
                RegCloseKey(hKey);
                return std::wstring(guidBuffer);
            }
            RegCloseKey(hKey);
        }
        return L"";
    }
    bool spoofguid() {
        HKEY hKey;
        const wchar_t* subKey = L"SOFTWARE\\Microsoft\\Cryptography";
        const wchar_t* valueName = L"MachineGuid";

        LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, subKey, 0, KEY_SET_VALUE, &hKey);
        if (result != ERROR_SUCCESS) {
            std::cerr << "Failed to open registry  " << result << std::endl;
            return false;
        }

        GUID newGuid;
        result = CoCreateGuid(&newGuid);
        if (result != S_OK) {
            std::cerr << "Failed to spoof GUID" << result << std::endl;
            RegCloseKey(hKey);
            return false;
        }

        wchar_t guidString[39];  
        int guidStringLength = StringFromGUID2(newGuid, guidString, 39);
        if (guidStringLength == 0) {
            std::cerr << "Failed to save the GUID as in an string" << std::endl;
            RegCloseKey(hKey);
            return false;
        }
        result = RegSetValueEx(hKey, valueName, 0, REG_SZ, reinterpret_cast<const BYTE*>(guidString), (guidStringLength * sizeof(wchar_t)));
        if (result != ERROR_SUCCESS) {
            std::cerr << "Failed to spoof registry value " << result << std::endl;
            RegCloseKey(hKey);
            return false;
        }
        RegCloseKey(hKey);
        std::wcout << L"new guid: " << guidString << std::endl;
        return true;
    }
} 
