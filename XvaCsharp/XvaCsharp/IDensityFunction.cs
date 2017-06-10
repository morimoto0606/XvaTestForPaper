using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XvaCsharp
{
    public interface IDensityFunction
    {
        double density(
            double tStart, double tEnd,
            double stateStart, double stateEnd);
    }
}
