#include "adminchecker.h"
#include "windows.h"
#include "memory"

namespace utils {

    bool islaunchedasadmin() {
        BOOL isAdmin = FALSE;
        PSID adminGroup = nullptr;

        SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;
        if (AllocateAndInitializeSid(&ntAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, //i have no idea 
            0, 0, 0, 0, 0, 0, &adminGroup)) {
            CheckTokenMembership(nullptr, adminGroup, &isAdmin);
            FreeSid(adminGroup);
        }

        return isAdmin;
    }

} 
