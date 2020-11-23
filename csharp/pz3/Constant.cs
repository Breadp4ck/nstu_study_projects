using System;
using System.Collections.Generic;

namespace MathCalculator
{
    class Constant : Expr
    {
        public Constant(double val)
        {
            Value = val;
        }

        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
            => Value;

        public override string ToString()
            => Value.ToString();

        public double Value { private set; get; }
    }
}
