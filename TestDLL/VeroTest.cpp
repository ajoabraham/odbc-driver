#include "Tests.h"


void veroRestApiTest() {
	std::vector<string> holder;
	restListProjects(KServerAddr, KPort, KUserName, KPassword, holder);

	for (unsigned int i = 0; i < holder.size(); i++) {
		printf("Project name = %s", holder);
	}
}

void veroMakeSlugTest() {
	char test[100];
	strcpy(test, "abc dev ght   sdasd");
	makeSlug(test);
	printf("\n makeSlug %s\n", test);
}
