/*************************************************************************
*  Copyright (C) 2004 by Olivier Galizzi                                 *
*  olivier.galizzi@imag.fr                                               *
*                                                                        *
*  This program is free software; it is licensed under the terms of the  *
*  GNU General Public License v2 or later. See file LICENSE for details. *
*************************************************************************/

#pragma once

#include<yade/lib-serialization/Serializable.hpp>
#include<yade/lib-multimethods/Indexable.hpp>

// the geometry through which the body will interact:
// - planet emitting gravity has just radius of influence
// - magnet has also just volume of influence
// - for tetrahedrons we can use sphere tree or sweptshpere volume
//
// in general we can use it to initialize interaction

#define BV_FUNCTOR_CACHE

class BoundingVolumeEngineUnit;

class InteractingGeometry : public Serializable, public Indexable
{
	public :
		InteractingGeometry(){diffuseColor=Vector3r(1,1,1);}
		Vector3r diffuseColor;	// FIXME - why here? and then - why no
					// bool wire; even though GeometricalModel has bool wire ?

		#ifdef BV_FUNCTOR_CACHE
			shared_ptr<BoundingVolumeEngineUnit> boundFunctor;
		#endif

/// Serialization
	REGISTER_ATTRIBUTES(Serializable,(diffuseColor));
	REGISTER_CLASS_AND_BASE(InteractingGeometry,Serializable Indexable);
/// Indexable
	REGISTER_INDEX_COUNTER(InteractingGeometry);
};
REGISTER_SERIALIZABLE(InteractingGeometry);
