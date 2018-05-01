-------------------------------------------------------------
-- sell_test.lua -- a sample script file for Orion3D shell --
-------------------------------------------------------------


-- a function to list the sub-directories
function PrintDirecories()
	for i=0,GetNbrSubDir()-1 do
		print("  " .. i .. " - " .. GetSubDir(i) )
	end
end



print "#############################"
print "### Welcome to shell test ###"
print "#############################"
print "This file is a LUA test script."
print "It will give an overview of the features of the shell and"
print "the integrated LUA interpreter."

-- test Orion3D shell functions 
print "\n### We can use shell functions to get the list of sub-directories : "
print("The number of sub-directories is : " .. GetNbrSubDir())
PrintDirecories()

print "\n### We can also navigate through the shell : "
if GetNbrSubDir()>0 then
	print( "-- we can use cd() to jump in the first directory, which is '" .. GetSubDir(0) .. "'" )
	cd( GetSubDir(0) )
	print( "-- now we can get the current pwd : " )
	pwd()
	print( "\n-- and make a listing of the sons directories : " )
	PrintDirecories()
	cd( ".." )
else
	print "Oups, there is no son directories ..."
end


