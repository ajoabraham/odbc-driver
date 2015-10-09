#include <map>
#include "Tests.h"


void veroRestApiTest() {
	std::map<string, string> projectMap;
	restListProjects(KServerAddr, KPort, KUserName, KPassword, projectMap);

	for (std::map<string, string>::iterator i = projectMap.begin(); i != projectMap.end(); i++) {
		cout << "Project = " << (*i).first << endl;
	}
}


void veroMakeUriTest() {
	char project[100];

	strcpy(project, "abc def");
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
