x1 = 1;
x2 = 2;
tol = 10^-15;

moves = 0;

while(moves <= 100)
    next_x = x2 - (f(x2)*(x2 - x1) / (f(x2) - f(x1)) );
    
    if(abs(next_x - x2) < tol)
        ans = next_x;
        break;
    end

    seq(moves+1, 1) = x2; 
    x1 = x2;
    x2 = next_x;
    moves = moves + 1;
end

ans
moves

function [out] = f(x)
    out = exp(x) + 2^-x + 2*cos(x) - 6;
end