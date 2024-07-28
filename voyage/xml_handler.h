#ifndef VOYAGE_XML_HANDLER_H_
#define VOYAGE_XML_HANDLER_H_

#include "../cxmlp/node.h"
#include "row.h"
#include "column.h"

Row *Voyage_GenSourceTree(XmlNode *);

Row *Voyage_GenSourceTree(XmlNode *root) {
	return Row_InitAtr(root);
}

#endif // VOYAGE_XML_HANDLER_H_
