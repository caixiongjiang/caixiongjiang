function coeff = mySpearman(X , Y)
% 本函数用于实现斯皮尔曼等级相关系数的计算操作
%
% 输入：
%   X：输入的数值序列
%   Y：输入的数值序列
%
% 输出：
%   coeff：两个输入数值序列X，Y的相关系数


if length(X) ~= length(Y)
    error('两个数值数列的维数不相等');
    return;
end

N = length(X); %得到序列的长度
Xrank = zeros(1 , N); %存储X中各元素的排行
Yrank = zeros(1 , N); %存储Y中各元素的排行

%计算Xrank中的各个值
for i = 1 : N
    cont1 = 1; %记录大于特定元素的元素个数
    cont2 = -1; %记录与特定元素相同的元素个数
    for j = 1 : N
        if X(i) < X(j)
            cont1 = cont1 + 1;
        elseif X(i) == X(j)
            cont2 = cont2 + 1;
        end
    end
    Xrank(i) = cont1 + mean([0 : cont2]);
end

%计算Yrank中的各个值
for i = 1 : N
    cont1 = 1; %记录大于特定元素的元素个数
    cont2 = -1; %记录与特定元素相同的元素个数
    for j = 1 : N
        if Y(i) < Y(j)
            cont1 = cont1 + 1;
        elseif Y(i) == Y(j)
            cont2 = cont2 + 1;
        end
    end
    Yrank(i) = cont1 + mean([0 : cont2]);
end

%利用差分等级(或排行)序列计算斯皮尔曼等级相关系数
fenzi = 6 * sum((Xrank - Yrank).^2);
fenmu = N * (N^2 - 1);
coeff = 1 - fenzi / fenmu;

end %函数mySpearman结束