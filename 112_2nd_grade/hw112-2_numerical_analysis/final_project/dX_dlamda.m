function [X_prime] = dX_dlamda(X, X0)
% X is a vector
% X0 is the init vector

X_prime = -(J(X)\F(X0));

end