# Calc
💻Calculator on C++

## Table of contents
 + [1. Installation](#1_parag);
 + [2. Description](#2_parag); 

## <a name="1_parag"></a>	1. Installation

There is no need to install this program. Just oppen "SV_Calc.exe" file from Win10exe folder

## <a name="2_parag"></a>	2 .Description

This is c++ calculator i made in Qt.<br>
It can count long expressions, not just two numbers
<details>
  <summary>screenshot</summary>
  
  ![screenshot](https://i.imgur.com/QpVizBq.png)
  
</details>

### Keys:<br>
[0-9] - numbers<br>
[+][-][/][*] - basic operations<br>
[Enter][=] - get result<br>
[Backspace] - delete last char<br>
[C] - delete last number<br>
[del] - delete all<br>
[,][.] for dot<br>

### Calculations queue:<br>
Power->root->devide->multiply->add

### How it works
After you finished typing expression, calculator will use regular expressions to find and count everything one by one.
Also, it can detect errors like negative in root and display them

<details>
  <summary>Example: </summary>
  
  Expression: 5-2^3--4+9/2√9
  1. 2^3=8 | 5-8--4+9/2√9
  2. 2√9=3 | 5-8--4+9/3
  3. 9/3=3 | 5-8--4+3
  4. 5+(-8)+4+3=4  
  Result is 4  
  
</details>
