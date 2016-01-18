/*CWBoon 2015 */
/* C.W. Boon, G.T. Houlsby, S. Utili (2013).  A new contact detection algorithm for three-dimensional non-spherical particles.  Powder Technology, 248, pp 94-102. */
/* code for calling MOSEK was for ver 6.  Please uncomment if you have the licence */

#pragma once
#include<lib/serialization/Serializable.hpp>
#include<pkg/dem/PotentialParticle.hpp>
#include<pkg/common/Dispatching.hpp>
#include<pkg/common/Sphere.hpp>
#include<Python.h>
#include<Eigen/Core>
#include <stdio.h>

# if 0
#include <mosek.h> 
#include <math.h>
#include <stdlib.h>
#include <string.h>
#endif


class Ig2_PP_PP_ScGeom: public IGeomFunctor
{

	//protected:
		//static std::ofstream output;
#if 0
		std::string myfile;
		std::string Key;
		MSKrescodee mosekTaskEnv;
		MSKenv_t    mosekEnv;
	
#endif


	public :
		virtual bool go(const shared_ptr<Shape>& cm1, const shared_ptr<Shape>& cm2, const State& state1, const State& se32, const Vector3r& shift2, const bool& force, const shared_ptr<Interaction>& c);
		
		
		
		double evaluatePP(const shared_ptr<Shape>& cm1, const State& state1, const Vector3r newTrial);
		void getPtOnParticle2(const shared_ptr<Shape>& cm1, const State& state1, Vector3r previousPt, Vector3r normal, Vector3r& newlocalPoint);
		
		bool contactPtMosekF2(const shared_ptr<Shape>& cm1, const State& state1, const shared_ptr<Shape>& cm2, const State& state2, Vector3r &contactPt);
		
		bool customSolve(const shared_ptr<Shape>& cm1, const State& state1, const shared_ptr<Shape>& cm2, const State& state2, Vector3r &contactPt, bool warmstart);
		
		
		Vector3r getNormal(const shared_ptr<Shape>& cm1, const State& state1, const Vector3r newTrial);
		
		void BrentZeroSurf(const shared_ptr<Shape>& cm1, const State& state1, const Vector3r bracketA, const Vector3r bracketB, Vector3r& zero);
		
	



	/////////////////////////////////////////////////////////////////////////////////////////////////////



	YADE_CLASS_BASE_DOC_ATTRS_CTOR(Ig2_PP_PP_ScGeom,IGeomFunctor,"pp",		
			((double, accuracyTol, pow(10,-7),, "accuracy desired, tolerance criteria for SOCP"))
			((double,interactionDetectionFactor,1.0,,"bool to avoid granular ratcheting")),
			//((std::string,myfile,"./PotentialParticles"+"","string")),
			//timingDeltas=shared_ptr<TimingDeltas>(new TimingDeltas);
			//mosekTaskEnv = MSK_makeenv(&mosekEnv,NULL,NULL,NULL,NULL);
			//mosekTaskEnv = MSK_initenv(mosekEnv);
	);

	
	

	FUNCTOR2D(PotentialParticle,PotentialParticle);
	// needed for the dispatcher, even if it is symmetric
	DEFINE_FUNCTOR_ORDER_2D(PotentialParticle,PotentialParticle);
	DECLARE_LOGGER;

	
	

};

REGISTER_SERIALIZABLE(Ig2_PP_PP_ScGeom);


#ifdef __cplusplus
extern "C" {
#endif

/* LAPACK LU */	
	//int dgesv(int varNo, int varNo2, double *H, int varNo3, int *pivot, double* g, int varNo4, int info){
	 extern void dgesv_(const int *N, const int *nrhs, double *Hessian, const int *lda, int *ipiv, double *gradient, const int *ldb, int *info);
	// int ans;
	// dgesv_(&varNo, &varNo2, H, &varNo3, pivot,g, &varNo4, &ans);
	// return ans;
	//}	

/* LAPACK Cholesky */
	extern void dpbsv_(const char *uplo, const int *n, const int *kd, const int *nrhs, double *AB, const int *ldab, double *B, const int *ldb, int *info);

/* LAPACK QR */
	extern void dgels_(const char *Trans, const int *m, const int *n, const int *nrhs, double *A, const int *lda, double *B, const int *ldb, const double *work, const int *lwork, int *info);

	
/*BLAS */
	extern void dgemm_(const char *transA, const char *transB, const int *m, const int *n, const int *k, const double *alpha, double *A, const int *lda, double *B, const int *ldb, const double *beta, double *C, const int *ldc);

	extern void dgemv_(const char *trans, const int *m, const int *n, const double *alpha, double *A, const int *lda, double *x, const int *incx, const double *beta, double *y, const int *incy);
		
	extern void dcopy_(const int *N, double *x, const int *incx, double *y, const int *incy);

	extern double ddot_(const int *N, double *x, const int *incx, double *y, const int *incy);

	extern void daxpy_(const int *N, const double *da, double *dx, const int *incx, double *dy, const int *incy);

	extern void dscal_(const int *N, const double *alpha, double *x, const int *incx);


	void dsyev_(const char *jobz, const char *uplo, const int *N, double *A, const int *lda, double *W, double *work, int *lwork, int *info);


#ifdef __cplusplus
};
#endif




