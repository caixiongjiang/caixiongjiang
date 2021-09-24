A=[1000	120	5000	1	50	1.5	1
700	60	4000	2	40	2	2
900	60	7000	1	70	1	4
800	70	8000	1.5	40	0.5	6
800	80	4000	2	30	2	5];
[m,n]=size(A);%找出多少行多少列
maxA=max(A);%找出每列最大值
minA=min(A);%找出每列最小值
G=maxA-min(A);%最大值减去最小值
A1=max(A(:,1));%A1为效益型
A2=min(A(:,2:n-1));%A2~A6为成本型
A3=max(A(:,7));%A7为效益型
u=[A1,A2,A3];
R=zeros(m,n);%将模糊综合矩阵初值设置为0
% 如下是得出模糊综合矩阵
for i=1:m
    for j=1:n
        R(i,j)=abs(A(i,j)-u(j))/G(j)
    end
end
%利用变异系数计算权向量
x=mean(A);
s=std(A);
v=s./x;
v2=sum(v);
c=zeros(1,7);
for i=1:7
    c(i)=v(i)/v2;
end

FF=R*c';