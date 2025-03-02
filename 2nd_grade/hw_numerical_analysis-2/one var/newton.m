x = 2;
tol = 10^-10;

moves = 0;

while(moves <= 100)
    next_x = x - (f(x) / f_prime(x));
    
    if(abs(next_x - x) < tol)
        x = next_x;
        break;
    end

    seq(moves+1,1) = next_x;
    x = next_x;
    moves = moves + 1;
end

x
moves

function [out] = f(x)
    out = exp(x) + 2^-x + 2*cos(x) - 6;
end

function [out] = f_prime(x)
    out = exp(x) + -2^-x * log(2) - 2*sin(x);
end