# Disease-Simulation

This program uses information about the situation of a disease in a community given in the form of a input text file to determine where
and when the disease will spread.

The input file provides a grid representing people. Each person is denoted by a letter: s (susceptible to the disease), i (infected 
from the disease), r (recovered from the disease), and v (vaccinated from the disease). The input file also specifies how long one
will stay infected with the disease, how infectious it is, and the interval of how many days to display (if it is every other day, this 
variable's value will be 2). 

Each day is printed to the screen as a separate grid showing what stage of the disease (s, i, r, or v) each person is in. After the last 
day (when the disease is eradicated), the program shows which day had the most infected people and how long the disease outbreak lasted. 
