#include <map>
#include "Tests.h"


void restAPITest() {
    {
        bool ret = restAuthenticate(KServerAddr, KPort, KUserName, KPassword);

        if (!ret)
        {
            report();
        }
    }

    {
        std::map<string, string> projectMap;
        restListProjects(KServerAddr, KPort, KUserName, KPassword, projectMap);

        if (projectMap.size() == 0)
        {
            report();
        }
    }

    {
        std::unique_ptr<MetadataResponse> ret = restGetMeta(KServerAddr, KPort, KUserName, KPassword, KDefaultProject);
    }
}
