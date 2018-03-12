#include "Recipe/parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Recipe/ingredient.h"
#include "Recipe/recipe.h"
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"



void Parser_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err) {}
											  
void Parser_Update(struct RTOS_SHARED_MEM* RTOS_MEM, uint32_t RTOSTime) {}



std::vector<Ingredient> Parser::parseFile(std::string fileName)
{
    std::vector<Ingredient> result;
    std::string line;
    std::string filePath = RECIPE_PATH + fileName + ".xml";
    std::ifstream File(filePath);
    if (File.is_open())
    {
        rapidxml::xml_document<> doc;
        rapidxml::xml_node<> *root_node;

        std::vector<char> buffer((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());
        buffer.push_back('\0');
        doc.parse<0>(&buffer[0]);
        root_node = doc.first_node("recipeml")->first_node("recipe");
        
        for(rapidxml::xml_node<> *i = root_node->first_node("ingredients")->first_node("ing");
            i != 0; i = i->next_sibling("ing"))
        {
            std::string spice_str  (i->first_node("item")->value());
            std::string meas_str   (i->first_node("amt")->first_node("unit")->value());
            std::string amount_str (i->first_node("amt")->first_node("qty")->value());
            double amount_d  = std::stod(amount_str);

            Ingredient ingredient_obj(amount_d, meas_str, spice_str);
            result.push_back(ingredient_obj);
        }

        File.close();
    }

    else
    {
        std::cout << "Could not read recipe" << std::endl;
    }
    return result;
}



void Parser::writeFile(std::string fileName, std::vector<Ingredient> IngList)
{
    std::string filePath = RECIPE_PATH + fileName + ".xml";
    rapidxml::xml_document<> doc;

    rapidxml::xml_node<> *decl = doc.allocate_node(rapidxml::node_declaration);
    decl->append_attribute(doc.allocate_attribute("version", "1.0"));
    decl->append_attribute(doc.allocate_attribute("encoding", "UTF-8"));
    doc.append_node(decl);

    rapidxml::xml_node<> *doct = doc.allocate_node(rapidxml::node_doctype, "",
                                                "recipeml PUBLIC \"-//FormatData//DTD RecipeML 0.5//EN\"\n"
                                                "\t\"http://www.formatdata.com/recipeml.recipeml.dtd\"");
    doc.append_node(doct);

    rapidxml::xml_node<> *style = doc.allocate_node(rapidxml::node_pi, "xml-stylesheet",
                                                    "href=\"dessert1.css\" type=\"text/css\"");
    doc.append_node(style);

    rapidxml::xml_node<> *root = doc.allocate_node(rapidxml::node_element, "recipeml");
    root->append_attribute(doc.allocate_attribute("version", "0.5"));
    doc.append_node(root);

    rapidxml::xml_node<> *recipe = doc.allocate_node(rapidxml::node_element, "recipe");
    root->append_node(recipe);

    rapidxml::xml_node<> *head = doc.allocate_node(rapidxml::node_element, "head");
    rapidxml::xml_node<> *title = doc.allocate_node(rapidxml::node_element, "title", "thing");
    head->append_node(title);
    recipe->append_node(head);

    rapidxml::xml_node<>* ingredients = doc.allocate_node(rapidxml::node_element, "ingredients");
    recipe->append_node(ingredients);

    rapidxml::xml_node<> *entry, *amt, *qty, *unit, *item;
    for(std::vector<Ingredient>::iterator i = IngList.begin(); i != IngList.end(); ++i)
    {
        std::stringstream ss;
        ss << (*i).getAmount();
        std::string amount_str = ss.str();
        char * amount = new char[amount_str.size() + 1];
        std::copy(amount_str.begin(), amount_str.end(), amount);
        amount[amount_str.size()] = '\0';

        std::string meas_str = (*i).getMeasurement();
        char * meas = new char[meas_str.size() + 1];
        std::copy(meas_str.begin(), meas_str.end(), meas);
        meas[meas_str.size()] = '\0';

        std::string spice_str = (*i).getType();
        char * spice = new char[spice_str.size() + 1];
        std::copy(spice_str.begin(), spice_str.end(), spice);
        spice[spice_str.size()] = '\0';


        entry = doc.allocate_node(rapidxml::node_element, "ing");
        ingredients->append_node(entry);

        amt = doc.allocate_node(rapidxml::node_element, "amt");
        entry->append_node(amt);

        qty = doc.allocate_node(rapidxml::node_element, "qty", amount);
        amt->append_node(qty);

        unit = doc.allocate_node(rapidxml::node_element, "unit", meas);
        amt->append_node(unit);

        item = doc.allocate_node(rapidxml::node_element, "item", spice);
        entry->append_node(item);
    }
    

    std::ofstream File(filePath);
    if (File.is_open())
    {
        File << doc;
        File.close();
        doc.clear();
    }

    else
    {
        std::cout << "Could not write recipe" << std::endl;
    }
}

