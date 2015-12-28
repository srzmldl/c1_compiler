; ModuleID = 'c1'

@output = global i32 0

declare i32 @print()

define i32 @main() {
entry:
  %n = alloca i32
  store i32 10, i32* %n
  %a = alloca [10 x i32]
  %c1 = alloca i32
  store i32 31313, i32* %c1
  %c2 = alloca i32
  store i32 3845, i32* %c2
  %c3 = alloca i32
  store i32 10007, i32* %c3
  %getArr = getelementptr [10 x i32]* %a, i32 0, i32 0
  store i32 123, i32* %getArr
  %i = alloca i32
  store i32 1, i32* %i
  br label %while.cond

while.cond:                                       ; preds = %while.loop, %entry
  %i1 = load i32* %i
  %n2 = load i32* %n
  %eq = icmp slt i32 %i1, %n2
  br i1 %eq, label %while.loop, label %while.end

while.loop:                                       ; preds = %while.cond
  %i3 = load i32* %i
  %subtmp = sub i32 %i3, 1
  %getArr4 = getelementptr [10 x i32]* %a, i32 0, i32 %subtmp
  %refArr = load i32* %getArr4
  %c15 = load i32* %c1
  %multmp = mul i32 %refArr, %c15
  %c26 = load i32* %c2
  %addtmp = add i32 %multmp, %c26
  %c37 = load i32* %c3
  %modrem = srem i32 %addtmp, %c37
  %i8 = load i32* %i
  %getArr9 = getelementptr [10 x i32]* %a, i32 0, i32 %i8
  store i32 %modrem, i32* %getArr9
  %i10 = load i32* %i
  %addtmp11 = add i32 %i10, 1
  store i32 %addtmp11, i32* %i
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %getArr12 = getelementptr [10 x i32]* %a, i32 0, i32 0
  %refArr13 = load i32* %getArr12
  %max = alloca i32
  store i32 %refArr13, i32* %max
  store i32 1, i32* %i
  br label %while.cond14

while.cond14:                                     ; preds = %if.end, %while.end
  %i17 = load i32* %i
  %n18 = load i32* %n
  %eq19 = icmp slt i32 %i17, %n18
  br i1 %eq19, label %while.loop15, label %while.end16

while.loop15:                                     ; preds = %while.cond14
  %i20 = load i32* %i
  %getArr21 = getelementptr [10 x i32]* %a, i32 0, i32 %i20
  %refArr22 = load i32* %getArr21
  %max23 = load i32* %max
  %ne = icmp sgt i32 %refArr22, %max23
  br i1 %ne, label %if.then, label %if.end

while.end16:                                      ; preds = %while.cond14
  %max29 = load i32* %max
  store i32 %max29, i32* @output
  %0 = call i32 @print()
  ret i32 0

if.then:                                          ; preds = %while.loop15
  %i24 = load i32* %i
  %getArr25 = getelementptr [10 x i32]* %a, i32 0, i32 %i24
  %refArr26 = load i32* %getArr25
  store i32 %refArr26, i32* %max
  br label %if.end

if.end:                                           ; preds = %if.then, %while.loop15
  %i27 = load i32* %i
  %addtmp28 = add i32 %i27, 1
  store i32 %addtmp28, i32* %i
  br label %while.cond14
}
