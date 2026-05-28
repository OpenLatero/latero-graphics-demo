#include "../config.h"
#ifndef DISABLE_GRAPHICS_DEMO

#include "cardcollection.h"
#include <iostream>

CardCollection::CardCollection()
{
}

CardCollection::~CardCollection()
{
	for (uint i=0; i<size(); ++i)
		delete (*this)[i];
	clear();
}

bool CardCollection::Load(std::string file, const latero::Tactograph *dev, uint scale)
{
	std::string path = Glib::path_get_dirname(file) + "/";

	try
	{
		xmlpp::DomParser parser;
		//parser.set_validate();
		parser.set_substitute_entities();
		parser.parse_file(file);
		if (parser)
		{
			const xmlpp::Node* pNode = parser.get_document()->get_root_node();
			if (pNode)
			{
				const xmlpp::Element* nodeElement = dynamic_cast<const xmlpp::Element*>(pNode);
				if (nodeElement)
					name_ = nodeElement->get_attribute("name")->get_value();

				xmlpp::Node::const_NodeList list = pNode->get_children();
				for(xmlpp::Node::const_NodeList::iterator iter = list.begin(); iter != list.end(); ++iter)
				{
					const xmlpp::Node* n = *iter;
					if (n->get_name() == "CardSet")
					{
						const xmlpp::Element* nodeElement = dynamic_cast<const xmlpp::Element*>(n);
						assert(nodeElement);
					
						std::string file = nodeElement->get_attribute("file")->get_value();
						CardSet *cs = new CardSet();
						cs->Load(path+file, dev, scale);
						push_back(cs);
					}
				}
			}
   		}
	}
	catch(const std::exception& ex)
	{
		std::cout << "Exception caught: " << ex.what() << std::endl;
		return false;
	}
	return true;
}

#endif
