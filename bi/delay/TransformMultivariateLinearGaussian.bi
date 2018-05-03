/*
 * Linear transformation of a multivariate Gaussian variate.
 */
class TransformMultivariateLinearGaussian(A:Real[_,_],
    x:DelayMultivariateGaussian, c:Real[_]) <
    TransformMultivariateLinear(A, c) {
  /**
   * Random variate.
   */
  x:DelayMultivariateGaussian <- x;
}

function TransformMultivariateLinearGaussian(A:Real[_,_],
    x:DelayMultivariateGaussian, c:Real[_]) ->
    TransformMultivariateLinearGaussian {
  m:TransformMultivariateLinearGaussian(A, x, c);
  return m;    
}
