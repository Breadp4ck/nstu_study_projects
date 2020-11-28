using System;
using System.Collections.Generic;

namespace MathCalculator
{
    abstract class Function : Expr
    {
        public Function(Expr argument)
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

    class Asin : Function
    {
        public Asin(Expr argument) : base(argument) { }
        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
            => Math.Asin(Argument.Compute(variableValues));
        public override string ToString()
            => $"asin({Argument})";
    }

    class Acos : Function
    {
        public Acos(Expr argument) : base(argument) { }
        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
            => Math.Acos(Argument.Compute(variableValues));
        public override string ToString()
            => $"acos({Argument})";
    }

    class Atan : Function
    {
        public Atan(Expr argument) : base(argument) { }
        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
            => Math.Atan(Argument.Compute(variableValues));
        public override string ToString()
            => $"atan({Argument})";
    }

    class Actg : Function
    {
        public Actg(Expr argument) : base(argument) { }
        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
            => Math.Atan(1 / Argument.Compute(variableValues));
        public override string ToString()
            => $"actg({Argument})";
    }
}
