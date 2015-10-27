#include <map>
#include <regex>
#include "Tests.h"

static const wchar_t* alwaysFailQueries[8] = {
	//L"(\\s)*CREATE(\\s)*LOCAL(\\s)*TEMPORARY(\\s)*TABLE(\\s)*\"XTableau_B_Connect\"(\\s)*\\((\\s)*\"COL\"(\\s)*INTEGER(\\s)*\\)(\\s)*ON(\\s)*COMMIT(\\s)*PRESERVE(\\s)*ROWS(\\s)*",
	//L"(\\s)*DROP(\\s)*TABLE(\\s)*\"XTableau_B_Connect\"(\\s)*",
	//L"(\\s)*INSERT(\\s)*INTO(\\s)*\"XTableau_C_Connect\"(\\s)*SELECT(\\s)*\\*(\\s)*FROM(\\s)*\\(SELECT(\\s)*1(\\s)*AS(\\s)*COL(\\s)*\\)(\\s)*AS(\\s)*CHECKTEMP(\\s)*LIMIT(\\s)*1(\\s)*",
	//L"(\\s)*DROP(\\s)*TABLE(\\s)*\"XTableau_C_Connect\"(\\s)*"

	L"(\\s)*CREATE(\\s)*LOCAL(\\s)*TEMPORARY(\\s)*TABLE(\\s)*\"(\\w)*\"(\\s)*\\((\\s)*\"COL\"(\\s)*INTEGER(\\s)*\\)(\\s)*ON(\\s)*COMMIT(\\s)*PRESERVE(\\s)*ROWS(\\s)*",
	L"(\\s)*DROP(\\s)*TABLE(\\s)*\"(\\w)*\"(\\s)*",
	L"(\\s)*SELECT(\\s)*TOP(\\s)*1(\\s)*\"COL\"(\\s)*FROM(\\s)*\\(SELECT(\\s)*1(\\s)*AS(\\s)*\"COL\"(\\s)*\\)(\\s)*AS(\\s)*\"CHECKTOP\"(\\s)*",
	L"(\\s)*SELECT(\\s)*\"SUBCOL\"(\\s)*AS(\\s)*\"COL\"(\\s)*FROM(\\s)*\\((\\s)*SELECT(\\s)*1(\\s)*AS(\\s)*\"SUBCOL\"(\\s)*\\)(\\s)*\"SUBQUERY\"(\\s)*GROUP(\\s)*BY(\\s)*1(\\s)*",
	L"(\\s)*SELECT(\\s)*\"SUBCOL\"(\\s)*AS(\\s)*\"COL\"(\\s)*FROM(\\s)*\\((\\s)*SELECT(\\s)*1(\\s)*AS(\\s)*\"SUBCOL\"(\\s)*\\)(\\s)*\"SUBQUERY\"(\\s)*GROUP(\\s)*BY(\\s)*\"COL\"(\\s)*",
	L"(\\s)*SELECT(\\s)*INSERT(\\s)*INTO(\\s)*\"(\\w)*\"(\\s)*SELECT(\\s)*\\*(\\s)*FROM(\\s)*\\(SELECT(\\s)*1(\\s)*AS(\\s)*COL(\\s)*\\)(\\s)*AS(\\s)*CHECKTEMP(\\s)*LIMIT(\\s)*1(\\s)*",
	L"(\\s)*SELECT(\\s)*\\*(\\s)*INTO(\\s)*\"(\\w)*\"(\\s)*FROM(\\s)*\\(SELECT(\\s)*1(\\s)*AS(\\s)*COL(\\s)*\\)(\\s)*AS(\\s)*CHECKTEMP(\\s)*LIMIT(\\s)*1(\\s)*",
	L"(\\s)*DROP(\\s)*TABLE(\\s)*\"(\\w)*\"(\\s)*"
};

static const wchar_t* alwaysSuccessQueries[3] = {
	L"(\\s)*SELECT(\\s)*1(\\s)*",
	L"(\\s)*SELECT(\\s)*\"COL\"(\\s)*FROM(\\s)*\\(SELECT(\\s)*1(\\s)*AS(\\s)*\"COL\"\\)(\\s)*AS(\\s)*\"SUBQUERY\"(\\s)*",
	L"(\\s)*SELECT(\\s)*\"COL\"(\\s)*FROM(\\s)*\\(SELECT(\\s)*1(\\s)*AS(\\s)*\"COL\"\\)(\\s)*AS(\\s)*\"CHECKTOP\"(\\s)*LIMIT(\\s)*1(\\s)*"
};

static const wchar_t* alwaysSuccessResults[3] = {
	L"{\"columnMetas\":[{\"isNullable\":2,\"displaySize\":11,\"label\":\"COL\",\"name\":\"COL\",\"schemaName\":\"\",\"catelogName\":\"\",\"tableName\":\"\",\"precision\":10,\"scale\":0,\"columnType\":4,\"columnTypeName\":\"int4\",\"writable\":true,\"caseSensitive\":false,\"autoIncrement\":false,\"searchable\":true,\"currency\":false,\"signed\":true,\"definitelyWritable\":false,\"readOnly\":false}],\"results\":[[\"1\"]],\"isResultsFlatten\":false,\"flattenResult\":null,\"flattenResultOriginalSize\":0,\"cubes\":null,\"affectedRowCount\":0,\"isException\":false,\"exceptionMessage\":null,\"duration\":0.002,\"partial\":false}",
	L"{\"columnMetas\":[{\"isNullable\":2,\"displaySize\":11,\"label\":\"COL\",\"name\":\"COL\",\"schemaName\":\"\",\"catelogName\":\"\",\"tableName\":\"\",\"precision\":10,\"scale\":0,\"columnType\":4,\"columnTypeName\":\"int4\",\"writable\":true,\"caseSensitive\":false,\"autoIncrement\":false,\"searchable\":true,\"currency\":false,\"signed\":true,\"definitelyWritable\":false,\"readOnly\":false}],\"results\":[[\"1\"]],\"isResultsFlatten\":false,\"flattenResult\":null,\"flattenResultOriginalSize\":0,\"cubes\":null,\"affectedRowCount\":0,\"isException\":false,\"exceptionMessage\":null,\"duration\":0.002,\"partial\":false}",
	L"{\"columnMetas\":[{\"isNullable\":2,\"displaySize\":11,\"label\":\"COL\",\"name\":\"COL\",\"schemaName\":\"\",\"catelogName\":\"\",\"tableName\":\"\",\"precision\":10,\"scale\":0,\"columnType\":4,\"columnTypeName\":\"int4\",\"writable\":true,\"caseSensitive\":false,\"autoIncrement\":false,\"searchable\":true,\"currency\":false,\"signed\":true,\"definitelyWritable\":false,\"readOnly\":false}],\"results\":[[\"1\"]],\"isResultsFlatten\":false,\"flattenResult\":null,\"flattenResultOriginalSize\":0,\"cubes\":null,\"affectedRowCount\":0,\"isException\":false,\"exceptionMessage\":null,\"duration\":0.002,\"partial\":false}"
};

static int findQuery(const wchar_t* sql, const wchar_t** regexs, int size) {
	for (int i = 0; i < size; ++i) {
		std::tr1::wregex rgx(regexs[i], regex_constants::icase);
		bool match = std::tr1::regex_search(sql, rgx);

		if (match) {
			return i;
		}
	}

	return -1;
}

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

    // rest meta
    std::unique_ptr<MetadataResponse> metaResponse = restGetMeta(KServerAddr, KPort, KUserName, KPassword, KDefaultProject);

	// rest query
	{
		std::unique_ptr<SQLResponse> y = restQuery(L"select Year", KServerAddr, KPort,
			KUserName, KPassword, KDefaultProject);

		if ((int)y->results.size() != 1) {
			report();
		}
	}
}

void veroProbeQueryTest() {
	//const wchar_t* sql = L"select * from dual";
	const wchar_t* sql = L"SELECT * INTO \"XTC_A_ABJHBFFB_CFDB_EAJC_IHDD_AADDADBFJCF_Connect\" FROM (SELECT 1 AS COL) AS CHECKTEMP LIMIT 1";

	int result = findQuery(sql, alwaysFailQueries, 7);

	cout << "ProbeQueryTest = " << result << endl;
	cout << "ProbeQueryTest = " << result << endl;
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
