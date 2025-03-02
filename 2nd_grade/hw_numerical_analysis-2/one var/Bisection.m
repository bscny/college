clear

left = 0;
right = 1;
mid = (left + right);

tol = 10^-10;
moves = 0;

while abs(f(mid) >= tol) | (right - left)/2 >= tol
    mid = (left + right)/2;
    
    if f(mid) > 0 
        right = mid;
    else
        left = mid;
    end

    moves = moves + 1;
end

mid
moves

function [out] = f(x)
    out = exp(x) + x^2 + 3*x -2;
end
