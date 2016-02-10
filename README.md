# Atomic/Diatomic/Triatomic Molecular Orbital & Geometry Specification

This project implements code to read XML data that describe
a molecular structure and atomic orbitals into internal variables
that can be used to drive SCF calculations, particularly for
optimization or plotting.

This package includes 
     1) a DOCTYPE definition template (in the example files) that defines
        the XML format for specifying molecular orbitals and geometries
	for SCF calculations (examples for atomic/diatomic only initially)
     2) a tree navigation program that parses and prints document elements
        to aid in validating the input XML file
     3) a parser (dia-xml-inp) that shows how to extract the data from
     	the XML files to create internal variables for SCF computations; 

This package requires libxml2 to compile.

Thanks to Dodji Seketeli for the base XML parsing code.  See program
comments for source reference.

Initially targeted for DIATOM, the STO-based  diatomic molecular orbital 
program based on research by Silverstone, Kay, and Todd, published in
the Journal of Chemical Physics.

Written by H. D. Todd, January, 2015 on OSX 10.10
Verified on Raspbian January, 2015.

