/**
 * Master program to read an XML input specification for a set of diatomic
 * molecular orbital calculations to be performed, including optimization or
 * plotting series specifications, and generate the input for the diatom
 * program.
 *
 * David Todd, April, 2014.
 * Packaged Jan, 2015
 *
 * dia-xml-inp.c : requires libxml2 library
 * To compile this file using gcc you can type
 * gcc `xml2-config --cflags --libs` -o dia-xml-inp dia-xml-inp.c xmlParse.c `xml2-config --libs`
 *
 * xml parsing code from http://xmlsoft.org/examples/tree1.c :
 * synopsis: Navigates a tree to print element names
 * purpose: Parse a file to a tree, use xmlDocGetRootElement() to
 *          get the root element, then walk the document and print
 *          all the element name in document order.
 * usage: tree1 filename_or_URL
 * test: tree1 test2.xml > tree1.tmp && diff tree1.tmp $(srcdir)/tree1.res
 * author: Dodji Seketeli
 * copy: see Copyright for the status of this software.
 */
#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

xmlNode* find_element(xmlNode * a_node, xmlChar * target);
xmlNode* find_content(xmlNode * anode);
xmlChar* get_field_value(xmlNode * dia_tree, xmlChar * field_name);
xmlChar *get_attribute_value(xmlNode * a_node, xmlChar * attrib_name);


int main(int argc, char **argv) {
    
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL, *dia_tree, *basis_fn, *cur_node;
    xmlChar *title, *probid, *opts, *atnoa, *atnob, *r, *charge, *multiplicity;
    xmlChar *r_range, *r_plot, *zeta_range;
    
    if (argc != 2) return(1);
    
    /*
     * This macro initializes the library and checks potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION
    
    /* Parse the file, validate the xml against the DTD, and get the DOM */
    doc = xmlReadFile(argv[1], NULL, XML_PARSE_DTDVALID | XML_PARSE_NOBLANKS);
    
    /* quit if the file couldn't be parsed */
    if (doc == NULL) {
        printf("error: could not parse file %s\n", argv[1]);
        printf("\tUse 'xmllint --valid %s' to validate input file\n", argv[1]);
    }
    
    /* Get the root element node */
    root_element = xmlDocGetRootElement(doc);
    
    /* First, find "diatomic" tree ELEMENT root node */
    dia_tree = find_element(root_element->parent, (xmlChar *) "diatomic");
    if (!dia_tree) {
        printf("Diatomic xml input error: libxml2 didn't find 'diatomic' defined in xml file %s\n", argv[1]);
        printf("Run 'xmllint --valid %s' to check input file for definition of 'diatomic'\n", argv[1]);
        return(1);
    }
    
    /* Retrieve the fields as text strings */
    title = get_field_value(dia_tree, (xmlChar *) "title");
    probid = get_field_value(dia_tree, (xmlChar *) "probid");
    opts = get_field_value(dia_tree, (xmlChar *) "opts");
    atnoa = get_field_value(dia_tree, (xmlChar *) "atnoa");
    atnob = get_field_value(dia_tree, (xmlChar *) "atnob");
    r = get_field_value(dia_tree, (xmlChar *) "r");
    if ( (cur_node=find_element(dia_tree, (xmlChar *) "r")) ) {
      if (cur_node->properties) {
	r_range = get_attribute_value(cur_node, (xmlChar *) "range");
        r_plot = get_attribute_value(cur_node, (xmlChar *) "plot");
      }
      else {
	r_plot = NULL;
        r_range = NULL;
      };
    };
    
    charge = get_field_value(dia_tree, (xmlChar *) "charge");
    multiplicity = get_field_value(dia_tree, (xmlChar *) "multiplicity");
    /* ... and print out those fixed-number fields */
    printf("\tTitle: %s\n", title);
    printf("\tProbid: %s\n", probid);
    printf("\tOpts: %s\n", opts);
    printf("\tAtNoA: %s\n", atnoa);
    printf("\tAtNoB: %s\n", atnob);
    printf("\tr: %s %s %s\n", r, r_range?r_range:(xmlChar *) "", r_plot?r_plot:(xmlChar *) "");
    printf("\tCharge: %s\n", charge);
    printf("\tMultiplicity: %s\n", multiplicity);
    
    /* Now process the variable number of basis functions */
    for ( (basis_fn=find_element(dia_tree, (xmlChar *) "basis_fn") ); basis_fn; basis_fn=basis_fn->next) {
        if ( (cur_node=find_element(basis_fn, (xmlChar *) "zeta")) )
            if (cur_node->properties) zeta_range = get_attribute_value(cur_node, (xmlChar *) "range");
            else zeta_range = NULL;
            else zeta_range = NULL;
        
        printf("\tBasis fn: center=%s, n=%s, l=%s, zeta=%s %s\n",
               get_field_value(basis_fn, (xmlChar *) "center"),
               get_field_value(basis_fn, (xmlChar *) "n"),
               get_field_value(basis_fn, (xmlChar *) "l"),
               get_field_value(basis_fn, (xmlChar *) "zeta"),
               zeta_range?zeta_range:(xmlChar *) "" );
    }
    
    /*free the document */
    xmlFreeDoc(doc);
    
    /*
     * Free the global variables that may
     * have been allocated by the parser.
     */
    xmlCleanupParser();
    
    return 0;
}

