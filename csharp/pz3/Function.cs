using System;
using System.Collections.Generic;

namespace MathCalculator
{
   abstract class Function : Expr
    {
        public Function(Expr argument, Variables[] variables)
        {
            Argument = argument;
            //TODO
            // insert variables to Variables beacuse they're
            // function's variables
        }

        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
        {
            return 0.0;
        }

        public IEnumerable<string> Variables { get; }
        public bool IsConstant { get => Argument.IsConstant; }
        public bool IsPolynom { get => Argument.IsPolynom; }

        public Expr Argument { get; }
    }
}
