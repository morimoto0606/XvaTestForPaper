using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XvaCsharp
{
    public class BsUnderlying : IUnderlyings
    {
        private List<List<double>> State { get; }
        private double Dt { get; }
        private int MaturityInYear { get; }
        private int NumOfPath { get; }
        public List<List<double>> BrownianMotion { get; }
        public BsUnderlying(
            double initialValue,
            double sigma,
            double mu,
            double dt,
            int maturityInYear,
            int numOfPath,
            GaussianRandomNumber random)
        {
            NumOfPath = NumOfPath;
            Dt = dt;
            MaturityInYear = maturityInYear;

            State = new List<List<double>>();
            BrownianMotion = new List<List<double>>();
            int numOfGrid = UnderlyingUtil.GetNumOfGrid(dt, maturityInYear);
            Func<Tuple<List<double>, List < double >>> onePath = () => {
                List<double> path = new List<double>();
                List<double> bm = new List<double>();
                path.Add(initialValue);
                bm.Add(0);
                for (int i = 1; i < numOfGrid; ++i)
                {
                    double dw = Math.Sqrt(dt) * random.Next();
                    double state = path[i - 1] * Math.Exp(
                        (mu - 0.5 * sigma * sigma) * dt + sigma * dw);
                    bm.Add(dw);
                    path.Add(state);
                }
                return new Tuple<List<double>, List<double>>(
                    path, bm);
            };
            for (int i = 0; i < numOfPath; ++i)
            {
                var stateAndBm = onePath();
                State.Add(stateAndBm.Item1);
                BrownianMotion.Add(stateAndBm.Item2);
            }
        }        
        public double GetLastState(int pathNo)
        {
            return State[pathNo].Last();
        }
        public double GetState(int pathNo, int grid)
        {
            return State[pathNo][grid];
        }
        public double GetDt()
        {
            return Dt;
        }
        public int GetMaturityInYear()
        {
            return MaturityInYear;
        }
        public int GetNumOfGrid()
        {
            return UnderlyingUtil.GetNumOfGrid(
                Dt, MaturityInYear);
        }
        public int GetPathNum()
        {
            return NumOfPath; 
        }
    }
}
