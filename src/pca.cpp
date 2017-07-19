/**
 * @file pca.cpp
 *
 * Implementation of PCA (Turk and Pentland, 1991).
 */
#include "logger.h"
#include "math_utils.h"
#include "pca.h"
#include "timer.h"

/**
 * Construct a PCA layer.
 *
 * @param n1
 */
PCALayer::PCALayer(int n1)
{
	this->n1 = n1;
}

/**
 * Compute the principal components of a matrix X, which
 * consists of observations in rows or columns. The observations
 * should also be mean-subtracted.
 *
 * The principal components of a matrix are the eigenvectors of
 * the covariance matrix.
 *
 * @param X
 * @param y
 * @param c
 */
void PCALayer::compute(const Matrix& X, const std::vector<DataEntry>& y, int c)
{
	// if n1 = -1, use default value
	int n1 = (this->n1 == -1)
		? min(X.rows(), X.cols())
		: this->n1;

	timer_push("PCA");

	if ( X.rows() > X.cols() ) {
		timer_push("compute surrogate of covariance matrix L");

		Matrix L = TRAN(X) * X;

		timer_pop();

		timer_push("compute eigendecomposition of L");

		Matrix V;
		L.eigen("V", "D", n1, V, this->D);

		timer_pop();

		timer_push("compute principal components");

		this->W = X * V;

		timer_pop();
	}
	else {
		timer_push("compute covariance matrix C");

		Matrix C = X * TRAN(X);

		timer_pop();

		timer_push("compute eigendecomposition of C");

		C.eigen("W_pca", "D", n1, this->W, this->D);

		timer_pop();
	}

	timer_pop();
}

/**
 * Project a matrix X into the feature space of a PCA layer.
 *
 * @param X
 */
Matrix PCALayer::project(const Matrix& X)
{
	return TRAN(this->W) * X;
}

/**
 * Save a PCA layer to a file.
 *
 * @param file
 */
void PCALayer::save(std::ofstream& file)
{
	this->W.save(file);
}

/**
 * Load an PCA layer from a file.
 *
 * @param file
 */
void PCALayer::load(std::ifstream& file)
{
	this->W.load(file);
}

/**
 * Print information about a PCA layer.
 */
void PCALayer::print()
{
	log(LL_VERBOSE, "PCA");
	log(LL_VERBOSE, "  %-20s  %10d", "n1", this->n1);
}
