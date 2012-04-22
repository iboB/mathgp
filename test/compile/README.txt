MathGP tests for compilation errors.

Use the Ruby script test_errors.rb to perform the tests.

To add a new test either add a new .cpp file or a new .inl file

* .cpp files will be compiled separately
* .h files will be included in a generated file within a function.
  This generated file will include MathGP.
  This is what the generate file looks like:
  
  #include "../../mathgp/mathgp.h
  
  using namespace mathgp;
  
  void f()
  {
    #include [thefile]
  }
* The existing .cxx are used internally as reference checks

Be careful to use one error generating feature per file
