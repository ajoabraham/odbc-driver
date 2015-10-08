#include "Tests.h"

void restAPITest() {
    {
        bool ret = restAuthenticate ( KServerAddr, KPort, KUserName, KPassword );
        
        if ( !ret )
        { report(); }
    }

    {
        std::vector<string> holder;
        restListProjects ( KServerAddr, KPort, KUserName, KPassword, holder );
        
        if ( holder.size() == 0 )
        { report(); }
    }

    {
        std::unique_ptr<MetadataResponse> ret = restGetMeta ( KServerAddr, KPort, KUserName, KPassword, KDefaultProject );
    }

}

void veroRestApiTest() {
	std::vector<string> holder;
	restListProjects(KServerAddr, KPort, KUserName, KPassword, holder);

	for (unsigned int i = 0; i < holder.size(); i++) {
		printf("Project name = %s", holder);
	}
}