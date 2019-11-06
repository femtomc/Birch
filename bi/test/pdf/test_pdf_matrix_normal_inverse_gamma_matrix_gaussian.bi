/*
 * Test matrix normal-inverse-gamma Gaussian pdf evaluations.
 */
program test_pdf_matrix_normal_inverse_gamma_matrix_gaussian(
    N:Integer <- 10000, B:Integer <- 10000, S:Integer <- 10) {
  m:TestMatrixNormalInverseGammaMatrixGaussian;
  m.play();
  test_pdf(m.marginal(), 5, 2, N, B, S);
}
