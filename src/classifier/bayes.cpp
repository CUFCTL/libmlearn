/**
 * @file bayes.cpp
 *
 * Implementation of the naive Bayes classifier.
 */
#include <algorithm>
#include "bayes.h"
#include "lda.h"
#include "logger.h"
#include "matrix_utils.h"

/**
 * Construct a Bayes classifier.
 */
BayesLayer::BayesLayer()
{
}

/**
 * Compute the probability of a class for a
 * feature vector using the Bayes discriminant
 * function:
 *
 * g_i'(x) = -1/2 * (x - mu_i)' * S_i^-1 * (x - mu_i)
 */
precision_t bayes_prob(Matrix x, const Matrix& mu, const Matrix& S_inv)
{
	x -= mu;

	return -0.5f * (TRAN(x) * S_inv * x).elem(0, 0);
}

/**
 * Classify an observation using naive Bayes.
 *
 * @param X
 * @param Y
 * @param C
 * @param X_test
 * @return predicted labels of the test observations
 */
std::vector<DataLabel> BayesLayer::predict(const Matrix& X, const std::vector<DataEntry>& Y, const std::vector<DataLabel>& C, const Matrix& X_test)
{
	std::vector<Matrix> X_c = m_copy_classes(X, Y, C.size());
	std::vector<Matrix> U = m_class_means(X_c);
	std::vector<Matrix> S = m_class_scatters(X_c, U);

	// compute inverses of each S_i
	std::vector<Matrix> S_inv;

	for ( size_t i = 0; i < C.size(); i++ ) {
		S_inv.push_back(S[i].inverse("S_i_inv"));
	}

	// compute label for each test vector
	std::vector<DataLabel> Y_pred;

	for ( int i = 0; i < X_test.cols(); i++ ) {
		std::vector<precision_t> probs;

		// compute the Bayes probability for each class
		for ( size_t j = 0; j < C.size(); j++ ) {
			precision_t p = bayes_prob(X_test(i, i + 1), U[j], S_inv[j]);

			probs.push_back(p);
		}

		// select the class with the highest probability
		int index = max_element(probs.begin(), probs.end()) - probs.begin();

		Y_pred.push_back(C[index]);
	}

	return Y_pred;
}

/**
 * Print information about a Bayes classifier.
 */
void BayesLayer::print()
{
	log(LL_VERBOSE, "Bayes");
}
