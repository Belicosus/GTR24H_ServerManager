//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
//›                                                                         ﬁ
//› Module: Internals Example Source File                                   ﬁ
//›                                                                         ﬁ
//› Description: Declarations for the Internals Example Plugin              ﬁ
//›                                                                         ﬁ
//›                                                                         ﬁ
//› This source code module, and all information, data, and algorithms      ﬁ
//› associated with it, are part of CUBE technology (tm).                   ﬁ
//›                 PROPRIETARY AND CONFIDENTIAL                            ﬁ
//› Copyright (c) 1996-2008 Image Space Incorporated.  All rights reserved. ﬁ
//›                                                                         ﬁ
//›                                                                         ﬁ
//› Change history:                                                         ﬁ
//›   tag.2005.11.30: created                                               ﬁ
//›                                                                         ﬁ
//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ

#include "Example.hpp"          // corresponding header file
#include <stdio.h>              // for sample output
#include <string>
#include <ctime>


// plugin information

extern "C" __declspec(dllexport)
const char * __cdecl GetPluginName()                   { return("ServerManager - 2014.06.02"); }

extern "C" __declspec(dllexport)
PluginObjectType __cdecl GetPluginType()               { return(PO_INTERNALS); }

extern "C" __declspec(dllexport)
int __cdecl GetPluginVersion()                         { return(1); } // InternalsPluginV01 functionality

extern "C" __declspec(dllexport)
PluginObject * __cdecl CreatePluginObject()            { return((PluginObject *) new ExampleInternalsPlugin); }

extern "C" __declspec(dllexport)
void __cdecl DestroyPluginObject(PluginObject *obj)  { delete((ExampleInternalsPlugin *)obj); }


static short loopsSinceUpdate = 0;


void ExampleInternalsPlugin::Startup(long version)
{
	//TODO: Delete this from interface if we don't need it
}


void ExampleInternalsPlugin::Shutdown()
{
	//TODO: Delete this from interface if we don't need it
}


void ExampleInternalsPlugin::StartSession()
{
	//TODO: Delete this from interface if we don't need it
}


void ExampleInternalsPlugin::EndSession()
{
	//TODO: Delete this from interface if we don't need it
}


void ExampleInternalsPlugin::UpdateScoring(const ScoringInfoV01 &info)
{
	//Note: function is called twice per second now (instead of once per second in previous versions)
	//Personal note: The above seems to be wrong. Looks more like 5 times per second..

	loopsSinceUpdate++;
	if (loopsSinceUpdate >= 25) { //Updating every 5 seconds
		loopsSinceUpdate = 0;

		std::string values = "";
		for (long i = 0; i < info.mNumVehicles; ++i)
		{
			VehicleScoringInfoV01 &vinfo = info.mVehicle[i];
			if (values != "") {
				values = values + ";";
			}
			values = values + vinfo.mDriverName;
		}

		//Send/Write the data
		//TODO: Send over IPC
		//Currently just writing the info to a file
		char tab2[2048];
		strncpy(tab2, values.c_str(), sizeof(tab2));
		tab2[sizeof(tab2)-1] = 0;
		FILE *fo;
		fo = fopen("PlayersOnServer.txt", "a");
		if (fo != NULL)
		{
			fprintf(fo, "%d: %s\n", time(0), tab2);
			fclose(fo);
		}

		//Check for new messages that should be written to rFactor console
		//TODO: Check for IPC messages
		//TODO: Write messages to console
	}
}
