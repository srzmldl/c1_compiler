; ModuleID = 'a.cpp'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@output = global i32 0, align 4

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %a = alloca i32, align 4
  store i32 0, i32* %retval
  store i32 1, i32* %a, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %0 = load i32* %a, align 4
  %cmp = icmp sle i32 %0, 10
  br i1 %cmp, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %1 = load i32* %a, align 4
  store i32 %1, i32* @output, align 4
  %2 = load i32* %a, align 4
  %sub = sub nsw i32 %2, 1
  store i32 %sub, i32* %a, align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  ret i32 0
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.6.0 (tags/RELEASE_360/final 254901)"}
