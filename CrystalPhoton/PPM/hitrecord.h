//------------------------------------------------------------------------------
// File : hitrecord.h
// Desc : Hit Record.
//------------------------------------------------------------------------------

#ifndef __HITRECORD_H__
#define __HITRECORD_H__

//------------------------------------------------------------------------------
// Incluldes
//------------------------------------------------------------------------------
#include "math_util.h"


////////////////////////////////////////////////////////////////////////////////
// HitRecord structure
////////////////////////////////////////////////////////////////////////////////
struct HitRecord
{
    Crystal::Math::Vector3dd         pos;
    Crystal::Math::Vector3dd         nrm;
    Crystal::Math::Vector3dd         flux;
    Crystal::Math::Vector3dd         f;
    double          r2;
    unsigned int    n; 
    int             idx;
};


#endif//__HITRECORD_H__
