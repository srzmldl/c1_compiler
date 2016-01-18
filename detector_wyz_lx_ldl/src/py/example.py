str = '''
   [B4]
   1: 1
   2: int a = 1;
   3: int c;
   4: a
   5: [B4.4] (ImplicitCastExpr, LValueToRValue, int)
   6: 1
   7: [B4.5] == [B4.6]
   T: [B4.7] ? ... : ...
   Preds (1): B5
   Succs (2): B2 B3
'''

sstr = '''
int foo()
 [B2 (ENTRY)]
   Succs (1): B1

 [B1]
   1: 0
   2: return [B1.1];
   Preds (1): B2
   Succs (1): B0

 [B0 (EXIT)]
   Preds (1): B1

int main()
 [B5 (ENTRY)]
   Succs (1): B4

 [B1]
   1: [B4.7] ? [B2.1] : [B3.1]
   2: c
   3: [B1.2] = [B1.1]
   Preds (2): B2 B3
   Succs (1): B0

 [B2]
   1: 1
   Preds (1): B4
   Succs (1): B1

 [B3]
   1: 0
   Preds (1): B4
   Succs (1): B1

 [B4]
   1: 1
   2: int a = 1;
   3: int c;
   4: a
   5: [B4.4] (ImplicitCastExpr, LValueToRValue, int)
   6: 1
   7: [B4.5] == [B4.6]
   T: [B4.7] ? ... : ...
   Preds (1): B5
   Succs (2): B2 B3

 [B0 (EXIT)]
   Preds (1): B1
'''

stderr = '''
int main()
 [B10 (ENTRY)]
   Succs (1): B9

 [B1]
   1: 0
   2: return [B1.1];
   Preds (2): B4 B7
   Succs (1): B0

 [B2]
   Preds (1): B3
   Succs (1): B4

 [B3]
   1: a
   2: [B3.1] (ImplicitCastExpr, LValueToRValue, int)
   3: n
   4: [B3.3] (ImplicitCastExpr, LValueToRValue, int)
   5: [B3.2] + [B3.4]
   6: a
   7: [B3.6] = [B3.5]
   Preds (1): B4
   Succs (1): B2

 [B4]
   1: a
   2: [B4.1] (ImplicitCastExpr, LValueToRValue, int)
   3: 0
   4: [B4.2] < [B4.3]
   T: while [B4.4]
   Preds (2): B2 B9
   Succs (2): B3 B1

 [B5]
   1: i
   2: [B5.1]++
   Preds (1): B6
   Succs (1): B7

 [B6]
   1: ans
   2: [B6.1] (ImplicitCastExpr, LValueToRValue, int)
   3: i
   4: [B6.3] (ImplicitCastExpr, LValueToRValue, int)
   5: [B6.2] + [B6.4]
   6: ans
   7: [B6.6] = [B6.5]
   Preds (1): B7
   Succs (1): B5

 [B7]
   1: i
   2: [B7.1] (ImplicitCastExpr, LValueToRValue, int)
   3: n
   4: [B7.3] (ImplicitCastExpr, LValueToRValue, int)
   5: [B7.2] < [B7.4]
   T: for (...; [B7.5]; ...)
   Preds (2): B5 B8
   Succs (2): B6 B1

 [B8]
   1: 0
   2: i
   3: [B8.2] = [B8.1]
   Preds (1): B9
   Succs (1): B7

 [B9]
   1: int a;
   2: int n;
   3: int ans;
   4: int i;
   5: a
   6: [B9.5] (ImplicitCastExpr, LValueToRValue, int)
   7: 0
   8: [B9.6] >= [B9.7]
   T: if [B9.8]
   Preds (1): B10
   Succs (2): B8 B4

 [B0 (EXIT)]
   Preds (1): B1

'''

func_foo = '''
int foo(int (a))
 [B2 (ENTRY)]
   Succs (1): B1

 [B1]
   1: a
   2: [B1.1] (ImplicitCastExpr, LValueToRValue, int)
   3: return [B1.2];
   Preds (1): B2
   Succs (1): B0

 [B0 (EXIT)]
   Preds (1): B1
'''