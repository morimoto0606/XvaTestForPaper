using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using XvaCsharp;
using System.Collections.Generic;
using System.Linq;
using MathNet.Numerics.Distributions;

namespace TestXvaCsharp
{
    [TestClass]
    public class StochasticMeshOperatorTest
    {
        [TestMethod]
        public void meshTest()
        {
            Func<double, double> f = (double x) => { return x * x; };
            var random = new GaussianRandomNumber(seed: 1);
            int numOfPath = 100;
            int numOfMesh = 100;
            double dt = 0.1;
            int maturityYear = 1;
            double mu = 0.1;
            double sigma = 0.3;
            var und = new BsUnderlying(initialValue: 100, sigma: sigma, mu: mu,
                dt: dt, maturityInYear: maturityYear, numOfPath: numOfPath, random: random);
            LogNormalDensity density = new LogNormalDensity(mu, sigma);
            var stochasticMesh = new StochasticMeshOperator(numOfMesh,
                und, density);
            int startGrid = 3;
            int endGrid = 10;

            double state = 0.1;
            double actual = stochasticMesh.Get(f, startGrid, endGrid)(state);
            double expected = 0.0;

            for (int i = 0; i < numOfPath; ++i)
            {
                double xEnd = und.GetLastState(i);
                IEnumerable<double> mesh
                    = from index in Enumerable.Range(0, numOfMesh)
                      select und.GetState(index, startGrid);
                double denominator = mesh.Select(
                    x => density.density(dt * startGrid,
                    maturityYear, x, xEnd)).Average();
                expected += f(xEnd) * density.density(startGrid * dt, endGrid * dt,
                    state, xEnd);
            }
            Assert.AreEqual(expected, actual, 1e-10);
        }
    }
}
