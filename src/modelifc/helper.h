#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <list>
#include <libxml/parser.h>
#include <libxml/tree.h>

class helper
{
public:
    helper();
    static std::string toupper(const std::string& text);
    static std::string tolower(const std::string& text);
    static std::string normalize(const std::string& text);
    static std::string escape(const std::string& text);
    static std::string escapeHTML(const std::string & text);
    static std::list<std::pair<std::string, std::string> > typelist(std::string cname);
    static std::string xml_string_property(const xmlNode* node, std::string name);
    static long xml_long_property(const xmlNode* node, std::string name, long defValue = 0);
    static bool xml_bool_property(const xmlNode* node, std::string name, bool defValue = false);
    static xmlNode* xml_find_child(xmlNode* node, std::string name);
    static std::string xml_content(xmlNode* node);
};

#endif // HELPER_H
