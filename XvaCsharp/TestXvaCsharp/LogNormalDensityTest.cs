using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using XvaCsharp;
using MathNet.Numerics.Distributions;

namespace TestXvaCsharp
{
    [TestClass]
    public class LogNormalDensityTest
    {
        [TestMethod]
        public void pdf()
        {
            double mu = 0.0;
            double sigma = 1;
            double x = 1;
            double y = 1;
            double t = 1.0;
            double s = 0.0;

            double actual = new LogNormalDensity(
                mu, sigma).density(s, t, x, y);
            double expected = Normal.PDF(
                0, 1, (Math.Log(y / x) - (mu - 0.5 * sigma * sigma) * (t - s)) / (sigma * Math.Sqrt(t - s)));
            Assert.AreEqual(expected, actual, 1e-8);

            mu = 0.1;
            sigma = 0.43;
            x = 1;
            y = 2;
            t = 4.0;
            s = 2.0;

            actual = new LogNormalDensity(
                mu, sigma).density(s, t, x, y);
            expected = Normal.PDF(
                0, 1, (Math.Log(y / x) - (mu - 0.5 * sigma * sigma) * (t - s)) / (sigma * Math.Sqrt(t - s)))
                / (y* sigma * Math.Sqrt(t - s));
            Assert.AreEqual(expected, actual, 1e-8);
        }
    }
}
