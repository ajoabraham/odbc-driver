#include "Tests.h"


void veroRestApiTest() {
	std::vector<string> holder;
	restListProjects(KServerAddr, KPort, KUserName, KPassword, holder);

	for (unsigned int i = 0; i < holder.size(); i++) {
		std::string projectName = holder.at(i);
		cout << "Project = " << projectName;
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
