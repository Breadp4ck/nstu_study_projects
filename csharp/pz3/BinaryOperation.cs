using System;
using System.Collections.Generic;

namespace MathCalculator
{

    abstract class BinaryOperation : Expr
    {
        public BinaryOperation(Expr argument1, Expr argument2)
        {
            Argument1 = argument1;
            Argument2 = argument2;
        }

        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
        {
            return 0.0;
        }

        public IEnumerable<string> Variables { get; }
        public bool IsConstant { get => Argument1.IsConstant && Argument2.IsConstant; }
        public bool IsPolynom { get => Argument1.IsPolynom || Argument2.IsPolynom; }

        public Expr Argument1 { get; }
        public Expr Argument2 { get; }
    }

    class Add : BinaryOperation
    {
        public Add(Expr argument1, Expr argument2) : base(argument1, argument2) { }
        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
            => Argument1.Compute(variableValues) + Argument2.Compute(variableValues);
    }

    class Sub : BinaryOperation
    {
        public Sub(Expr argument1, Expr argument2) : base(argument1, argument2) { }
        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
            => Argument1.Compute(variableValues) - Argument2.Compute(variableValues);
    }

    class Mult : BinaryOperation
    {
        public Mult(Expr argument1, Expr argument2) : base(argument1, argument2) { }
        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
            => Argument1.Compute(variableValues) * Argument2.Compute(variableValues);
    }

    class Divide : BinaryOperation
    {
        public Divide(Expr argument1, Expr argument2) : base(argument1, argument2) { }
        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
            => Argument1.Compute(variableValues) / Argument2.Compute(variableValues);
    }
}
