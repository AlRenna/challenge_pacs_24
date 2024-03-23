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
