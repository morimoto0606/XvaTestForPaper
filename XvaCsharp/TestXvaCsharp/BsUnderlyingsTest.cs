using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

using System.Collections.Generic;
using System.Linq;
using XvaCsharp;

namespace TestXvaCsharp
{
    [TestClass]
    public class BsUnderlyingsTest
    {
        DateTime Today()
        {
            return new DateTime(2016, 12, 1);
        }
        DateTime tarGetDate()
        {
            return new DateTime(2017, 12, 3);
        }

        [TestMethod]
        public void GetState()
        {
            double mu = 0.1;
            double sigma = 0.3;
            double dt = 0.1;
            int maturityInyear = 10;
            int numOfPath = 100;
            double initialValue = 100;
            int seed = 1;
            var rand = new GaussianRandomNumber(
                seed);
            var und = new BsUnderlying(mu: mu, sigma: sigma, initialValue: initialValue,
                dt: dt, maturityInYear: maturityInyear, numOfPath: numOfPath, random: rand);

            double expected = initialValue;
            Assert.AreEqual(und.GetState(pathNo: 0, grid: 0), expected);

            expected = expected * Math.Exp((mu - 0.5 * sigma * sigma) * dt +
                sigma * und.BrownianMotion[0][1]);
            Assert.AreEqual(und.GetState(pathNo: 0, grid: 1), expected);

            expected = expected * Math.Exp((mu - 0.5 * sigma * sigma) * dt +
                sigma * und.BrownianMotion[0][2]);
            Assert.AreEqual(und.GetState(pathNo: 0, grid: 2), expected);
        }
    }
}
