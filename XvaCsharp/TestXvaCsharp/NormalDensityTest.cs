using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using XvaCsharp;
using MathNet.Numerics.Distributions;

namespace TestXvaCsharp
{
    [TestClass]
    public class NormalDensityTest
    {
        [TestMethod]
        public void normalDensity()
        {
            double mu = 0.0;
            double sigma = 1;
            double x = 0.0;
            double y = 0.0;
            double t = 1.0;
            double s = 0.0;

            double actual = new NormalDensity(
                mu, sigma).density(s, t, x, y) * Math.Sqrt(Math.PI*2);
            double expected = Normal.PDF(
                0, 1, (y - x - mu * (t - s)) / (sigma * Math.Sqrt(t - s)))
                * Math.Sqrt(Math.PI * 2);
            Assert.AreEqual(expected, actual, 1e-8);

            mu = 0.0;
            sigma = 1;
            x = 0.0;
            y = 0.0;
            t = 1.0;
            s = 0.0;
            actual = new NormalDensity(
                mu, sigma).density(s, t, x, y) * Math.Sqrt(Math.PI * 2);
            expected = Normal.PDF(
                0, 1, (y - x - mu * (t - s)) / (sigma * Math.Sqrt(t - s)))
                * Math.Sqrt(Math.PI * 2);
            Assert.AreEqual(expected, actual, 1e-8);
        }
    }
}
