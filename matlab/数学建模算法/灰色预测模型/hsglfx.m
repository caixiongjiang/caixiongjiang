%【1】确定比较对象（评价对象）(就是数据，并且需要进行规范化处理，就是标准化处理，见下面例题的表格数据)和参考数列（评价标准，一般该列数列都是1，就是最优的的情况） 
%【2】确定各个指标权重，可用层次分析确定 
%【3】计算灰色关联系数 
%【4】计算灰色加权关联度 
%【5】评价分析

x1=[1.14 1.49 1.69 2.12 2.43 4.32 5.92 6.07 7.85;3.30 3.47 3.61 3.80 4.00 4.19 4.42 4.61 4.80;6.00 6.00 6.00 7.50 7.50 7.50 9.00 9.00 9.00;1.20 1.20 1.80 1.80 1.80 2.40 2.70 3.60 4.00;4.87 5.89 6.76 7.97 8.84 10.05 11.31 12.25 11.64];%原始数据5行9列
x=x1;
for i=1:5
    for j=1:9
  x(i,j)=x(i,j)/x1(1,j);
    end
end
x1=x;
for i=1:5
    for j=1:9
  x(i,j)=abs(x(i,j)-x1(i,1));
    end
end
max=x(1,1);
min=x(1,1);
for i=1:5
    for j=1:9
        if x(i,j)>=max
     max=x(i,j);
        end
    end
end
for i=1:5
    for j=1:9
        if x(i,j)<=min
     min=x(i,j);
        end
    end
end
k=0.5; %分辨系数取值
l=(min+k*max)./(x+k*max);%求关联系数矩阵
guanliandu = SUM(l')/n;
[rs,rind]=sort(guanliandu,'descend'); %对关联度进行排序