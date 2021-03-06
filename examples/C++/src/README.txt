
This directory contains some files that are intended for beginning STIR
developers. The first version of these files was constructed for 
(and presented at) the STIR workshop at IEEE MIC 2004.

Source code files
-----------------

demo1.cxx
	A simple program that backprojects some projection data.
	It illustrates
	- basic interaction with the user,
	- reading of images and projection data
	- construction of a specified type of back-projector,
	- how to use back-project all projection data
	- output of an image

demo2.cxx
	A small modification of demo1.cxx to ask the user for the
	back projector she wants to use.
	It illustrates
	- how to ask the user for objects for which different types
	  exist (e.g. back-projector, forward-projectors, image processors 
	  etc), anything based on the RegisteredObject hierarchy.
	- that STIR is able to select basic processing units at run-time
	- how to use the (very) basic display facilities in STIR

demo3.cxx
	A modification of demo2.cxx that parses all parameters from a parameter file.
	It illustrates
	- basic class derivation principles
	- how to use ParsingObject to have automatic capabilities of parsing
	  parameters files (and interactive questions to the user)
	- how most STIR programs parse the parameter files.

	Note that the same functionality could be provided without deriving
	a new class from ParsingObject. One could have a KeyParser object
	in main() and fill it in directly.

demo4_obj_fun.cxx
	A modified demo3.cxx that computes the objective function 
	value of the image generated from demo3.cxx.
	  It illustrates
		- how to initialise and setup an objective function object
		- how to compute the objective function (log-likelihood) value of an image
	    - how to compute the objective function (log-likelihood) gradient
	    - how a basic iterative optimisation works (or may not, if parameters are altered)

demo5_line_search.cxx
	Deviating from the previous demos, this demo performs a line search from a provided image
	in the direction of the gradient for various step sizes.
	  It illustrates
		- how to initialise and setup an objective function object
		- how to compute the objective function (log-likelihood) value and gradient
	    - Demonstrates how important step sizes for each iteration of an optimisation algorithm.
 
CMakeLists.txt
	A CMake file to say which files to build.

Supporting files
----------------
extra_stir_dirs.cmake
	A sub-cmakefile that needs to be moved to STIR/src/local (or at least
 	pointed to, see below). This way, it
	will be picked up by CMake. Its contents simply say
	that there are extra files in examples/src.

demo.par
	An example parameter file for demo3.cxx, using the 
	interpolating backprojector (i.e. the default one set-up by
	demo3.cxx)

demoPM.par
	An example parameter file for demo3.cxx, using the 
	backprojector that uses a projection matrix (using the ray tracing 
	model)

demo_obj_fun.par
	An example parameter file for demo4_obj_fun.cxx, used to
	compute the objective function value of an image and perform 
	some iterative gradient ascent updates.

demo5_line_search.par
	An example parameter file for demo5_line_search.cxx, used to
	perform a line search of a image and objective function.

generate_image.par
	An example parameter file for generate_image that allows it
	to construct a simple image that can be used for constructing 
	projection data, and it used as the template image in demo*.par.

small.*s
	An example (empty) projection data file (created using 
	create_projdata_template) that can be used as a template for 
	constructing projection data


How to compile using CMake (on Unix-type systems)
-----------------------------------------------
# step 1: tell STIR to use these files. 2 alternatives

# alternative 1: copy extra_stir_dirs.cmake to a default location
mkdir -p ../src/local
cp extra_stir_dirs.cmake ../src/local/
cd your-build-dir
# reconfigure your project
ccmake .

# alternative 2: set STIR_LOCAL to this directory
cd your-build-dir
# reconfigure your project
ccmake -DSTIR_LOCAL=/where/ever/the/STIR/source/is/STIR/examples/C++/src  .

# make the examples
make demo1 demo2 demo3 demo4_obj_fun demo5_line_search
# optionally install everything, including the demos
make install

How to run
----------
First you need to create some data.

#Generate an image
      generate_image generate_image.par

#Generate projection data
      forward_project sino.hs image.hv  small.hs

# Run the demos.
EXE_LOC=/whereever/you/built/STIR/src/examples/C++
	
# demo1
	$EXE_LOC/demo1
	# you can display the output using for instance
	manip_image output.hv
      
# demo2
	$EXE_LOC/demo2
	# demo2 contains a call `stir::display`, so you'll see the display immediately ( at least when on Unix)

# demo3
	$EXE_LOC/demo3 demo.par
	$EXE_LOC/demo3 demoPM.par
	# the next one will ask the questions interactively
	$EXE_LOC/demo3 

# demo4_obj_fun
	$EXE_LOC/demo4_obj_fun demo4_obj_fun.par
	# Feel free to alter the "step size" and "number of iterations" in "demo_obj_fun.par".
	# However, it is quite easy to cause unstable behaviour in the estimates.
	# Additionally, there is a lack of positivity constraint on the density images (typical for PET reconstruction).

# demo5_line_search
	$EXE_LOC/demo5_line_search demo5_line_search.par
	# Feel free to alter the objective function, image filename, and the step size configuration in the parameter file.
	# Try plotting the output `alphas.dat` and `Phis.dat` and visualise how the step size can impact the
	  objective function value
	# Now try `use exponential alphas := 1`?

What now ?
----------
Play around, modify the .par files, the templates, the source, and have fun.

Good luck

Kris Thielemans
12 November 2004
(with minor updates until 2017)
Robert Twyman, 2020,2021 (addition of demo4_obj_fun and demo5_line_search)
