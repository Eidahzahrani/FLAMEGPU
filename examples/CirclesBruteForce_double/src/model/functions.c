/*
* Copyright 2011 University of Sheffield.
* Author: Dr Paul Richmond
* Contact: p.richmond@sheffield.ac.uk (http://www.paulrichmond.staff.shef.ac.uk)
*
* University of Sheffield retain all intellectual property and
* proprietary rights in and to this software and related documentation.
* Any use, reproduction, disclosure, or distribution of this software
* and related documentation without an express license agreement from
* University of Sheffield is strictly prohibited.
*
* For terms of licence agreement please attached licence or view licence
* on www.flamegpu.com website.
*
*/

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "header.h"

#define radius 2.0


__FLAME_GPU_FUNC__ int move(xmachine_memory_Circle* xmemory)
{

	xmemory->x += xmemory->fx;
	xmemory->y += xmemory->fy;

	return 0;
}


#endif // #ifndef _FUNCTIONS_H_
