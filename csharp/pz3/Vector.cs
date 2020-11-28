using System;
using System.Linq;
using System.Collections.Generic;

namespace MathCalculator
{
    class Vector : Expr
    {
        public Vector(Expr[] val)
        {
            Value = val;
        }

        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
        {
            //for (int i = 0; i < Length; i++)
            //    Value[i] = Compute(variableValues);
            return 0.0;
        }

        public override string ToString()
        {
            string vectorString = "{ ";
            for(int i = 0; i < Length-1; i++)
                vectorString += $"{ Value[i] }, ";
            // Remove K O C T bl ji b
            vectorString += $"{ Value[Length-1] }" + " }";

            return vectorString;
        }


        public Expr[] Value { get; }
        public int Length { get => Value.Length; }
    }
}
