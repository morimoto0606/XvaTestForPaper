using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using XvaCsharp;

namespace TestXvaCsharp
{
    [TestClass]
    public class XvaPricerTest
    {
        [TestMethod]
        public void XvaPricer()
        {
            double dt = 1;
            int maturityInYear = 10;
            int numOfPath = 100;
            var random = new GaussianRandomNumber(seed: 1);
            var underlying = new BsUnderlying(
                initialValue: 100, sigma: 0.3, mu: 0.0, dt: dt,
                maturityInYear: maturityInYear,
                numOfPath: numOfPath,
                random: random);
            var payoff = new European(strike: 105, type: European.PayOffType.Call);
            //ContinuationValue
            //Integrate()
        }
    }
}
