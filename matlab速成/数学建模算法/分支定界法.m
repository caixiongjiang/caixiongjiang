addA(n) = 1;
%构造第一个分支 x<=floor(x(n))
A = [A;addA];
B = [B,floor(x(n))];%向下取整
[x1,fval1,status1,bound1] = branchbound(f,A,B,I,x0,fval0,bound,Aeq,Beq,lb,ub,e);
A(end,:) = [];
B(:,end) = [];
%解得第一个分支，若为更优解则替换，若不是则保持原状

status = status1;
if status1 > 0 && bound1 < bound
    newx = x1;
    newfval = fval1;
    bound = fval1;
    newbound = bound1;
else
    newx = x0;
    newfval = fval0;
    newbound = bound;
end

%构造第二分支
A = [A;-addA];
B = [B,-ceil(x(n))];%向上取整
[x2,fval2,status2,bound2] = branchbound(f,A,B,I,x0,fval0,bound,Aeq,Beq,lb,ub,e);    
A(end,:) = [];
B(:,end) = [];

%解得第二分支，并与第一分支做比较，如果更优则替换
if status2 > 0 && bound2 < bound
    status = status2;
    newx = x2;
    newfval = fval2;
    newbound = bound2;
end
