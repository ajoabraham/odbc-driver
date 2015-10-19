#include <map>
#include "Tests.h"


void veroRestApiTest() {
    // rest authenticate
    bool ret = restAuthenticate(KServerAddr, KPort, KUserName, KPassword);
    if (!ret) {
        report();
    }

    // rest projects
	std::map<string, string> projectMap;
	restListProjects(KServerAddr, KPort, KUserName, KPassword, projectMap);

	for (std::map<string, string>::iterator i = projectMap.begin(); i != projectMap.end(); i++) {
		cout << "Project = " << (*i).first << endl;
	}

    /*
    // rest meta
    std::unique_ptr<MetadataResponse> metaResponse = restGetMeta(KServerAddr, KPort, KUserName, KPassword, KDefaultProject);
    */
}


void veroMakeUriTest() {
	char project[100];

	strcpy(project, "yulins_project");
	makeSlug(project);
	
	cout << "\n";
	cout << "Project make slug = " << project << "\n";

	std::wstringstream metaUri = makeMetaUri(project);
	std::wstringstream queryUri = makeQueryUri(project);

	std::unique_ptr<char[]> metaUriPtr = wchar2char(metaUri.str().c_str());
	std::unique_ptr<char[]> queryUriPtr = wchar2char(queryUri.str().c_str());

	cout << "Meta uri = " << metaUriPtr.get() << "\n";
	cout << "Query uri = " << queryUriPtr.get() << "\n";
}
