using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XvaCsharp
{
    public class StochasticMeshOperator
    {
        private IUnderlyings Underlying { get; }
        private IDensityFunction DensityFunction { get;}
        private int NumOfMesh { get; }
        public StochasticMeshOperator(
            int numOfMesh,
            IUnderlyings underlying,
            IDensityFunction densityFunction)
        {
            NumOfMesh = numOfMesh > underlying.GetPathNum()
                ? numOfMesh : underlying.GetPathNum();
            DensityFunction = densityFunction;
            Underlying = underlying;
        }
        public Func<double, double> Get(
            Func<double, double> f,
            int startGrid,
            int endGrid)
        {
            double dt = Underlying.GetDt();

            Func<double, double> denominator = y =>
            {
                IEnumerable<double> mesh
                    = from pathNo in Enumerable.Range(0, NumOfMesh)
                      select Underlying.GetState(pathNo, startGrid);

                return mesh.Select(
                    x => DensityFunction.density(
                    dt * startGrid, dt * endGrid, x, y))
                    .Average();
            };
            Func<double, double> result = x =>
            {
                IEnumerable<double> mesh
                = from pathNo in Enumerable.Range(0, NumOfMesh)
                  select Underlying.GetState(pathNo, endGrid);

                double func = mesh.Select(
                    y => f(y) * DensityFunction.density(
                        dt * startGrid, dt * endGrid,
                        x, y) / denominator(y)).Average();
                return func;
            };
            return result;
        }
    }
}
