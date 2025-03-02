function [Y] = F(X)
% the original functions
% X is a vector

Y = [(3*X(1,1) - cos(X(2, 1) * X(3, 1)) - 0.5);
     (X(1, 1)^2 - 81 * (X(2, 1) + 0.1)^2 + sin(X(3, 1)) + 1.06)
     (exp(-X(1, 1) * X(2, 1)) + 20 * X(3, 1) + (10*pi - 3)/3)];

end