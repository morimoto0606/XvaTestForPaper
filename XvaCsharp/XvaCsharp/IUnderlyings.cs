using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XvaCsharp
{
    public class UnderlyingUtil
    {
        public static int GetNumOfGrid(
            double dt, 
            int maturityInYear)
        {
            return (int)(Math.Truncate(maturityInYear/dt))+1;
        }
    }
    public interface IUnderlyings
    {
        double GetState(int pathNo, int Grid);
        int GetPathNum();
        double GetDt();
        int GetMaturityInYear();
        int GetNumOfGrid();
    }
}
