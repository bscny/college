function [Y] = H(lamda, X, X0)
% lamda is a parameter from 0 ~ 1
% X is a vector
% X0 is the init vector

if(lamda < 0 || lamda > 1)
    fprintf('Error: lamda out of scope \n');
end

Y = F(X) + (lamda - 1) * F(X0);

end