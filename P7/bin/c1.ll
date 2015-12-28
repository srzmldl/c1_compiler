; ModuleID = 'c1'

@a = global i32 3
@b = global i32 10
@c = global i32 15
@output = global i32 0

declare i32 @print()

define i32 @main() {
entry:
  %h = alloca [5 x i32]
  %i = alloca i32
  store i32 0, i32* %i
  %getArr = getelementptr [5 x i32]* %h, i32 0, i32 1
  store i32 1, i32* %getArr
  %getArr1 = getelementptr [5 x i32]* %h, i32 0, i32 2
  store i32 2, i32* %getArr1
  br label %while.cond

while.cond:                                       ; preds = %while.loop, %entry
  %i2 = load i32* %i
  %eq = icmp sle i32 %i2, 4
  br i1 %eq, label %while.loop, label %while.end

while.loop:                                       ; preds = %while.cond
  %i3 = load i32* %i
  %getArr4 = getelementptr [5 x i32]* %h, i32 0, i32 %i3
  %refArr = load i32* %getArr4
  store i32 %refArr, i32* @output
  %0 = call i32 @print()
  %i5 = load i32* %i
  %addtmp = add i32 %i5, 1
  store i32 %addtmp, i32* %i
  br label %while.cond

while.end:                                        ; preds = %while.cond
  ret i32 0
}
