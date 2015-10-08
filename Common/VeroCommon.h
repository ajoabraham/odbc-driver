#pragma once

#if defined(_KYLIN_REST_SERVICE)
#define REST_URI_PROJECTS				L"/kylin/api/projects"
#define REST_URI_TABLES_AND_COLUMNS		L"/kylin/api/tables_and_columns"
#define REST_URI_QUERY					L"/kylin/api/query"
#else
// TODO: 20151008 yulinwen: not done
#define REST_URI_PROJECTS				L"/api/v1/projects"
#define REST_URI_TABLES_AND_COLUMNS		L"/api/v1/projects/project-slug/schema"
#define REST_URI_QUERY					L"/api/v1/projects/project-slug/query"
#endif