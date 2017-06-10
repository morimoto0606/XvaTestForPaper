using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XvaCsharp
{
    public class Integration
    {
        public static double integrate(
            Func<int, double> f,
            int start,
            int end,
            List<double> dt)
        {
            double result = 0;
            for (int i = start; i < end; ++i)
            {
                result += f(i) * dt[i];
            }
            return result;
        }
    }
}
