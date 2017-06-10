using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XvaCsharp
{
    public class European : IPayOff
    {
        public enum PayOffType
        {
            Call,
            Put,
        }
        private double Strike { get; }
        private double CallPut { get; }
        public European(
            double strike,
            PayOffType type)
        {
            Strike = strike;
            if (type == PayOffType.Call)
            {
                CallPut = 1.0;
            }
            else if (type == PayOffType.Put)
            {
                CallPut = -1.0;
            }
        } 
        public double PayOff(double state)
        {
            return CallPut * Math.Max(state - Strike, 0.0);
        }
    }
}
