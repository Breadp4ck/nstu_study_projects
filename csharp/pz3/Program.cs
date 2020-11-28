using System;
using System.Collections.Generic;

namespace MathCalculator
{
    class Program
    {
        static void Main(string[] args)
        {
            // the 8th option, inverse trigonometric functions
            Variable a = new Variable("a");
            Variable b = new Variable("b");
            Constant c = new Constant(5);

            //var exp = new Add(a, (new Add(c, b)));
            //var exp = a * b + c;
            //Console.WriteLine(exp.Compute(new Dictionary<string, double> { ["a"] = 2, ["b"] = 4 }));
            //Console.WriteLine(exp);

            //Console.WriteLine("\n\n");

            //Constant a1 = new Constant(3.4);
            //Constant b1 = new Constant(7.6);
            //var exp1 = (new Add(c, new Add(a1, b1)));
            //Console.WriteLine(exp1.Compute(null));

            var expr = (a + b) / c;
            var s = new Vector(new Expr[] {expr, expr, expr});

            Console.WriteLine(s.Compute(null));
            Console.WriteLine(s);
        }
    }
}
