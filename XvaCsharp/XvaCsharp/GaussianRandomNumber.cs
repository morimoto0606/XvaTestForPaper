using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MathNet.Numerics.Distributions;
namespace XvaCsharp
{
    public class GaussianRandomNumber
    {
        private int Seed { get; set; }
        private Random Rand { get; }
        public List<double> MemoryOfRandm { get; }
        public GaussianRandomNumber(
            int seed)  
        {
            Seed = seed;
            MemoryOfRandm = new List<double>();
            Rand = new Random(seed);
        }
        public double Next()
        {
            double value = Rand.NextDouble();
            MemoryOfRandm.Add(value);
            return Normal.InvCDF(0, 1, value);
        }
    }
}
