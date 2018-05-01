-- test file for LUA wrapper
-- by Gabriel Peyré, 08/30/2001

function factorial(n)
	if n==0 then return 1
	else return n*factorial( n-1 ) end
end

print("enter a number : ")
a = read("*number")
print( factorial(a) )