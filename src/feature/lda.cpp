/**
 * @file lda.cpp
 *
 * Implementation of LDA (Belhumeur et al., 1996; Zhao et al., 1998).
 */
#include "lda.h"
#include "logger.h"
#include "matrix_utils.h"
#include "pca.h"
#include "timer.h"

/**
 * Construct an LDA layer.
 *
 * @param n1
 * @param n2
 */
LDALayer::LDALayer(int n1, int n2)
{
	this->n1 = n1;
	this->n2 = n2;
}

/**
 * Compute the LDA features of a matrix X.
 *
 * @param X
 * @param y
 * @param c
 */
void LDALayer::compute(const Matrix& X, const std::vector<DataEntry>& y, int c)
{
	// if n1 = -1, use default value
	int n1 = (this->n1 == -1)
		? X.cols() - c
		: this->n1;

	// if n2 = -1, use default value
	int n2 = (this->n2 == -1)
		? c - 1
		: this->n2;

	if ( n1 <= 0 ) {
		log(LL_ERROR, "error: training set is too small for LDA");
		exit(1);
	}

	timer_push("LDA");

	timer_push("compute eigenfaces");

	PCALayer pca(n1);
	pca.compute(X, y, c);
	Matrix P_pca = pca.project(X);

	timer_pop();

	timer_push("compute scatter matrices S_b and S_w");

	std::vector<Matrix> X_c = m_copy_classes(P_pca, y, c);
	std::vector<Matrix> U = m_class_means(X_c);
	Matrix S_b = m_scatter_between(X_c, U);
	Matrix S_w = m_scatter_within(X_c, U);

	timer_pop();

	timer_push("compute eigendecomposition of S_b and S_w");

	Matrix S_w_inv = S_w.inverse("inv(S_w)");
	Matrix J = S_w_inv * S_b;

	Matrix W_fld;
	Matrix J_eval;
	J.eigen("W_fld", "J_eval", n2, W_fld, J_eval);

	timer_pop();

	timer_push("compute Fisherfaces");

	this->W = pca.W * W_fld;

	timer_pop();

	timer_pop();
}

/**
 * Project a matrix X into the feature space of an LDA layer.
 *
 * @param X
 */
Matrix LDALayer::project(const Matrix& X)
{
	return TRAN(this->W) * X;
}

/**
 * Save an LDA layer to a file.
 *
 * @param file
 */
void LDALayer::save(std::ofstream& file)
{
	this->W.save(file);
}

/**
 * Load an LDA layer from a file.
 *
 * @param file
 */
void LDALayer::load(std::ifstream& file)
{
	this->W.load(file);
}

/**
 * Print information about an LDA layer.
 */
void LDALayer::print()
{
	log(LL_VERBOSE, "LDA");
	log(LL_VERBOSE, "  %-20s  %10d", "n1", this->n1);
	log(LL_VERBOSE, "  %-20s  %10d", "n2", this->n2);
}
