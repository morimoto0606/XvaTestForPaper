using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using XvaCsharp;
using System.Collections.Generic;
using System.Linq;

namespace TestXvaCsharp
{
    [TestClass]
    public class IntegrationTest
    {
        [TestMethod]
        public void integrate()
        {
            int numOfGrid = 1000;
            double end = 1;
            double delta = end / numOfGrid;
            Func<int, double> f = (int i) => Math.Sin(delta * i * Math.PI);
            var dt = Enumerable.Range(0, numOfGrid).Select(x => delta).ToList();
            double actual = Integration.integrate(f, 0, numOfGrid, dt);
            double expected = 2.0 / Math.PI;
            Assert.AreEqual(expected, actual, delta);
        }
    }
}
 