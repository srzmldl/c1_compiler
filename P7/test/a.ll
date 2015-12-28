; ModuleID = 'a.cpp'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %a = alloca [10 x i32], align 16
  %b = alloca [4 x i32], align 16
  %c = alloca i32, align 4
  store i32 0, i32* %retval
  store i32 0, i32* %c, align 4
  %0 = load i32* %c, align 4
  %add = add nsw i32 %0, 1
  %idxprom = sext i32 %add to i64
  %arrayidx = getelementptr inbounds [4 x i32]* %b, i32 0, i64 %idxprom
  %1 = load i32* %arrayidx, align 4
  %2 = load i32* %c, align 4
  %idxprom1 = sext i32 %2 to i64
  %arrayidx2 = getelementptr inbounds [10 x i32]* %a, i32 0, i64 %idxprom1
  store i32 %1, i32* %arrayidx2, align 4
  ret i32 0
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.6.0 (tags/RELEASE_360/final 254901)"}
