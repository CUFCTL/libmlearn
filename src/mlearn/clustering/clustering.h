/**
 * @file clustering/clustering.h
 *
 * Interface definitions for the abstract clustering layer.
 */
#ifndef CLUSTERING_H
#define CLUSTERING_H

#include <vector>
#include "mlearn/math/matrix.h"
#include "mlearn/util/iodevice.h"



namespace ML {



class ClusteringLayer : public IODevice {
public:
	virtual ~ClusteringLayer() {};
	virtual int fit(const std::vector<Matrix>& X) = 0;

	virtual float entropy() const = 0;
	virtual float log_likelihood() const = 0;
	virtual int num_clusters() const = 0;
	virtual int num_parameters() const = 0;
	virtual int num_samples() const = 0;
	virtual const std::vector<int>& output() const = 0;
};



}

#endif