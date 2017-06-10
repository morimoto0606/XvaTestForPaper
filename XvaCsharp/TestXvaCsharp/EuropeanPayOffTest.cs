using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using XvaCsharp;
namespace TestXvaCsharp
{
    [TestClass]
    public class EuropeanPayOffTest
    {
        [TestMethod]
        public void PayOff()
        {
            double strike = 100;
            var payoff = new European(strike, European.PayOffType.Call);
            double state = 120;
            Assert.AreEqual(state - strike, payoff.PayOff(state));
            state = 50;
            Assert.AreEqual(0, payoff.PayOff(state));
        }
    }
}
