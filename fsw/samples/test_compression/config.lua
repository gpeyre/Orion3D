-----------------------------------------------------------------------
--  This is the configuration file for test_compression by G.Peyre   --
-----------------------------------------------------------------------

author = "Gabriel Peyr�"
date = 2002
copyright = "Copyright (c) 2002 Orion3D"
start_whith = "          .. Test for FSW compression .." 

nbr_steps = 50		-- number of steps to do in decompression
max_bpv = 1				-- maximum bit per vertex to test for decompression 

test_list = 
{
	{ test_name="LenaB",	test_caption="Image ''lena'', buttefly wavelet",		temp_file="Lena.fsw",		scaling="L2", transform="Butterfly", basemesh="Octahedron", func_type="Image",		image_file="../data/lena.gif" },
	{ test_name="LenaL",	test_caption="Image ''lena'', linear wavelet",			temp_file="Lena.fsw",		scaling="L2", transform="Linear",	basemesh="Octahedron", func_type="Image",		image_file="../data/lena.gif" }
}

---------------------------------------------------------------------
-- Copyright (c) 2002 Gabriel Peyr� -- EDIT AT YOUR OWN RISK       --
---------------------------------------------------------------------