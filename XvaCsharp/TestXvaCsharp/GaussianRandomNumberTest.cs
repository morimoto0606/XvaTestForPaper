using System;
using System.Text;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using XvaCsharp;
using MathNet.Numerics.Statistics;


namespace TestXvaCsharp
{
    /// <summary>
    /// GaussianRandomNumberTest の概要の説明
    /// </summary>
    [TestClass]
    public class GaussianRandomNumberTest
    {
        public GaussianRandomNumberTest()
        {
            //
            // TODO: コンストラクター ロジックをここに追加します
            //
        }
        
        [TestMethod]
        public void GaussianRandom()
        {
            int size = 1000;
            var rand = new GaussianRandomNumber(0);
            var values = new List<double>();
            for (int i = 0; i < size; ++i)
            {
                values.Add(rand.Next());
            }
            double mean = values.Mean();
            double variance = values.Variance();
            double delta = 1 / Math.Sqrt(size);
            Assert.AreEqual(mean, 0.0, delta);
            Assert.AreEqual(variance, 1.0, 0.1);
            
        }
    }
}
