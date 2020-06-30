1.函数定义：

<程序> ——> int main{<语句表>}

<program>  ——>  int main{<state_table>}

2.语句定义：

<语句块> ——>  <声明语句><执行语句>

<state_table> ——>  <de_state><exe_state>	

3.声明语句定义：

<声明语句> ——>  <类型><标志符>;<声明语句> | ε

<de_state> ——> type iden ; <de_state> | ε

4.执行语句定义：

<执行语句> ——>  iden=<算术表达式>;<执行语句> | if<if块><执行语句>  | while<while块><执行语句 | ε

<exe_state> ——> iden =<arith_ex> ; <exe_state> | if<judge_clock><exe_state>| while<loop_clock><exe_state>| ε

<if块>    ——>   (<判断句>){<执行语句>}<else块>

<judge_clock>    ——>   (<judge_1>){<exe_state>}<other_clock>

<判断句>  ——> !(<判断句_1>) | <判断句_1>

<judge_1>  ——> !(<judge_2>) | <judge_2>

<判断句_1> ——>  <判断句_3><判断句_2>

<judge_2> ——>  <judge_4><judge_3>

<判断句_2> ——>  &&<判断句> | ||<判断句>| ε

<judge_3> ——> &&<judge_1> | ||<judge_1> | ε

<判断句_3> ——>  <算术表达式><判断句_4>

<judge_4> ——>  <arith_ex> <judge_5>

<判断句_4> ——>  ω2<算术表达式> |ε

<judge_5> ——>  ω2 <arith_ex> | ε    
                
<else块>  ——>   else{<执行语句>}  | ε

<other_clock> ——> else{<exe_state>} | ε

<while块> ——>   (<判断句>){<执行语句>}

<loop_clock> ——> (<judge_1>){<exe_state>}

5.算术表达式定义：

<算术表达式>  ——>  <项> <算术表达式1>		

<arith_ex>  ——> <term> <arith_ex1>

<算术表达式1>  ——> ω0 <项><算术表达式1> | ε

<arith_ex1> ——> ω0 <term><arith_ex1> | ε

<项>   ——>   <因子><项1>

<term>   ——>   <factor><term1>

<项1>  ——>   ω1 <因子> <项1>| ε    

<term1> ——> ω1 <factor> <term1> | ε   

<因子> ——>   <算术量>  | ( <算术表达式> )

<factor> ——>   <arith_qu> | ( <arith_ex> )

<算术量> ——> <标识符> | <浮点数>  

<arith_qu> ——> iden  |  float  | string

6.类型定义：

<类型> ——> string | float

<type> ——> string  | float
注：
ω0 — +或-
ω1 — *或/
ω2 — < > <= >= == !=
