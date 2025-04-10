# Overwriting-Operators-For-Matrixes
This C++ program implements matrix operations using operator overloading, including addition (+), subtraction (-), element-wise multiplication (^), matrix multiplication (*), and transposition (~).\
The Matrix class is designed to handle matrix operations efficiently using std::vector, making it more flexible and dynamic compared to fixed-size arrays.\
Additionally, the Vector class is introduced to extract and represent a specific column from a matrix, enabling easy column-wise operations.\
Key Features:\
•	Operator Overloading: Provides intuitive syntax for matrix arithmetic.\
•	Dynamic Memory Management: Uses std::vector instead of fixed-size arrays, allowing matrices of any size.\
•	Dimension Checking: Prevents invalid operations such as adding matrices of different sizes or multiplying incompatible matrices.\
•	Transposition Support: Implements the transpose operation efficiently.\
•	Error Handling: Detects out-of-bounds access and invalid matrix operations to prevent runtime crashes.\

