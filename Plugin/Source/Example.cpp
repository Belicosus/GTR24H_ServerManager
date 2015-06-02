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
#include <math.h>               // for atan2, sqrt
#include <stdio.h>              // for sample output


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
	//TODO: Add update code

	// Note: function is called twice per second now (instead of once per second in previous versions)
	FILE *fo = fopen("ExampleInternalsScoringOutput.txt", "a");
	if (fo != NULL)
	{
		// Print general scoring info
		fprintf(fo, "TrackName=%s\n", info.mTrackName);
		fprintf(fo, "Session=%d NumVehicles=%d CurET=%.3f\n", info.mSession, info.mNumVehicles, info.mCurrentET);
		fprintf(fo, "EndET=%.3f MaxLaps=%d LapDist=%.1f\n", info.mEndET, info.mMaxLaps, info.mLapDist);

		// Note that only one plugin can use the stream (by enabling scoring updates) ... sorry if any clashes result
		fprintf(fo, "START STREAM\n");
		const char *ptr = info.mResultsStream;
		while (*ptr != NULL)
			fputc(*ptr++, fo);
		fprintf(fo, "END STREAM\n");

		// New version 2 stuff
		fprintf(fo, "GamePhase=%d YellowFlagState=%d SectorFlags=(%d,%d,%d)\n", info.mGamePhase, info.mYellowFlagState,
			info.mSectorFlag[0], info.mSectorFlag[1], info.mSectorFlag[2]);
		fprintf(fo, "InRealtime=%d StartLight=%d NumRedLights=%d\n", info.mInRealtime, info.mStartLight, info.mNumRedLights);
		fprintf(fo, "PlayerName=%s PlrFileName=%s\n", info.mPlayerName, info.mPlrFileName);
		fprintf(fo, "DarkCloud=%.2f Raining=%.2f AmbientTemp=%.1f TrackTemp=%.1f\n", info.mDarkCloud, info.mRaining, info.mAmbientTemp, info.mTrackTemp);
		fprintf(fo, "Wind=(%.1f,%.1f,%.1f) OnPathWetness=%.2f OffPathWetness=%.2f\n", info.mWind.x, info.mWind.y, info.mWind.z, info.mOnPathWetness, info.mOffPathWetness);

		// Print vehicle info
		for (long i = 0; i < info.mNumVehicles; ++i)
		{
			VehicleScoringInfoV01 &vinfo = info.mVehicle[i];
			fprintf(fo, "Driver %d: %s\n", i, vinfo.mDriverName);
			fprintf(fo, " ID=%d Vehicle=%s\n", vinfo.mID, vinfo.mVehicleName);
			fprintf(fo, " Laps=%d Sector=%d FinishStatus=%d\n", vinfo.mTotalLaps, vinfo.mSector, vinfo.mFinishStatus);
			fprintf(fo, " LapDist=%.1f PathLat=%.2f RelevantTrackEdge=%.2f\n", vinfo.mLapDist, vinfo.mPathLateral, vinfo.mTrackEdge);
			fprintf(fo, " Best=(%.3f, %.3f, %.3f)\n", vinfo.mBestSector1, vinfo.mBestSector2, vinfo.mBestLapTime);
			fprintf(fo, " Last=(%.3f, %.3f, %.3f)\n", vinfo.mLastSector1, vinfo.mLastSector2, vinfo.mLastLapTime);
			fprintf(fo, " Current Sector 1 = %.3f, Current Sector 2 = %.3f\n", vinfo.mCurSector1, vinfo.mCurSector2);
			fprintf(fo, " Pitstops=%d, Penalties=%d\n", vinfo.mNumPitstops, vinfo.mNumPenalties);

			// New version 2 stuff
			fprintf(fo, " IsPlayer=%d Control=%d InPits=%d LapStartET=%.3f\n", vinfo.mIsPlayer, vinfo.mControl, vinfo.mInPits, vinfo.mLapStartET);
			fprintf(fo, " Place=%d VehicleClass=%s\n", vinfo.mPlace, vinfo.mVehicleClass);
			fprintf(fo, " TimeBehindNext=%.3f LapsBehindNext=%d\n", vinfo.mTimeBehindNext, vinfo.mLapsBehindNext);
			fprintf(fo, " TimeBehindLeader=%.3f LapsBehindLeader=%d\n", vinfo.mTimeBehindLeader, vinfo.mLapsBehindLeader);
			fprintf(fo, " Pos=(%.3f,%.3f,%.3f)\n", vinfo.mPos.x, vinfo.mPos.y, vinfo.mPos.z);

			// Forward is roughly in the -z direction (although current pitch of car may cause some y-direction velocity)
			fprintf(fo, " LocalVel=(%.2f,%.2f,%.2f)\n", vinfo.mLocalVel.x, vinfo.mLocalVel.y, vinfo.mLocalVel.z);
			fprintf(fo, " LocalAccel=(%.1f,%.1f,%.1f)\n", vinfo.mLocalAccel.x, vinfo.mLocalAccel.y, vinfo.mLocalAccel.z);

			// Orientation matrix is left-handed
			fprintf(fo, " [%6.3f,%6.3f,%6.3f]\n", vinfo.mOri[0].x, vinfo.mOri[0].y, vinfo.mOri[0].z);
			fprintf(fo, " [%6.3f,%6.3f,%6.3f]\n", vinfo.mOri[1].x, vinfo.mOri[1].y, vinfo.mOri[1].z);
			fprintf(fo, " [%6.3f,%6.3f,%6.3f]\n", vinfo.mOri[2].x, vinfo.mOri[2].y, vinfo.mOri[2].z);
			fprintf(fo, " LocalRot=(%.3f,%.3f,%.3f)\n", vinfo.mLocalRot.x, vinfo.mLocalRot.y, vinfo.mLocalRot.z);
			fprintf(fo, " LocalRotAccel=(%.2f,%.2f,%.2f)\n", vinfo.mLocalRotAccel.x, vinfo.mLocalRotAccel.y, vinfo.mLocalRotAccel.z);
		}

		// Delimit sections
		fprintf(fo, "\n");

		// Close file
		fclose(fo);
	}
}
