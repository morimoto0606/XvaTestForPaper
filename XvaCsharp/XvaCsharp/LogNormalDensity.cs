using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MathNet.Numerics.Distributions;

namespace XvaCsharp
{
    public class LogNormalDensity : IDensityFunction
    {

        private double Mu { get; }
        private double Sigma { get; }
        public LogNormalDensity(
            double mu, double sigma)
        {
            Mu = mu;
            Sigma = sigma;
        }
        public double density(
            double tStart, double tEnd,
            double stateStart, double stateEnd)
        {
            double mean = (Mu - 0.5 * Sigma * Sigma) * (tEnd - tStart);
            double sigma = Sigma * Math.Sqrt(tEnd - tStart);
            return LogNormal.PDF(mean, sigma, stateEnd / stateStart);
        }
    }
}
