﻿//------------------------------------------------------------------------------
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
    Vector3         pos;
    Vector3         nrm;
    Vector3         flux;
    Vector3         f; 
    double          r2;
    unsigned int    n; 
    int             idx;
};


#endif//__HITRECORD_H__