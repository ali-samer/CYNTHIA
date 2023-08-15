//
// Created by Samer Ali on 8/14/23.
//

#ifndef CYNTHIA_SRC_CYNTHIA_CORE_ENTRYPOINT_H
#define CYNTHIA_SRC_CYNTHIA_CORE_ENTRYPOINT_H


#include "CYNTHIA/Cynthia.h"


int main(int argc, char** argv)
{
	Cynthia::Log::Init();
	CY_CORE_WARN("Initialized Log!");
	CY_CORE_INFO("INFO: "  );
	CY_CORE_TRACE("TRACE: ");
	CY_CORE_ERROR("ERROR: ");
	CY_CORE_CRITICAL("CRITICAL: ");
	CY_CORE_DEBUG("DEBUG: ");
	int a = 5;
	CY_INFO("Hello! Var {0}", a);

	auto app = Cynthia::CreateApplication();
	app->Run();
	delete app;
}


#endif //CYNTHIA_SRC_CYNTHIA_CORE_ENTRYPOINT_H
