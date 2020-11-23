using System;
using System.Collections.Generic;

namespace MathCalculator
{
    class Program
    {
        static void Main(string[] args)
        {
            Variable a = new Variable("a");
            Variable b = new Variable("b");

            var exp = (new Add(a, b));
            Console.WriteLine(exp.Compute(new Dictionary<string, double> { ["a"] = 3.4, ["b"] = 7.6 }));
            Console.WriteLine(new Sub(a, b).Compute(new Dictionary<string, double> { ["a"] = 3.4, ["b"] = 7.6 }));
            Console.WriteLine(new Mult(a, b).Compute(new Dictionary<string, double> { ["a"] = 3.4, ["b"] = 7.6 }));
            Console.WriteLine(new Divide(a, b).Compute(new Dictionary<string, double> { ["a"] = 3.4, ["b"] = 7.6 }));

            Console.WriteLine("\n\n");

            Constant a1 = new Constant(3.4);
            Constant b1 = new Constant(7.6);
            var exp1 = (new Add(a1, b1));
            Console.WriteLine(exp1.Compute(new Dictionary<string, double> { ["a"] = 0, ["b"] = 0 }));
            Console.WriteLine(new Sub(a1, b1).Compute(new Dictionary<string, double> { ["a"] = 0, ["b"] = 0 }));
            Console.WriteLine(new Mult(a1, b1).Compute(new Dictionary<string, double> { ["a"] = 0, ["b"] = 0 }));
            Console.WriteLine(new Divide(a1, b1).Compute(new Dictionary<string, double> { ["a"] = 0, ["b"] = 0 }));
        }
    }
}
