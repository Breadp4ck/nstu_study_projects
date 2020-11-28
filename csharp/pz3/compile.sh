#!/bin/bash

csc /t:exe /out:Program.exe Program.cs BinaryOperation.cs \
    Function.cs Constant.cs IExpr.cs Variable.cs \
    UnaryOperation.cs
