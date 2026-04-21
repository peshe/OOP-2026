#include <iostream>

#include "DynMatrix.h"
#include "String.h"

// structs/classes that implement operator() are called functors
struct Multiplier
{
   int factor;

   int operator()(int x) const { return x * factor; }
};

void PrintSth(const String& str)
{
   // uses the const variant of operator[]
   std::cout << str[2] << std::endl;
}

template <typename T>
void PrintMatrix(const DynMatrix<T>& mat)
{
   for (int i = 0; i < mat.Rows(); ++i)
   {
      for (int j = 0; j < mat.Cols(); ++j)
         std::cout << mat[i][j] << " ";  // uses the const variant of operator[]
      std::cout << "\n";
   }
}

int main()
{
   Multiplier quad{4};
   int res = quad(10);  // Objects of functors can be used as functions
   std::cout << res << std::endl;

   String str = "asdf";
   str[2] = 'E';

   PrintSth(str);
   std::cout << str << std::endl;

   std::cout << (str == "fmi") << std::endl;
   std::cout << ("asEf" == str) << std::endl;

   DynMatrix<int> mat(3, 4);
   for (int i = 0; i < mat.Rows(); ++i)
      for (int j = 0; j < mat.Cols(); ++j)
         mat[i][j] = i * mat.Cols() + j;

   DynMatrix<int> mat2(5, 2);
   mat2 = mat;  // testing operator=
   try
   {
      mat2.At(4, 0);
   }
   catch (const std::out_of_range& ex)
   {
      std::cout << ex.what() << std::endl;
   }
   mat2.At(1, 1) = 42;

   PrintMatrix(mat2);

   return 0;
}
