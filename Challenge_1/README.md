 # PACS Challenge 1
 **A gradient method for minimization of a multivariate function**

 ## Execution:

The make command has 3 functions: all (default), clean, distclean.

***make all*** creates the executable.

***make clean*** and ***make distclean*** are cleanup commands.

Data can be set inside ***data.txt***.
The results are printed in ***results.txt***.


## File structure:
- **main.cpp**: call gradient method and print data;
- **vector_utilities.hpp**: vector operators and functions;
- **learning_rate.hpp**: learning rate rules for parameter alpha - *Armijo Rule*, *Exponential Decay*, *Inverse Decay*, *Constant Alpha*;
- **schemes.hpp**: gradient methods - *Gradient Descent*, *Heavy Ball*, *Nesterov*;
- **params.hpp** and **params.cpp**: Paramters struct.

Inside **main.cpp**, the function template **apply_scheme()** is called several times to compute the minimum with different methods and rules (for the learning rate). These are chosen using two enumerator as template parameters, one for the methods and the other for the learning rate rule.


