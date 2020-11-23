using System;
using System.Collections.Generic;

namespace MathCalculator
{
    class Variable : Expr
    {
        public Variable(string val)
        {
            Value = val;
        }

        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
        {
            foreach (var obj in variableValues)
            {
                if (Value == obj.Key)
                    return obj.Value;
            }
            return 0;
        }

        public override string ToString()
            => Value.ToString();

        public string Value { get; }
    }
}
