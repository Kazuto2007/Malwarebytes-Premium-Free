#include "restart.h"
#include "iostream"
#include "thread"
#include "chrono"

namespace utils {

    void planrestart() {
        std::cout << "The system will restart in 1 minute. Type 'No' and press Enter to cancel the restart.\n";
        std::thread restartThread([]() {
            std::this_thread::sleep_for(std::chrono::seconds(60));
            system("shutdown /r /t 0");
            });
        restartThread.detach();
    }

    void cancelrestart() {
        system("shutdown /a"); // /a = stop/cancel
        std::cout << "Restart has been canceled.\n";
    }

} 