#include "Recipe/parser.h"
#include "OS/OSMemMap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include "Recipe/ingredient.h"
#include "Recipe/recipe.h"
#include "Recipe/rapidxml-1.13/rapidxml.hpp"
#include "Recipe/rapidxml-1.13/rapidxml_print.hpp"

// #define ENABLE_DEBUG_CONSOLE

Parser parser;

//TEST RECIPE TO WRITE!!!!
std::vector<Ingredient> testIng;
std::vector<std::string> testDir;

void Parser_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err)
{
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Recipe init task starting" << std::endl;
	#endif
	
	struct Parser_MemMap* RecipeMem_ptr = &((*RTOS_MEM).ParserMem);
	(*RecipeMem_ptr).Recipe_Path = "./saved_recipes/";
	(*RecipeMem_ptr).rawfilename = "test.xml";
	(*RecipeMem_ptr).filename = (*RecipeMem_ptr).Recipe_Path + (*RecipeMem_ptr).rawfilename;


	// TEST RECIPE TO WRITE!!!!
	Ingredient a(1.3, "pounds", "salt");
	testIng.push_back(a);

	Ingredient b(1, "tablespoon", "garlic powder");
	testIng.push_back(b);
	
	Ingredient c(23, "ounces", "thyme flowers");
	testIng.push_back(c);
	
	Ingredient d(3.5, "grams", "bbq seasoning");
	testIng.push_back(d);
	

	testDir.push_back("Combine salt and garlic powder");
	testDir.push_back("Sprinkle the bbq seasoning over");
	testDir.push_back("Coat chicken with mixture");
	testDir.push_back("Grill for 3 minutes on each side");
	testDir.push_back("Garnish with thyme flowers");
	
	
	
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Recipe init task ending\n" << std::endl;
	#endif
}


											  
void Parser_Update(struct RTOS_SHARED_MEM* RTOS_MEM, uint32_t RTOSTime)
{
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Recipe update task starting" << std::endl;
	#endif
	
	//task update code	
	struct Parser_MemMap* RecipeMem_ptr = &((*RTOS_MEM).ParserMem);
	struct UI_MemMap* UIMem_ptr = &((*RTOS_MEM).UIMem);
	
	// Read a new recipe
	if((*UIMem_ptr).readRecipeFlag == 1)
	{
		(*RecipeMem_ptr).currentRecipe = parser.parseFile((*RecipeMem_ptr).filename);
		
		//#ifdef ENABLE_DEBUG_CONSOLE
			((*RecipeMem_ptr).currentRecipe).display();
		//#endif
		(*UIMem_ptr).readRecipeFlag = 0;
	}
	
	// Write the current recipe
	else if((*UIMem_ptr).writeRecipeFlag == 1)
	{
		/* TODO: test writing */
		Recipe testRec("./saved_recipes/writingTest.xml", testIng, testDir);
		parser.writeFile(testRec);
		(*UIMem_ptr).writeRecipeFlag = 0;
	}
	
		
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Recipe update task ending\n" << std::endl;
	#endif
}



Recipe Parser::parseFile(std::string fileName)
{
	Recipe result(fileName);
    std::string line;
    std::ifstream File(fileName);
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
            std::transform(spice_str.begin(), spice_str.end(), spice_str.begin(), ::tolower);
            std::transform(meas_str.begin(), meas_str.end(), meas_str.begin(), ::tolower);
           
            Ingredient ingredient_obj(amount_d, meas_str, spice_str);
            
            if(ingredient_obj.isSpice())
				result.addSpice(ingredient_obj);       
 
			else
				result.addIngredient(ingredient_obj);

        }
        
        for(rapidxml::xml_node<> *i = root_node->first_node("directions")->first_node("step");
            i != 0; i = i->next_sibling("step"))
        {
            std::string dir = i->value();
            result.addDirection(dir);
        }
        File.close();
    }

    else
    {
        std::cout << "Could not read recipe" << std::endl;
    }
    return result;
}



void Parser::writeFile(Recipe r)
{
    std::string filePath = r.getFileName();
    std::ofstream File(filePath);

    if (File.is_open())
    {
		std::vector<Ingredient> IngList = r.getIngredients();
		std::vector<std::string> DirList = r.getDirections();
        
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
		

		rapidxml::xml_node<>* directions = doc.allocate_node(rapidxml::node_element, "directions");
		recipe->append_node(directions);

		rapidxml::xml_node<> *step;

		for(std::vector<std::string>::iterator i = DirList.begin(); i != DirList.end(); ++i)
		{
			std::string dir_str = *i;
			char * dir = new char[dir_str.size() + 1];
			std::copy(dir_str.begin(), dir_str.end(), dir);
			dir[dir_str.size()] = '\0';
			
			step = doc.allocate_node(rapidxml::node_element, "step", dir);
			directions->append_node(step);
		}

        File << doc;
        File.close();
        doc.clear();
    } 
    
    
    else
    {
        std::cout << "Could not write recipe" << std::endl;
    }
}

