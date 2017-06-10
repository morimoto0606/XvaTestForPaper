using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XvaCsharp
{
    class Program
    {
        static void Main(string[] args)
        {
            var rand = new Random(0);
            for (int i = 1; i < 100; ++i)
            {
                Console.WriteLine(rand.NextDouble());
            }
            Console.Write(0);

        }
    }
}
