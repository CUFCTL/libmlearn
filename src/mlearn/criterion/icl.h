/**
 * @file clustering/icl.h
 *
 * Interface definitions for the ICL layer.
 */
#ifndef ICL_H
#define ICL_H

#include "mlearn/criterion/criterion.h"



namespace ML {



class ICLLayer : public CriterionLayer {
public:
	float compute(ClusteringLayer *layer);
	void print() const;
};



}

#endif