/******************************************************************************

GHAAS Water Balance/Transport Model V3.0
Global Hydrologic Archive and Analysis System
Copyright 1994-2014, UNH - CCNY/CUNY

MDIrrRefET.c

dominink.wisser@unh.edu

*******************************************************************************/

#include <stdio.h>
#include <cm.h>
#include <MF.h>
#include <MD.h>

static int _MDOutIrrRefEvapotransID = MFUnset;

enum { MDinput, MDhamon, MDfao };

int MDIrrRefEvapotransDef () {
	int optID = MFUnset;
	const char *optStr, *optName = MDOptIrrReferenceET;
	const char *options [] = { MDInputStr, "Hamon", "FAO", (char *) NULL };

	if (_MDOutIrrRefEvapotransID != MFUnset) return (_MDOutIrrRefEvapotransID);

	if ((optStr = MFOptionGet (optName)) != (char *) NULL) optID = CMoptLookup (options,optStr,true);

	MFDefEntering ("Irrigation Reference Evapotranspiration");
	if (MDSPackChgDef () == CMfailed) return (CMfailed);

	switch (optID) {
		case MDinput: _MDOutIrrRefEvapotransID = MFVarGetID (MDVarIrrRefEvapotrans, "mm", MFInput, MFFlux, false); break;
		case MDhamon: _MDOutIrrRefEvapotransID = MDIrrRefEvapotransHamonDef (); break;
		case MDfao:   _MDOutIrrRefEvapotransID = MDIrrRefEvapotransFAODef   (); break;
		default: MFOptionMessage (optName, optStr, options); return (CMfailed);
	}
	MFDefLeaving ("Irrigation Reference Evapotranspiration");
	return (_MDOutIrrRefEvapotransID);
}
