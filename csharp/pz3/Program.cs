using System;

namespace pz3
{
    class Program
    {
        static void Main(string args[])
        {

        }
    }

    interface IExpr
    {
        double Compute(IReadOnlyDictionary<string, double> variableValues);
        IEnumerable<string> Variables { get; }
        bool IsConstant { get; }
        bool IsPolynom { get; }
    }

    abstract class UnaryOperation
    {

    }

    abstract class BinaryOperation
    {

    }

    abstract class Function
    {

    }

    class Variable
    {

    }

    class Constant
    {

    }
}
