using System;
using System.Collections.Generic;

namespace MathCalculator
{
    abstract class UnaryOperation : Expr
    {
        public UnaryOperation(Expr argument)
        {
            Argument = argument;
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

    class Invert : UnaryOperation
    {
        public Invert(Expr argument) : base(argument) { }
        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
            => (new Mult(Argument, new Constant(-1))).Compute(variableValues);
        public override string ToString()
            => $"-({Argument})";
    }
}
