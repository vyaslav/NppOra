#pragma once
#include <occi.h>
#include <string>
#include <list>
#include <iostream>

using namespace oracle::occi;
using namespace std;

class V_OraDatabase
{
  private:
  Environment *env;
  Connection *conn;
  Statement *stmt;

  public:
  V_OraDatabase()
  {
      env = Environment::createEnvironment (Environment::DEFAULT);
      conn = env->createConnection ("vasa", "vasa", "//ItDogAnimal:1521/ORCL");
  }

  ~V_OraDatabase()
  {
	  env->terminateConnection (conn);
      Environment::terminateEnvironment (env);
  }

  std::list<std::string*>* getData()
  {
	std::list<std::string*>* strList = new std::list<std::string*>();
	string sqlStmt = "SELECT OWNER, OBJECT_NAME FROM ALB where object_id between 1 and 20";
	stmt = conn->createStatement (sqlStmt);
	ResultSet *rset;
	try{
	rset = stmt->executeQuery ();

	while (rset->next())
	{
		std::string* strarr = new std::string[2];
		strarr[0].assign(rset->getString(1));
		strarr[1].assign(rset->getString(2));
		strList->push_back(strarr);
	}
	}catch(SQLException ex)
	{
		int ora = ex.getErrorCode();
		std::string e(ex.getMessage());
	cout<<"Exception thrown for displayVersion";
	cout<<"Error number: ORA-"<<  ora<<e;
	}
	
	stmt->closeResultSet (rset);
	conn->terminateStatement (stmt);
	return strList;
  }

};