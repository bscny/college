x = 2;
tol = 10^-10;

moves = 0;

while(moves <= 100)
    next_x = f(x);
    
    if(abs(next_x - x) < tol)
        x = next_x;
        break;
    end

    x = next_x;
    moves = moves + 1;
end

x
moves

function [out] = f(x)
    out = 5/x^2 + 2;
end