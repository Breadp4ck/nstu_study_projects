using System;
using System.Collections.Generic;

namespace MathCalculator
{
    interface IExpr
    {
        double Compute(IReadOnlyDictionary<string, double> variableValues);
        IEnumerable<string> Variables { get; }
        bool IsConstant { get; }
        bool IsPolynom { get; }
    }

    abstract class Expr : IExpr
    {
        public abstract double Compute(IReadOnlyDictionary<string, double> variableValues);
        public IEnumerable<string> Variables { get; }
        public bool IsConstant { get; }
        public bool IsPolynom { get; }

        public static Expr operator+(Expr variable)
            => variable;
        public static Expr operator-(Expr variable)
            => new Invert(variable);

        public static Expr operator+(Expr variable1, Expr variable2)
            => new Add(variable1, variable2);
        public static Expr operator-(Expr variable1, Expr variable2)
            => new Sub(variable1, variable2);
        public static Expr operator*(Expr variable1, Expr variable2)
            => new Mult(variable1, variable2);
        public static Expr operator/(Expr variable1, Expr variable2)
            => new Divide(variable1, variable2);
    }
}
