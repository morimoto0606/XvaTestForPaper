using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MathNet.Numerics.Distributions;
namespace XvaCsharp
{
    public class NormalDensity : IDensityFunction
    {
        private double Mu { get; }
        private double Sigma { get; }
        public NormalDensity(
            double mu,
            double sigma)
        {
            Mu = mu;
            Sigma = sigma;
        }
        public double density(
            double tStart, double tEnd,
            double stateStart, double stateEnd)
        {
            double tau = tEnd - tStart;
            double mean = stateStart + Mu * tau;
            double stdev = Math.Sqrt(tau) * Sigma;
            return Normal.PDF(mean, stdev, stateEnd);
        }
    }
}
