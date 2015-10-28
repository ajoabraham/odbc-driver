#include "JsonConverter.h"

#define ASSIGN_IF_NOT_NULL(x,y,z)  if(!y.is_null())x=y.z
#define x_ASSIGN_IF_NOT_NULL(x,y,z)  if(!y.is_null())x=wstring2string(y.z)


TableMeta* TableMetaFromJSON(web::json::value & object) {
	TableMeta* result = new TableMeta();

	x_ASSIGN_IF_NOT_NULL(result->TABLE_CAT, object[U("table_CAT")], as_string());
	x_ASSIGN_IF_NOT_NULL(result->TABLE_SCHEM, object[U("table_SCHEM")], as_string());
	x_ASSIGN_IF_NOT_NULL(result->TABLE_NAME, object[U("table_NAME")], as_string());
	x_ASSIGN_IF_NOT_NULL(result->TABLE_TYPE, object[U("table_TYPE")], as_string());
	x_ASSIGN_IF_NOT_NULL(result->REMARKS, object[U("remarks")], as_string());
	x_ASSIGN_IF_NOT_NULL(result->TYPE_CAT, object[U("type_CAT")], as_string());
	x_ASSIGN_IF_NOT_NULL(result->TYPE_SCHEM, object[U("type_SCHEM")], as_string());
	x_ASSIGN_IF_NOT_NULL(result->TYPE_NAME, object[U("type_NAME")], as_string());
	x_ASSIGN_IF_NOT_NULL(result->SELF_REFERENCING_COL_NAME, object[U("self_REFERENCING_COL_NAME")], as_string());
	x_ASSIGN_IF_NOT_NULL(result->REF_GENERATION, object[U("ref_GENERATION")], as_string());

	return result;
}

ColumnMeta* ColumnMetaFromJSON(
    web::json::value &table_object, 
    web::json::value &column_object,
    unsigned int count) {
	ColumnMeta* result = new ColumnMeta();

    x_ASSIGN_IF_NOT_NULL(result->TABLE_CAT, column_object[U("table_CAT")], as_string());
    x_ASSIGN_IF_NOT_NULL(result->TABLE_SCHEM, column_object[U("table_SCHEM")], as_string());
    x_ASSIGN_IF_NOT_NULL(result->TABLE_NAME, column_object[U("table_NAME")], as_string());
    x_ASSIGN_IF_NOT_NULL(result->COLUMN_NAME, column_object[U("column_NAME")], as_string());
	//ASSIGN_IF_NOT_NULL(result->DATA_TYPE ,column_object[U("data_TYPE")], as_integer());
    x_ASSIGN_IF_NOT_NULL(result->TYPE_NAME, column_object[U("type_NAME")], as_string());
    ASSIGN_IF_NOT_NULL(result->COLUMN_SIZE, column_object[U("column_SIZE")], as_integer());
    ASSIGN_IF_NOT_NULL(result->BUFFER_LENGTH, column_object[U("buffer_LENGTH")], as_integer());
    ASSIGN_IF_NOT_NULL(result->DECIMAL_DIGITS, column_object[U("decimal_DIGITS")], as_integer());
    ASSIGN_IF_NOT_NULL(result->NUM_PREC_RADIX, column_object[U("num_PREC_RADIX")], as_integer());
    ASSIGN_IF_NOT_NULL(result->NULLABLE, column_object[U("nullable")], as_integer());
    x_ASSIGN_IF_NOT_NULL(result->REMARKS, column_object[U("remarks")], as_string());
    x_ASSIGN_IF_NOT_NULL(result->COLUMN_DEF, column_object[U("column_DEF")], as_string());
	//ASSIGN_IF_NOT_NULL(result->SQL_DATA_TYPE ,column_object[U("sql_DATA_TYPE")], as_integer());
    ASSIGN_IF_NOT_NULL(result->SQL_DATETIME_SUB, column_object[U("sql_DATETIME_SUB")], as_integer());
    ASSIGN_IF_NOT_NULL(result->CHAR_OCTET_LENGTH, column_object[U("char_OCTET_LENGTH")], as_integer());
    ASSIGN_IF_NOT_NULL(result->ORDINAL_POSITION, column_object[U("ordinal_POSITION")], as_integer());
    x_ASSIGN_IF_NOT_NULL(result->IS_NULLABLE, column_object[U("is_NULLABLE")], as_string());
    x_ASSIGN_IF_NOT_NULL(result->SCOPE_CATLOG, column_object[U("scope_CATLOG")], as_string());
    x_ASSIGN_IF_NOT_NULL(result->SCOPE_SCHEMA, column_object[U("scope_SCHEMA")], as_string());
    x_ASSIGN_IF_NOT_NULL(result->SCOPE_TABLE, column_object[U("scope_TABLE")], as_string());
    x_ASSIGN_IF_NOT_NULL(result->IS_AUTOINCREMENT, column_object[U("iS_AUTOINCREMENT")], as_string());

    if (!column_object[U("source_DATA_TYPE")].is_null()) {
        result->SOURCE_DATA_TYPE = (short)column_object[U("source_DATA_TYPE")].as_integer();
	}

	// the orig value passed from REST is java.sql.Types, we convert it to SQL Type
    if (!column_object[U("data_TYPE")].is_null()) {
        result->DATA_TYPE = JDBC2ODBC(column_object[U("data_TYPE")].as_integer());
	}

    if (!column_object[U("sql_DATA_TYPE")].is_null()) {
        result->SQL_DATA_TYPE = JDBC2ODBC(column_object[U("sql_DATA_TYPE")].as_integer());
	}

	return result;
}

std::unique_ptr<MetadataResponse> MetadataResponseFromJSON(web::json::value & object) {
	std::unique_ptr<MetadataResponse> result(new MetadataResponse());

	web::json::array& tableMetaArray = object.as_array();

    for (auto outer_iter = tableMetaArray.begin(); outer_iter != tableMetaArray.end(); ++outer_iter) {
        result->tableMetas.push_back(TableMetaFromJSON(*outer_iter));
        web::json::value& columns = (*outer_iter)[U("columns")];
		web::json::array& columnsMetaArray = columns.as_array();

        unsigned int inner_count = 1;
		for (auto inner_iter = columnsMetaArray.begin(); inner_iter != columnsMetaArray.end(); ++inner_iter) {
            result->columnMetas.push_back(ColumnMetaFromJSON(*outer_iter, *inner_iter, inner_count));
            inner_count++;
		}
	}

	return result;
}

SelectedColumnMeta* SelectedColumnMetaFromJSON(web::json::value & object) {
	SelectedColumnMeta* result = new SelectedColumnMeta();
	ASSIGN_IF_NOT_NULL(result->isAutoIncrement, object[U("autoIncrement")], as_bool());
	ASSIGN_IF_NOT_NULL(result->isCaseSensitive, object[U("caseSensitive")], as_bool());
	ASSIGN_IF_NOT_NULL(result->isSearchable, object[U("searchable")], as_bool());
	ASSIGN_IF_NOT_NULL(result->isCurrency, object[U("currency")], as_bool());
	ASSIGN_IF_NOT_NULL(result->isNullable, object[U("isNullable")], as_integer());
	ASSIGN_IF_NOT_NULL(result->isSigned, object[U("signed")], as_bool());
	ASSIGN_IF_NOT_NULL(result->displaySize, object[U("displaySize")], as_integer());
	x_ASSIGN_IF_NOT_NULL(result->label, object[U("label")], as_string());
	x_ASSIGN_IF_NOT_NULL(result->name, object[U("name")], as_string());
	x_ASSIGN_IF_NOT_NULL(result->schemaName, object[U("schemaName")], as_string());
	x_ASSIGN_IF_NOT_NULL(result->catelogName, object[U("catelogName")], as_string());
	x_ASSIGN_IF_NOT_NULL(result->tableName, object[U("tableName")], as_string());
	ASSIGN_IF_NOT_NULL(result->precision, object[U("precision")], as_integer());
	ASSIGN_IF_NOT_NULL(result->scale, object[U("scale")], as_integer());
	//ASSIGN_IF_NOT_NULL(result->columnType ,object[U("columnType")], as_integer());
	x_ASSIGN_IF_NOT_NULL(result->columnTypeName, object[U("columnTypeName")], as_string());
	ASSIGN_IF_NOT_NULL(result->isReadOnly, object[U("readOnly")], as_bool());
	ASSIGN_IF_NOT_NULL(result->isWritable, object[U("writable")], as_bool());
	ASSIGN_IF_NOT_NULL(result->isDefinitelyWritable, object[U("definitelyWritable")], as_bool());

	if (!object[U("columnType")].is_null()) {
		result->columnType = JDBC2ODBC(object[U("columnType")].as_integer());
	}

	return result;
}

void constructUnflattenResults(SQLResponse* result, web::json::value& o_results) {
	if (o_results.is_null())
	{
		return;
	}

	for (auto iter = o_results.as_array().begin(); iter != o_results.as_array().end(); ++iter) {
		SQLRowContent* row = new SQLRowContent();

		for (auto jter = iter->as_array().begin(); jter != iter->as_array().end(); ++jter) {
			if (jter->is_null()) {
				wstring emptyCell;
				row->contents.push_back(emptyCell);
			}

			else {
				row->contents.push_back((jter->as_string()));
			}
		}

		result->results.push_back(row);
	}
}

std::unique_ptr<SQLResponse> SQLResponseFromJSON(web::json::value & object) {
	std::unique_ptr<SQLResponse> result(new SQLResponse());
	web::json::value& o_columnMetas = object[U("columnMetas")];
	web::json::value& o_results = object[U("results")];
	result->affectedRowCount = object[U("affectedRowCount")].as_integer();

    if (!object[U("isException")].is_null()) {
        result->isException = object[U("isException")].as_bool();
    } else if (!object[U("exception")].is_null()) {
        result->isException = object[U("exception")].as_bool();
    }

	ASSIGN_IF_NOT_NULL(result->exceptionMessage, object[U("exceptionMessage")], as_string());

	if (!o_columnMetas.is_null()) {
		for (auto iter = o_columnMetas.as_array().begin(); iter != o_columnMetas.as_array().end(); ++iter) {
			result->columnMetas.push_back(SelectedColumnMetaFromJSON(*iter));
		}
	}

	constructUnflattenResults(result.get(), o_results);
	return result;
}

std::unique_ptr<ErrorMessage> ErrorMessageFromJSON(web::json::value & object) {
	std::unique_ptr<ErrorMessage> result(new ErrorMessage());
	ASSIGN_IF_NOT_NULL(result->url, object[U("url")], as_string());
	ASSIGN_IF_NOT_NULL(result->msg, object[U("exception")], as_string());
	return result;
}