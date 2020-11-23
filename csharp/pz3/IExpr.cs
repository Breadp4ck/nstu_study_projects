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
    }
}
