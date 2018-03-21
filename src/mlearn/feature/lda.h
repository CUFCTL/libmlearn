/**
 * @file feature/lda.h
 *
 * Interface definitions for the LDA feature layer.
 */
#ifndef LDA_H
#define LDA_H

#include "mlearn/feature/feature.h"



namespace ML {



class LDALayer : public FeatureLayer {
public:
	LDALayer(int n1, int n2);
	LDALayer() : LDALayer(-1, -1) {}

	void compute(const Matrix& X, const std::vector<int>& y, int c);
	Matrix project(const Matrix& X);

	void save(IODevice& file) const;
	void load(IODevice& file);
	void print() const;

private:
	int _n1;
	int _n2;
	Matrix _W;
};



}

#endif
