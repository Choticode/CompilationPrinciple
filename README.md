一些编译原理小代码，有些乱，乱到不想再去整理

exp4:语法分析-自上而下（非递归）
    使用的文法如下：
	    E  ->  TE'
	  	E' ->  + TE' | e
     	T  ->  FT'
     	T' ->  * FT' | e
     	F  ->  (E) | id

    例子：
        输入：id+id*id
        输出：  
            E  ->  TE'
            T  ->  FT'
            F  ->  id
            E' ->  + TE'
            T  ->  FT'

exp5:...

exp6:...