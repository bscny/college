function [X, recording] = Newton_on_H(lamda, X0, const_X0)
% X0 is the init vector predicted by the continue method, is a vector

if(lamda < 0 || lamda > 1)
    fprintf('Error: lamda out of scope \n');
end

step = 0;
TOL = 10^-12;

residual = H(lamda, X0, const_X0);
recording = [step norm(residual, inf)];

while(step < 15 & recording(step + 1, 2) > TOL)
    X = X0 - (J(X0)\residual);
    X0 = X;

    step = step + 1;
    residual = H(lamda, X0, const_X0);

    recording(step + 1, 1) = step;
    recording(step + 1, 2) = norm(residual, inf);
end

end