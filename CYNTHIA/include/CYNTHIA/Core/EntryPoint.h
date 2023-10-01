//
// Created by Samer Ali on 8/14/23.
//

#ifndef CYNTHIA_CORE_ENTRYPOINT_H
#define CYNTHIA_CORE_ENTRYPOINT_H

#include "CYNTHIA/Cynthia.h"

int main(int argc, char** argv)
{
	Cynthia::Log::Init();
	auto app = Cynthia::CreateApplication();
	app->Run();
	delete app;
}


#endif //CYNTHIA_CORE_ENTRYPOINT_H
