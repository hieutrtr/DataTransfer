#pragma once
#include "MySQLController.h"
class CCentrolizeMySQLController : public CMySQLController
{
public:
	CCentrolizeMySQLController(void);
	~CCentrolizeMySQLController(void);

	virtual bool Find() = 0;
	virtual bool Insert() = 0;
};