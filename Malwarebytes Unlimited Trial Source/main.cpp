#include "iostream"
#include "saveoldserial.h"
#include "adminchecker.h"
#include "spoofer.h"
#include "string"
#include "restart.h"

void waitforuser();

int main() {
    if (!utils::islaunchedasadmin()) {
        std::cerr << "Relaunch as Admin" << std::endl;
        std::cout << "press something to exit";
        std::cin.ignore();  
        return 1;
    }

    std::wstring currentGuid = utils::getguid();
    if (currentGuid.empty()) {
        std::cerr << "Failed to read current GUID." << std::endl;
        return 1;
    }
    std::wcout << L"Current Guid: " << currentGuid << std::endl;
    std::cout << "Do you want to save the current Guid before updating?  (yes or no) : ";
    std::string response;
    std::getline(std::cin, response);
    if (response == "yes" || response == "Yes" || response == "y" || response == "Y") {
        std::wstring filePath = L"myoldguid.txt";
        if (utils::saveoldguid(currentGuid, filePath)) {
            std::wcout << L"Old Guid saved in myoldguid.txt " << filePath << std::endl;
        }
        else {
            std::cerr << "Failed to save old Guid." << std::endl;    }
    }

    if (utils::spoofguid()) {
        std::cout << "Guid updated successfully." << std::endl;
        utils::planrestart();
    }
    else {
        std::cerr << "Failed to update Guid." << std::endl;
    }

    waitforuser();

    return 0;
}

void waitforuser() {
    std::cout << "Restarting in 1 Minute necessary for trial reset! To cancel enter No: ";
    std::string answer;
    std::getline(std::cin, answer);
    if (answer == "No" || answer == "no") {
        utils::cancelrestart();
    }

    std::cout << "continue ? press enter";
    std::cin.ignore();  
}
