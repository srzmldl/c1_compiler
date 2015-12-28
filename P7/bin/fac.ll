; ModuleID = 'c1'

@n = global i32 0
@ans = global i32 0
@output = global i32 0

declare i32 @print()

define i32 @factorial() {
entry:
  %n = load i32* @n
  %ne = icmp ne i32 %n, 1
  br i1 %ne, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %ans = load i32* @ans
  %n1 = load i32* @n
  %multmp = mul i32 %ans, %n1
  store i32 %multmp, i32* @ans
  %n2 = load i32* @n
  %subtmp = sub i32 %n2, 1
  store i32 %subtmp, i32* @n
  %0 = call i32 @factorial()
  br label %if.end

if.else:                                          ; preds = %entry
  %ans3 = load i32* @ans
  store i32 %ans3, i32* @output
  %1 = call i32 @print()
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret i32 0
}

define i32 @main() {
entry:
  store i32 10, i32* @n
  store i32 1, i32* @ans
  %0 = call i32 @factorial()
  %a = alloca i32
  store i32 3, i32* %a
  %a1 = load i32* %a
  %subtmp = sub i32 %a1, 1
  %b = alloca i32
  store i32 %subtmp, i32* %b
  %a2 = load i32* %a
  %b3 = load i32* %b
  %addtmp = add i32 %a2, %b3
  store i32 %addtmp, i32* @n
  store i32 1, i32* @ans
  %1 = call i32 @factorial()
  ret i32 0
}
