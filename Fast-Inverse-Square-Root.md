Fast Inverse Square Root algorithm

- `long` 32 bits integer number
- `float` 32 decimal number (single)

$ Z_d \cong (Z_d + C_{d,1}) / C_{d,1} \oplus (Z_d \cap C_{d,1}) $ 

$ [z] \in Z \cap C / B \cap C $ means that $ z\in  Z\cap C$ and is equal to the set
$[z] = \{z + b | b \in B\cap C \}$
##  IEEE 754
$11000 = 1.1 \times 2^4$  
- sign(1-bit):  0 postive, 1 negative
- Exponent(8-bits): represent exponent numbers (start from -127)
- Mantissa(23-bits): represent mantissa number after decimal dot

### example
0 00000011 
positve 2^(3-127)
``` 
85.125
85 = 1010101
0.125 = 001
85.125 = 1010101.001
       = 1.010101001 x 2^6 
       = (1+M/2^23) x 2^(E - 127)
sign = 0 

1. Single precision:
biased exponent 127+6 = 133 = E
133 = 10000101
Normalised mantisa = 010101001
we will add 0's to complete the 23 bits

The IEEE 754 Single precision is:
= 0 10000101 01010100100000000000000
This can be written in hexadecimal form 42AA4000
```

##  IEEE 754 with number
We define the bits reprsentation of a number with E and M to be $2^{23}\times E + M = $ shift E by 23 dits and then add the bits in M into it.

Now, take logarithm with base 2 to 
$$
(1 + \frac{M}{2^{23}} ) \cdot 2^{E - 127}
$$
gives 
$$
\log_2(1 + \frac{M}{2^{23}} ) +  E - 127
$$
, and then apply tricks $log(1+x)  \approx x + \mu$, where $\mu = 0.0430 $ is the correction term to choosen to give the smallest average error. Thus,
$$
\log_2(1 + \frac{M}{2^{23}} ) +  E - 127\\
\approx \frac{M}{2^{23}} + \mu + E - 127\\
\approx \frac{M + 2^{23} \cdot E}{2^{23}} + \mu - 127
$$
and note that the bit representation of a number is equal to its logarithm up to some scaling and shifting.

## back to algorithm
`float y`
- IEEE 754
- no bit manipulation
- used to store number 

`long i`
- ordinary 32-bit number
- has bit manipulation

`i = (long) y`
- convert float to long, eg, 3 <--3.33 
- but lose so much information

`i = * (long *) &y`
- convert the type of the orginal address without modifying the contents inside.
- now `i` is y's bits representation, which is about equal to log(y) up to some scaling and shifting.

`i = 0x5f3759df - ( i >> 1);`

In order to compute $\frac{1}{\sqrt{y}}: = z $, it is easier to compute $\log(z)$, and 
$$
\begin{aligned}
\log(z) & = \frac{1}{2^{23}} (M_z + 2^{23} \cdot E_z ) + \mu - 127 \\
& = \log(\frac{1}{\sqrt{y}})\\ 
& = (-\frac{1}{2})\log(y)\\
& =- \frac{1}{2} (\frac{1}{2^{23}} (M_y + 2^{23} \cdot E_y ) + \mu - 127) 
\end{aligned}
$$
Since we only need to compute the bit representation of $z: M_z + 2^{23} \cdot E_z $, from above, it is equal to 
$$
\begin{aligned}
= & \frac{3}{2} 2^{23} (127 - \mu) - \frac{1}{2} (M_y + 2^{23} \cdot E_y )\\
= & \text{ 0x5f3759df}  - ( i >> 1);  
\end{aligned}
$$

`y = * ( float * ) &i;`
- convert back to a float number

`y = y * (threehalfs - ( x2 * y * y ) );`

Newton Method:
Used to find root of $f(x) = 0$, updated by $x_{new} = x - \frac{f(x)}{f'(x)} $.

Here $f(y) = \frac{1}{y^2} - x =0 $, given $x$ we hope to find $y$. Thus,
$$
\begin{aligned}
y_{new} & = y + \frac{y}{2} (1 - x y ^2) \\ &= y(\frac{3}{2} - \frac{x}{2} y ^2)
\end{aligned}
$$


