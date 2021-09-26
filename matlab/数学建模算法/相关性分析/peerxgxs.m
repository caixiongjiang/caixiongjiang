function coeff = myPearson(X , Y)
% 本函数实现了皮尔逊相关系数的计算操作
% 皮尔逊相关系数计算公式（P18）及无偏相关系数矫正公式(P19)参见《现代气候统计诊断与预测技术》-魏凤英
%
% 输入：
%   X：输入的数值序列
%   Y：输入的数值序列
%
% 输出：
%   coeff：两个输入数值序列X，Y的相关系数
%

if length(X) ~= length(Y)
    error('两个数值数列的维数不相等');
    return;
end

fenzi = sum((X-sum(X)/length(X)).*(Y-sum(Y)/length(Y)));
fenmu = sqrt(sum((X-sum(X)/length(X)).^2))*sqrt(sum((Y-sum(Y)/length(Y)).^2));
coef = fenzi / fenmu;

if length(X)>30
    coeff = coef;
elseif length(X)>4 && length(X)<30
    coeff = coef*(1+(1-coef^2)/(2*(length(X)-4)));      %计算无偏相关系数加以矫正
else
    coeff = coef;
    fprintf('数据长度小于5 %8.4f\n',coeff);
end

end %函数myPearson结束
