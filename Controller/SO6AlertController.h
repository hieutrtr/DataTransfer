#pragma once
#include "CentrolizeMySQLController.h"

class CSO6AlertController : public CCentrolizeMySQLController
{
public:
	CSO6AlertController(void);
	~CSO6AlertController(void);

	bool Find();
	bool Insert();
};