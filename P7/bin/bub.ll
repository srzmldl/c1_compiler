; ModuleID = 'c1'

@output = global i32 0

declare i32 @print()

define i32 @main() {
entry:
  %n = alloca i32
  store i32 10, i32* %n
  %a = alloca [10 x i32]
  %getArr = getelementptr [10 x i32]* %a, i32 0, i32 0
  store i32 10, i32* %getArr
  %getArr1 = getelementptr [10 x i32]* %a, i32 0, i32 1
  store i32 7, i32* %getArr1
  %getArr2 = getelementptr [10 x i32]* %a, i32 0, i32 2
  store i32 5, i32* %getArr2
  %getArr3 = getelementptr [10 x i32]* %a, i32 0, i32 3
  store i32 100, i32* %getArr3
  %getArr4 = getelementptr [10 x i32]* %a, i32 0, i32 4
  store i32 1, i32* %getArr4
  %getArr5 = getelementptr [10 x i32]* %a, i32 0, i32 5
  store i32 7, i32* %getArr5
  %getArr6 = getelementptr [10 x i32]* %a, i32 0, i32 6
  store i32 67, i32* %getArr6
  %getArr7 = getelementptr [10 x i32]* %a, i32 0, i32 7
  store i32 4, i32* %getArr7
  %getArr8 = getelementptr [10 x i32]* %a, i32 0, i32 8
  store i32 99, i32* %getArr8
  %getArr9 = getelementptr [10 x i32]* %a, i32 0, i32 9
  store i32 6, i32* %getArr9
  %i = alloca i32
  store i32 0, i32* %i
  br label %while.cond

while.cond:                                       ; preds = %while.loop, %entry
  %i10 = load i32* %i
  %n11 = load i32* %n
  %subtmp = sub i32 %n11, 1
  %eq = icmp sle i32 %i10, %subtmp
  br i1 %eq, label %while.loop, label %while.end

while.loop:                                       ; preds = %while.cond
  %i12 = load i32* %i
  %addtmp = add i32 %i12, 1
  store i32 %addtmp, i32* %i
  br label %while.cond

while.end:                                        ; preds = %while.cond
  store i32 0, i32* %i
  br label %while.cond13

while.cond13:                                     ; preds = %while.end22, %while.end
  %i16 = load i32* %i
  %n17 = load i32* %n
  %subtmp18 = sub i32 %n17, 1
  %eq19 = icmp slt i32 %i16, %subtmp18
  br i1 %eq19, label %while.loop14, label %while.end15

while.loop14:                                     ; preds = %while.cond13
  %j = alloca i32
  store i32 0, i32* %j
  br label %while.cond20

while.end15:                                      ; preds = %while.cond13
  %flag = alloca i32
  store i32 1, i32* %flag
  store i32 0, i32* %i
  br label %while.cond53

while.cond20:                                     ; preds = %if.end, %while.loop14
  %j23 = load i32* %j
  %n24 = load i32* %n
  %subtmp25 = sub i32 %n24, 1
  %i26 = load i32* %i
  %subtmp27 = sub i32 %subtmp25, %i26
  %eq28 = icmp slt i32 %j23, %subtmp27
  br i1 %eq28, label %while.loop21, label %while.end22

while.loop21:                                     ; preds = %while.cond20
  %j29 = load i32* %j
  %addtmp30 = add i32 %j29, 1
  %getArr31 = getelementptr [10 x i32]* %a, i32 0, i32 %addtmp30
  %refArr = load i32* %getArr31
  %j32 = load i32* %j
  %getArr33 = getelementptr [10 x i32]* %a, i32 0, i32 %j32
  %refArr34 = load i32* %getArr33
  %eq35 = icmp slt i32 %refArr, %refArr34
  br i1 %eq35, label %if.then, label %if.end

while.end22:                                      ; preds = %while.cond20
  %i51 = load i32* %i
  %addtmp52 = add i32 %i51, 1
  store i32 %addtmp52, i32* %i
  br label %while.cond13

if.then:                                          ; preds = %while.loop21
  %j36 = load i32* %j
  %getArr37 = getelementptr [10 x i32]* %a, i32 0, i32 %j36
  %refArr38 = load i32* %getArr37
  %t = alloca i32
  store i32 %refArr38, i32* %t
  %j39 = load i32* %j
  %addtmp40 = add i32 %j39, 1
  %getArr41 = getelementptr [10 x i32]* %a, i32 0, i32 %addtmp40
  %refArr42 = load i32* %getArr41
  %j43 = load i32* %j
  %getArr44 = getelementptr [10 x i32]* %a, i32 0, i32 %j43
  store i32 %refArr42, i32* %getArr44
  %t45 = load i32* %t
  %j46 = load i32* %j
  %addtmp47 = add i32 %j46, 1
  %getArr48 = getelementptr [10 x i32]* %a, i32 0, i32 %addtmp47
  store i32 %t45, i32* %getArr48
  br label %if.end

if.end:                                           ; preds = %if.then, %while.loop21
  %j49 = load i32* %j
  %addtmp50 = add i32 %j49, 1
  store i32 %addtmp50, i32* %j
  br label %while.cond20

while.cond53:                                     ; preds = %if.end68, %while.end15
  %i56 = load i32* %i
  %n57 = load i32* %n
  %subtmp58 = sub i32 %n57, 1
  %eq59 = icmp slt i32 %i56, %subtmp58
  br i1 %eq59, label %while.loop54, label %while.end55

while.loop54:                                     ; preds = %while.cond53
  %i60 = load i32* %i
  %getArr61 = getelementptr [10 x i32]* %a, i32 0, i32 %i60
  %refArr62 = load i32* %getArr61
  %i63 = load i32* %i
  %addtmp64 = add i32 %i63, 1
  %getArr65 = getelementptr [10 x i32]* %a, i32 0, i32 %addtmp64
  %refArr66 = load i32* %getArr65
  %ne = icmp sgt i32 %refArr62, %refArr66
  br i1 %ne, label %if.then67, label %if.end68

while.end55:                                      ; preds = %while.cond53
  store i32 0, i32* %i
  br label %while.cond71

if.then67:                                        ; preds = %while.loop54
  store i32 0, i32* %flag
  br label %if.end68

if.end68:                                         ; preds = %if.then67, %while.loop54
  %i69 = load i32* %i
  %addtmp70 = add i32 %i69, 1
  store i32 %addtmp70, i32* %i
  br label %while.cond53

while.cond71:                                     ; preds = %while.loop72, %while.end55
  %i74 = load i32* %i
  %n75 = load i32* %n
  %subtmp76 = sub i32 %n75, 1
  %eq77 = icmp sle i32 %i74, %subtmp76
  br i1 %eq77, label %while.loop72, label %while.end73

while.loop72:                                     ; preds = %while.cond71
  %i78 = load i32* %i
  %getArr79 = getelementptr [10 x i32]* %a, i32 0, i32 %i78
  %refArr80 = load i32* %getArr79
  store i32 %refArr80, i32* @output
  %0 = call i32 @print()
  %i81 = load i32* %i
  %addtmp82 = add i32 %i81, 1
  store i32 %addtmp82, i32* %i
  br label %while.cond71

while.end73:                                      ; preds = %while.cond71
  ret i32 0
}
