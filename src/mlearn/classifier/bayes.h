/**
 * @file classifier/bayes.h
 *
 * Interface definitions for the naive Bayes classifier.
 */
#ifndef BAYES_H
#define BAYES_H

#include "mlearn/classifier/classifier.h"



namespace ML {



class BayesLayer : public ClassifierLayer {
public:
	BayesLayer() = default;

	void compute(const Matrix& X, const std::vector<int>& y, int c);
	std::vector<int> predict(const Matrix& X_test);
	void print() const;

private:
	float prob(Matrix x, const Matrix& mu, const Matrix& S_inv);

	std::vector<Matrix> _mu;
	std::vector<Matrix> _S_inv;
};



}

#endif