#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

// Compile: gcc genxml.c -o genxml `xml2-config --cflags --libs

#define TMP_XML_FILE "/tmp/qemuxml.xml"

int main(int argc, char **argv)
{
	xmlDocPtr doc = NULL;
	xmlNodePtr root = NULL;

	// create new XML document
	doc = xmlNewDoc(BAD_CAST "1.0"); 
	// create root of XML
	root = xmlNewNode(NULL, BAD_CAST "root"); 
	xmlDocSetRootElement(doc, root);

	xmlSaveFormatFileEnc(TMP_XML_FILE, doc, "UTF-8", 1);

	// free the document
	xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();

	// read from the file
	FILE *fp = fopen(TMP_XML_FILE, "r");
	if(fp == NULL)
	{
		perror("Cannot open file\n");
		return 1;
	}

	char buf[1024];

	while(!feof(fp))
	{
		if(fgets(buf, 1024, fp) != NULL)
			printf("%s", buf);
		memset(buf, 0, 1024);
	}

	printf("\n");

	fclose(fp);

	return 0;
}
